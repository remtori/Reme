#pragma once

#include "Reme/Renderer/Color.h"
#include "Reme/Renderer/Bitmap.h"

#include <glm/glm.hpp>

namespace Reme
{
    /**
     * Path2D with API similar to Web-Canvas
     */ 
    class Path2D
    {
    public:
        Path2D();
        Path2D(const Path2D&& other);
        ~Path2D();

        void BeginPath();
        void ClosePath();
        void MoveTo(float x, float y);
        void LineTo(float x, float y);

        // No curvy stuff for now

        // void BezierCurveTo(float cx1, float cy1, float cx2, float cy2, float x, float y);
        // void QuadraticCurveTo(float cx, float cy, float x, float y);
        // void ArcTo(float x1, float y1, float x2, float y2, float radius);
        // void Arc(float x, float y, float radius, float startAngle, float endAngle, bool isAntiClockWise = false);
        // void Ellipse(float x, float y, float rX, float rY);

        void Rect(float x, float y, float w, float h);

        void Stroke(const Color& color = Color::Black, uint32_t lineWidth = 10);
        void Fill(const Color& color = Color::Black);

        // Transformation
		const glm::mat3& GetTransform() { return m_Paths.back().transformMat; }
		void SetTransform(const glm::mat3& mat) { m_Paths.back().transformMat = mat; }

		void Translate(float x, float y);
		void Scale(float x, float y);
		void Rotate(float rotRadian);        

        std::string ToString() const;
    private:
        struct SubPath2D 
        { 
            glm::mat3 transformMat { 1.0f };
            std::vector<glm::vec2> points;
        };

        inline bool HasPath() { return m_Paths.size() > 0; }
        inline SubPath2D& GetPath() { return m_Paths.back(); }
        void DrawBitmap();

        bool m_Dirty;
        glm::vec4 m_AABB;
        Ref<Bitmap> m_Target;
        std::vector<SubPath2D> m_Paths;
    };
}
