#pragma once

#include "ui/rect.hpp"

namespace GL {
    static const char* RECT_VERTEX_SHADER = R"END(
        #version 450 core

        in vec3 iPosition; 
        in vec4 iColor; 
        in vec2 iCenter; 
        in vec2 iExtents; 
        in vec4 iRadius; 

        out vec4 fragDiffuseColor; 
        out vec3 fragCoord; 

        uniform mat4 uProjection; 

        out VS_OUT {
            vec2 center;
            vec2 extents; 
            vec4 borderRadius;
        } rect;
        
        void main() {
            gl_Position = uProjection * vec4(iPosition, 1.0); 
            fragDiffuseColor = iColor; 
            fragCoord = iPosition; 
            rect.center = iCenter; 
            rect.extents = iExtents;
            rect.borderRadius = iRadius; 
        })END";

    static const char* RECT_FRAG_SHADER = R"END(
        #version 450 core

        in vec4 fragDiffuseColor;
        in vec3 fragCoord; 
        
        in VS_OUT {
            flat vec2 center;
            flat vec2 extents;
            flat vec4 borderRadius; 
        } rect;

        uniform vec2 uResolution; 

        out vec4 outputColor;

        float sdf_rect(vec2 pos, vec2 half_extents, float cornerRadius) {
            vec2 position = abs(pos) - half_extents + cornerRadius;
            return length(max(position, 0.0)) + min(max(position.x, position.y), 0.0) - cornerRadius;
        }

        void main() {
            int index = fragCoord.x > rect.center.x ? (fragCoord.y > rect.center.y ? 1 : 3) : (fragCoord.y > rect.center.y ? 0 : 2);
            float dist = sdf_rect(fragCoord.xy - rect.center, rect.extents, rect.borderRadius[index]);
            if (dist > 0.0) discard;
            outputColor = fragDiffuseColor;
            //float borderSize = 0.1; 
            //if (abs(dist) < borderSize) {
                //outputColor = vec4(1.0, 0.0, 0.0, 1.0);
            //}
            //float smoothness = 0.01;
            //outputColor.a = mix(outputColor.a, 0.0, smoothstep(smoothness, 0.0, abs(dist))); 
        })END";

    struct RectVertex {
        Vec3f pos; 
        Vec4f rgba;
        Vec2f center; 
        Vec2f extents; 
        Vec4f radius;
    };

    class GLRectangle : public UI::Rectangle {
        public:
            GLRectangle() : UI::Rectangle() {}

            void DrawElement() override {

            }
    };
}