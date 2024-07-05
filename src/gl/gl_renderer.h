#pragma once

#include <iostream>
#include <vector>

#include "gl_rect.h"
#include "ui/rect.h"

namespace {
    Vec4f GenRGBA() {
        return { rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, 1.0f }; 
    }

    void GenRect(std::vector<GL::RectVertex>& vec, Vec4f dim, Vec4f rgba, Vec2f center, Vec4f borderRadius) {
        Vec2f extents = { (dim.y - dim.x) / 2.0f, (dim.z - dim.w) / 2.0f };
        vec.emplace_back(GL::RectVertex{{ dim.x, dim.z, 0.0f }, rgba, center, extents, borderRadius});
        vec.emplace_back(GL::RectVertex{{ dim.x, dim.w, 0.0f }, rgba, center, extents, borderRadius});
        vec.emplace_back(GL::RectVertex{{ dim.y, dim.w, 0.0f }, rgba, center, extents, borderRadius});
        vec.emplace_back(GL::RectVertex{{ dim.y, dim.w, 0.0f }, rgba, center, extents, borderRadius});
        vec.emplace_back(GL::RectVertex{{ dim.y, dim.z, 0.0f }, rgba, center, extents, borderRadius});
        vec.emplace_back(GL::RectVertex{{ dim.x, dim.z, 0.0f }, rgba, center, extents, borderRadius});
    }
}

#include <iostream>

namespace GL {
    std::vector<RectVertex> GenVertexData(const GLRectangle& rect) {
        auto dimensions = rect.GetBoundingBox().GetDimensions(); 
        auto halfWidth = (dimensions.right - dimensions.left) / 2.0f;
        auto halfHeight = (dimensions.top - dimensions.bottom) / 2.0f; 
        auto radius = rect.GetRadius(); 
        
        Vec4f rgba = GenRGBA(); 
        std::vector<RectVertex> vec{}; 
        
        GenRect(vec, Vec4f{ dimensions.left, dimensions.right, dimensions.top, dimensions.bottom }, 
            rgba, Vec2f{ dimensions.left + halfWidth, dimensions.top - halfHeight }, 
            { radius.topLeft, radius.topRight, radius.bottomLeft, radius.bottomRight }); 

        return vec;
    }
}

