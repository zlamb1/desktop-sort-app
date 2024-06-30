#pragma once

#include <iostream>
#include <vector>

#include "rect.h"

namespace GLRect {
    static const char* RECT_VERTEX_SHADER = R"END(
        #version 450 core

        in vec3 iPosition; 
        in vec4 iColor; 
        in vec2 iCenter; 
        in float iRadius; 
        in int iAxis; 

        out vec4 fragDiffuseColor; 
        out vec3 fragCoord; 

        out vec2 rectCenter; 
        out float rectRadius; 
        out int rectAxis;
        
        void main() {
            gl_Position = vec4(iPosition, 1.0); 
            fragDiffuseColor = iColor; 
            fragCoord = iPosition; 

            rectCenter = iCenter; 
            rectRadius = iRadius; 
            rectAxis = iAxis; 
        })END";

    static const char* RECT_FRAG_SHADER = R"END(
        #version 450 core

        in vec4 fragDiffuseColor;
        in vec3 fragCoord; 
        
        flat in vec2 rectCenter; 
        flat in float rectRadius; 
        flat in int rectAxis;

        out vec4 outputColor;

        void main() {
            if (rectRadius > 0.0 && distance(fragCoord.xy, rectCenter) > rectRadius) {
                if (rectAxis == 0 && fragCoord.x < rectCenter.x && fragCoord.y > rectCenter.y) {
                    discard;
                }
                if (rectAxis == 1 && fragCoord.x > rectCenter.x && fragCoord.y > rectCenter.y) {
                    discard;
                }
                if (rectAxis == 2 && fragCoord.x < rectCenter.x && fragCoord.y < rectCenter.y) {
                    discard;
                }
                if (rectAxis == 3 && fragCoord.x > rectCenter.x && fragCoord.y < rectCenter.y) {
                    discard;
                }
            }
            outputColor = fragDiffuseColor;
        })END";

    struct Vertex {
        Vec3<float> pos; 
        Vec4<float> rgba;
        Vec2<float> center; 
        float radius;
        int32_t axis;  
    };

    Vec4<float> GenRGBA() {
        return Vec4<float>{ rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, 1.0f }; 
    }

    void GenRect(std::vector<Vertex>& vec, Vec4<float> dim, Vec4<float> rgba, Vec2<float> center, float radius, int32_t axis) {
        vec.emplace_back(Vertex{dim.x, dim.z, 0.0f, rgba.x, rgba.y, rgba.z, rgba.w, center.x, center.y, radius, axis});
        vec.emplace_back(Vertex{dim.x, dim.w, 0.0f, rgba.x, rgba.y, rgba.z, rgba.w, center.x, center.y, radius, axis});
        vec.emplace_back(Vertex{dim.y, dim.w, 0.0f, rgba.x, rgba.y, rgba.z, rgba.w, center.x, center.y, radius, axis});
        vec.emplace_back(Vertex{dim.y, dim.w, 0.0f, rgba.x, rgba.y, rgba.z, rgba.w, center.x, center.y, radius, axis});
        vec.emplace_back(Vertex{dim.y, dim.z, 0.0f, rgba.x, rgba.y, rgba.z, rgba.w, center.x, center.y, radius, axis});
        vec.emplace_back(Vertex{dim.x, dim.z, 0.0f, rgba.x, rgba.y, rgba.z, rgba.w, center.x, center.y, radius, axis});
    }

    std::vector<Vertex> GenVertexData(const Rectangle& rect) {
        auto boundingRect = rect.GetBoundingRect(); 
        auto halfWidth = (boundingRect.right - boundingRect.left) / 2.0f;
        auto halfHeight = (boundingRect.top - boundingRect.bottom) / 2.0f; 
        auto radius = rect.GetNormalizedRadius(); 
        
        Vec4<float> rgba = GenRGBA(); 
        std::vector<Vertex> vec{}; 

        GenRect(vec, Vec4<float>{ boundingRect.left, boundingRect.left + halfWidth, boundingRect.top, boundingRect.top - halfHeight }, 
            rgba, Vec2<float>{ boundingRect.left + radius.topLeft, boundingRect.top - radius.topLeft }, radius.topLeft, 0); 
        GenRect(vec, Vec4<float>{ boundingRect.left + halfWidth, boundingRect.right, boundingRect.top, boundingRect.top - halfHeight }, 
            rgba, Vec2<float>{ boundingRect.right - radius.topRight, boundingRect.top - radius.topRight }, radius.topRight, 1); 
        GenRect(vec, Vec4<float>{ boundingRect.left, boundingRect.left + halfWidth, boundingRect.top - halfHeight, boundingRect.bottom }, 
            rgba, Vec2<float>{ boundingRect.left + radius.bottomLeft, boundingRect.bottom + radius.bottomLeft }, radius.bottomLeft, 2); 
        GenRect(vec, Vec4<float>{ boundingRect.left + halfWidth, boundingRect.right, boundingRect.top - halfHeight, boundingRect.bottom }, 
            rgba, Vec2<float>{ boundingRect.right - radius.bottomRight, boundingRect.bottom + radius.bottomRight }, radius.bottomRight, 3); 

        return vec;
    }
}

