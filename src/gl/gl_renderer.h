#pragma once

#include <iostream>
#include <vector>

#include "gl_rect.h"
#include "ui/rect.h"

namespace {
    Vec4<float> GenRGBA() {
        return Vec4<float>{ rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, 1.0f }; 
    }

    void GenRect(std::vector<GL::RectVertex>& vec, Vec4<float> dim, Vec4<float> rgba, Vec2<float> center, Vec4<float> borderRadius) {
        Vec2<float> extents = { (dim.y - dim.x) / 2.0f, (dim.z - dim.w) / 2.0f };
        vec.emplace_back(GL::RectVertex{dim.x, dim.z, 0.0f, rgba, center, extents, borderRadius});
        vec.emplace_back(GL::RectVertex{dim.x, dim.w, 0.0f, rgba, center, extents, borderRadius});
        vec.emplace_back(GL::RectVertex{dim.y, dim.w, 0.0f, rgba, center, extents, borderRadius});
        vec.emplace_back(GL::RectVertex{dim.y, dim.w, 0.0f, rgba, center, extents, borderRadius});
        vec.emplace_back(GL::RectVertex{dim.y, dim.z, 0.0f, rgba, center, extents, borderRadius});
        vec.emplace_back(GL::RectVertex{dim.x, dim.z, 0.0f, rgba, center, extents, borderRadius});
    }
}

namespace GL {
    std::vector<RectVertex> GenVertexData(const GLRectangle& rect) {
        auto boundingRect = rect.GetBoundingRect(); 
        std::cout << boundingRect.left << ", " << boundingRect.right << ", " << boundingRect.top << ", " << boundingRect.bottom << std::endl;
        auto halfWidth = (boundingRect.right - boundingRect.left) / 2.0f;
        auto halfHeight = (boundingRect.top - boundingRect.bottom) / 2.0f; 
        auto radius = rect.GetNormalizedRadius(); 
        
        Vec4<float> rgba = GenRGBA(); 
        std::vector<RectVertex> vec{}; 

        GenRect(vec, Vec4<float>{ boundingRect.left, boundingRect.right, boundingRect.top, boundingRect.bottom }, 
            rgba, Vec2<float>{ boundingRect.left + halfWidth, boundingRect.top - halfHeight }, 
            { radius.topLeft, radius.topRight, radius.bottomLeft, radius.bottomRight }); 

        return vec;
    }
}

