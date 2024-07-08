#pragma once

namespace GL {
    static const char* RECT_VERTEX_SHADER = R"END(
        #version 450 core

        in vec3 iPosition; 
        in vec4 iColor; 

        out vec4 fragDiffuseColor; 

        uniform mat4 uProjection; 
        
        void main() 
        {
            gl_Position = uProjection * vec4(iPosition, 1.0); 
            fragDiffuseColor = iColor; 
        })END";

    static const char* RECT_FRAG_SHADER = R"END(
        #version 450 core

        in vec4 fragDiffuseColor;

        out vec4 outputColor;

        void main() 
        {
            outputColor = fragDiffuseColor;
        })END";

    struct AABB2D
    {
        float left, right, bottom, top; 
    };

    struct RectVertex {
        VML::Vec3f pos; 
        VML::Vec4f rgba;
    };

    class Rectangle {
        public:
            Rectangle() 
            {
            }

            AABB2D m_BBox; 
    };
}