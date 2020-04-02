#include "pch.h"
#include "Reme/Renderer2D/Path2D.h"

#include <math.h>
#include <glm/gtc/constants.hpp>

namespace Reme
{
    constexpr const float PI = glm::pi<float>();
    constexpr const float EPSILON = glm::epsilon<float>();

    float NormalizeAngle(float a)
    {
        while (a > 2 * PI) a -= 2 * PI;
        while (a < 0.0f) a += 2 * PI;
        return a;
    }

    float Slope(const glm::vec2& a, const glm::vec2& b)
    {
        return (b.y - a.y) / (b.x - a.x);
    }

    Path2D::Path2D(const std::vector<SubPath2D>& subPath)
        : m_SubPaths(subPath)
    {
    }

    void Path2D::AddPath(const Path2D& path, const glm::mat3& m)
    {
        // TODO
        // m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z,
		// m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z
    }

    void Path2D::CloseSubPath()
    {
        if (m_SubPaths.size() == 0) return;

        SubPath2D& subPath = GetSubPath();
        if (subPath.size() > 1 && subPath.front() != subPath.back())
        {
            subPath.push_back(subPath.front());

            BeginSubPath();
            GetSubPath().push_back(subPath.front());
        }
    }

    void Path2D::MoveTo(float x, float y)
    {
        BeginSubPath();
        GetSubPath().emplace_back(x, y);
    }

    void Path2D::LineTo(float x, float y)
    {
        if (m_SubPaths.empty())
        {
            MoveTo(x, y);
        }
        else
        {
            GetSubPath().emplace_back(x, y);
        }
    }

    void Path2D::BezierCurveTo(float c1X, float c1Y, float c2X, float c2Y, float x, float y)
    {
        EnsureSubPath(c1X, c1Y);
        auto& subPath = GetSubPath();
        glm::vec2 p = subPath.back();
        for (double t = 0.0; t <= 1.0; t += 0.0001)
        {
            glm::vec2 np(
                pow(1-t,3)*p.x + 3*t*pow(1-t, 2)*c1X + 3*(1-t)*t*t*c2X + t*t*t*x,
                pow(1-t,3)*p.y + 3*t*pow(1-t, 2)*c1Y + 3*(1-t)*t*t*c2Y + t*t*t*y
            );

            if (glm::distance(np, subPath.back()) >= 1.0f) subPath.push_back(np);
        }
    }

    void Path2D::QuadraticCurveTo(float cX, float cY, float x, float y)
    {
        EnsureSubPath(cX, cY);
        auto& subPath = GetSubPath();
        glm::vec2 p = subPath.back();
        for (double t = 0.0; t <= 1.0; t += 0.0001)
        {
            glm::vec2 np(
                pow(1 - t, 2) * p.x + 2 * (1 - t) * t * cX + t * t * x,
                pow(1 - t, 2) * p.y + 2 * (1 - t) * t * cY + t * t * y
            );

            if (glm::distance(np, subPath.back()) >= 1.0f) subPath.push_back(np);
        }
    }

    void Path2D::ArcTo(float c1X, float c1Y, float c2X, float c2Y, float radius)
    {
        EnsureSubPath(c1X, c1Y);

        glm::vec2 p0 = GetSubPath().back();
        glm::vec2 p1(c1X, c1Y);
        glm::vec2 p2(c2X, c2Y);

        // Execute these calculations in double precision to avoid cumulative
        // rounding errors.
        double dir, a2, b2, c2, cosX, sinX, d, anx, any, bnx, bny, x3, y3, x4, y4, cx,
            cy, angle0, angle1;
        bool anticlockwise;

        if (p0 == p1 || p1 == p2 || radius == 0) {
            LineTo(p1.x, p1.y);
            return;
        }

        // Check for colinearity
        dir = (p2.x - p1.x) * (p0.y - p1.y) + (p2.y - p1.y) * (p1.x - p0.x);
        if (dir == 0) {
            LineTo(p1.x, p1.y);
            return;
        }

        // XXX - Math for this code was already available from the non-azure code
        // and would be well tested. Perhaps converting to bezier directly might
        // be more efficient longer run.
        a2 = (p0.x - c1X) * (p0.x - c1X) + (p0.y - c1Y) * (p0.y - c1Y);
        b2 = (c1X - c2X) * (c1X - c2X) + (c1Y - c2Y) * (c1Y - c2Y);
        c2 = (p0.x - c2X) * (p0.x - c2X) + (p0.y - c2Y) * (p0.y - c2Y);
        cosX = (a2 + b2 - c2) / (2 * sqrt(a2 * b2));

        sinX = sqrt(1 - cosX * cosX);
        d = radius / ((1 - cosX) / sinX);

        anx = (c1X - p0.x) / sqrt(a2);
        any = (c1Y - p0.y) / sqrt(a2);
        bnx = (c1X - c2X) / sqrt(b2);
        bny = (c1Y - c2Y) / sqrt(b2);
        x3 = c1X - anx * d;
        y3 = c1Y - any * d;
        x4 = c1X - bnx * d;
        y4 = c1Y - bny * d;
        anticlockwise = (dir < 0);
        cx = x3 + any * radius * (anticlockwise ? 1 : -1);
        cy = y3 - anx * radius * (anticlockwise ? 1 : -1);
        angle0 = atan2((y3 - cy), (x3 - cx));
        angle1 = atan2((y4 - cy), (x4 - cx));

        LineTo(x3, y3);

        Arc(cx, cy, radius, angle0, angle1, anticlockwise);
    }

    void Path2D::Arc(float x, float y, float radius, float startAngle, float endAngle, bool anticlockwise)
    {
        Ellipse(x, y, radius, radius, startAngle, endAngle, anticlockwise);
    }

    void Path2D::Ellipse(
        float x, float y, float rX, float rY,
        float rotation, float startAngle, float endAngle,
        bool anticlockwise
    )
    {
        startAngle = NormalizeAngle(startAngle);
        endAngle = NormalizeAngle(endAngle);

        float cosRot = glm::cos(rotation);
        float sinRot = glm::sin(rotation);

        float d = PI / glm::mix(rX, rY, 0.5f);

        SubPath2D& subPath = GetSubPath();
        auto loop = [&](float angle)
        {
            float cosA = glm::cos(angle);
            float sinA = glm::sin(angle);
            glm::vec2 np(
                x + rX * cosA * cosRot - rY * sinA * sinRot,
                y + rX * cosA * sinRot + rY * sinA * cosRot
            );

            if (glm::distance(np, subPath.back()) >= 1.0f) subPath.push_back(np);
        };

        if (anticlockwise)
        {
            if (startAngle >= endAngle) endAngle += 2 * PI;
            for(float a = startAngle; a <= endAngle; a += d) loop(a);
        }
        else
        {
            if (startAngle <= endAngle) startAngle += 2 * PI;
            for(float a = startAngle; a >= endAngle; a -= d) loop(a);
        }
    }

    void Path2D::Rect(float x, float y, float w, float h)
    {
        MoveTo(x    , y);
        LineTo(x + w, y);
        LineTo(x + w, y + h);
        LineTo(x    , y + w);
        CloseSubPath();
    }

    const std::vector<SubPath2D>& Path2D::GetPathData()
    {
        auto it = m_SubPaths.cend() - 1;
        for (; it != m_SubPaths.cbegin(); --it)
        {
            if (it->size() == 1)
            {
                m_SubPaths.erase(it);
            }
        }

        return m_SubPaths;
    }
}