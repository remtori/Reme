#pragma once

#include "Reme/Core/Core.h"

#include <glm/glm.hpp>
#include <vector>

namespace Reme
{
    using SubPath2D = std::vector<glm::vec2>;

    class Path2D
    {
    public:
        Path2D() = default;

        /**
         * Adds a path to the current path
         */
        void AddPath(const Path2D& path, const glm::mat3& transform = glm::mat3(1.0f));

        /**
         * Create a new empty sub-path and add it to the current path.
         */
        inline void BeginSubPath() { m_SubPaths.emplace_back(); }

        /**
         * Causes the point of the pen to move back to the start of the current sub-path.
         * It tries to draw a straight line from the current point to the start.
         * If the shape has already been closed or has only one point, this function does nothing.
         */
        void CloseSubPath();

        /**
         * Moves the starting point of a new sub-path to the Point coordinates.
         */
        void MoveTo(float x, float y);

        /**
         * Connects the last point in the subpath to the Point coordinates with a straight line.
         */
        void LineTo(float x, float y);

        /**
         * Adds a cubic Bézier curve to the path.
         * It requires three points.
         * The first two points are control points and the third one is the end point.
         * The starting point is the last point in the current path,
         * which can be changed using MoveTo() before creating the Bézier curve.
         */
        void BezierCurveTo(float c1X, float c1Y, float c2X, float c2Y, float x, float y);

        /**
         * Adds a quadratic Bézier curve to the current path.
         * It requires two points.
         * The first one is a control point and the second one is the end point.
         * The starting point is the latest point in the current path,
         * which can be changed using MoveTo() before creating the quadratic Bézier curve.
         */
        void QuadraticCurveTo(float cX, float cY, float x, float y);

        /**
         * Adds a circular arc to the current sub-path,
         * using the given control points and radius.
         * The arc is automatically connected to the path's latest point with a straight line,
         * if necessary for the specified parameters.
         */
        void ArcTo(float c1X, float c1Y, float c2X, float c2Y, float radius);

        /**
         * Adds an arc to the path which is centered at Point position
         * with radius r starting at startAngle and ending at endAngle
         * going in the given direction by clockwise (defaulting to clockwise).
         */
        void Arc(float x, float y, float radius, float startAngle, float endAngle, bool anticlockwise = false);

        /**
         * Adds an elliptical arc to the path which is centered at centerPoint position
         * with the radii radii.x and radii.y
         * starting at startAngle and ending at endAngle
         * going in the given direction by clockwise (defaulting to clockwise).
         */
        void Ellipse(
            float x, float y, float rX, float rY,
            float rotation, float startAngle, float endAngle,
            bool anticlockwise = false
        );

        /**
         * Creates a path for a rectangle at position Point
         * with a size that is determined by size.x and size.y
         */
        void Rect(float x, float y, float w, float h);

        const std::vector<SubPath2D>& GetPathData();
    private:
        Path2D(const std::vector<SubPath2D>& subPath);
        inline SubPath2D& GetSubPath() { return m_SubPaths.back(); }
        inline void EnsureSubPath(float x, float y)
        {
            if (m_SubPaths.empty()) MoveTo(x, y);
        }
    private:
        std::vector<SubPath2D> m_SubPaths;
    };
}
