#pragma once

#include "math/math.hpp"

// Axis-Aligned Bounding Box

namespace UI {
    
    struct Dimension2D {
        float left, right, top, bottom; 
    };

    struct AABB2D {
        Vec2f center, size; 

        Dimension2D GetDimensions() const {
            return Dimension2D{center.x - size.x, center.x + size.x, center.y + size.y, center.y - size.y};
        }
    };

    struct AABB3D {
        Vec3f center, size; 
    };

}