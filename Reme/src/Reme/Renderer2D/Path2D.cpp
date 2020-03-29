#include "pch.h"
#include "Reme/Renderer2D/Path2D.h"

#include <glm/gtc/constants.hpp>
#include <glm/gtx/vector_angle.hpp>

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

    void Path2D::MoveTo(const glm::vec2& point)
    {
        BeginSubPath();
        GetSubPath().push_back(point);
    }

    void Path2D::LineTo(const glm::vec2& point)
    {
        if (m_SubPaths.empty()) 
        {
            MoveTo(point);
        }
        else
        {
            GetSubPath().push_back(point);
        }
    }

    void Path2D::BezierCurveTo(const glm::vec2& ctrlPoint1, const glm::vec2& ctrlPoint2, const glm::vec2& endPoint)
    {
        if (m_SubPaths.empty()) 
        {
            MoveTo(ctrlPoint1);
        }
        // TODO
    }

    void Path2D::QuadraticCurveTo(const glm::vec2& ctrlPoint, const glm::vec2& endPoint)
    {
        if (m_SubPaths.empty()) 
        {
            MoveTo(ctrlPoint);
        }
        // TODO
    }

    void Path2D::ArcTo(const glm::vec2& ctrlPoint1, const glm::vec2& ctrlPoint2, float radius)
    {
        if (m_SubPaths.empty()) 
        {
            MoveTo(ctrlPoint1);
        }

        SubPath2D& subPath = GetSubPath();
        if (
            subPath.back() == ctrlPoint1 || 
            ctrlPoint1 == ctrlPoint2 ||
            radius < EPSILON ||
            (Slope(ctrlPoint1, subPath.back()) - Slope(ctrlPoint1, ctrlPoint2)) < EPSILON
        )
        {
            LineTo(ctrlPoint1);
            return;
        }

        glm::vec2 v = glm::normalize(subPath.back() - ctrlPoint2);

        // glm::vec2 arcCenter = 

    }

    void Path2D::Arc(const glm::vec2& centerPoint, float radius, float startAngle, float endAngle, bool clockwise)
    {        
        Ellipse(centerPoint, { radius, radius }, startAngle, endAngle, clockwise);
    }

    void Path2D::Ellipse(const glm::vec2& centerPoint, const glm::vec2& radii, float rotation, float startAngle, float endAngle, bool clockwise)
    {
        startAngle = NormalizeAngle(startAngle);
        endAngle = NormalizeAngle(endAngle);        

        float cosRot = glm::cos(rotation);
        float sinRot = glm::sin(rotation);

        float d = PI / glm::mix(radii.x, radii.y, 0.5f);

        SubPath2D& subPath = GetSubPath();
        auto loop = [&](float angle)
        {
            float cosA = glm::cos(angle);
            float sinA = glm::sin(angle);
            subPath.emplace_back(
                centerPoint.x + radii.x * cosA * cosRot - radii.y * sinA * sinRot, 
                centerPoint.y + radii.x * cosA * sinRot + radii.y * sinA * cosRot
            );
        };

        if (clockwise)
        {
            if (startAngle < endAngle) startAngle += 2 * PI;
            for(float a = startAngle; a >= endAngle; a -= d) loop(a);
        }
        else
        {
            if (startAngle > endAngle) endAngle += 2 * PI;
            for(float a = startAngle; a <= endAngle; a += d) loop(a);
        }
    }

    void Path2D::Rect(const glm::vec2& point, const glm::vec2& size)
    {
        MoveTo(point);
        LineTo({ point.x + size.x, point.y          });
        LineTo({ point.x + size.x, point.y + size.y });
        LineTo({ point.x         , point.y + size.y });
        CloseSubPath();
    }
}
