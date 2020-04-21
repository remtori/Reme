#include "RemePCH.h"
#include "Reme/Renderer/Path2D.h"
#include "Reme/Renderer/Renderer2D.h"

#include <glm/gtx/matrix_transform_2d.hpp>

namespace Reme
{
    Path2D::Path2D()
    {
    }

    Path2D::Path2D(const Path2D&& other)
        : m_Paths(std::move(other.m_Paths))
    {
    }

    Path2D::~Path2D()
    {
    }

    void Path2D::BeginPath()
    {
        m_Dirty = true;
        m_Paths.emplace_back();
    }

    void Path2D::ClosePath()
    {
        m_Dirty = true;
        auto& points = GetPath().points;
        if (points.size() > 1 && points.front() != points.back())
        {
            points.push_back(points.front());
        }
    }

    void Path2D::MoveTo(float x, float y)
    {
        m_Dirty = true;
        BeginPath();
        GetPath().points.emplace_back(x, y);
    }

    void Path2D::LineTo(float x, float y)
    {
        m_Dirty = true;
        // TODO: Refactor to EnsureSubPath
        if (GetPath().points.size() == 0) 
            GetPath().points.push_back(m_Paths[m_Paths.size() - 2].points.back());

        GetPath().points.emplace_back(x, y);
    }

    // void Path2D::BezierCurveTo(float cx1, float cy1, float cx2, float cy2, float x, float y)
    // {
    
    // }

    // void Path2D::QuadraticCurveTo(float cx, float cy, float x, float y)
    // {

    // }

    // void Path2D::ArcTo(float x1, float y1, float x2, float y2, float radius)
    // {

    // }

    // void Path2D::Arc(float x, float y, float radius, float startAngle, float endAngle, bool isAntiClockWise = false)
    // {

    // }

    // void Path2D::Ellipse(float x, float y, float rX, float rY)
    // {

    // }

    void Path2D::Rect(float x, float y, float w, float h)
    {        
        m_Dirty = true;
        MoveTo(x, y);
        LineTo(x + w, y);
        LineTo(x, y + h);
        LineTo(x + w, y + h);
        ClosePath();
    }

    void Path2D::Stroke(const Color& color, uint32_t lineWidth)
    {
        if (!m_Dirty){
            return DrawBitmap();

        
    }

    void Path2D::Fill(const Color& color)
    {
        if (!m_Dirty)
            return DrawBitmap();        
    }

    void Path2D::DrawBitmap()
    {
        Renderer2D::DrawTexture(m_Target, m_AABB.x, m_AABB.y, m_AABB.z, m_AABB.w);
    }

    void Path2D::Translate(float x, float y)
    {
        GetPath().transformMat = glm::translate(GetPath().transformMat, { x, y });
    }

    void Path2D::Scale(float x, float y)
    {
        GetPath().transformMat = glm::scale(GetPath().transformMat, { x, y });
    }

    void Path2D::Rotate(float rotRadian)
    {
        GetPath().transformMat = glm::rotate(GetPath().transformMat, rotRadian);
    }    

    std::string Path2D::ToString() const
    {
        std::stringstream ss; 

        ss << "Path2D {\n";
        for (const SubPath2D& sub : m_Paths)
        {
            ss << "SubPath { ";
            for (const glm::vec2& point : sub.points)
                ss << "(" << point.x << ", " << point.y << "), ";

            ss << " }\n";
        }

        ss << "}";

        return ss.str();
    }
}
