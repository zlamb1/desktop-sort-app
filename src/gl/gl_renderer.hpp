#pragma once

#include <iostream>
#include <vector>

#include "gl_rect.hpp"
#include "ui/rect.hpp"
#include "ui/ui_renderer.hpp"

namespace {
    Vec4f GenRGBA() 
    {
        return { rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, 1.0f }; 
    }

    void GenRect(std::vector<GL::RectVertex>& vec, Vec4f dim, Vec4f rgba, Vec2f center, Vec4f borderRadius) 
    {
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

namespace GL 
{
    std::vector<RectVertex> GenVertexData(const GLRectangle& rect) 
    {
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

    class UIRenderer : public UI::UIRenderer 
    {
        public:
            UIRenderer(const Vec2i& framebufferSize) : m_FramebufferSize(framebufferSize)
            {
                m_RectangleShader.AttachShader(GL::RECT_VERTEX_SHADER, GL_VERTEX_SHADER);
                m_RectangleShader.AttachShader(GL::RECT_VERTEX_SHADER, GL_FRAGMENT_SHADER); 
                assert(m_RectangleShader.CompileProgram()); 
                m_OrthoProjection = CreateOrthoProjectionf(0.0f, m_FramebufferSize.width, 0.0f, m_FramebufferSize.height, -1.0f, 1.0f);
            }

            void DrawElements() override 
            {
                m_RectangleShader.Bind(); 
                m_RectangleShader.SetUniformMat4f("proj", m_OrthoProjection, GL_TRUE); 
                glDrawArrays(GL_TRIANGLES, 0, m_VertexCount); 
            }

            void FlowLayout(const Vec2i& framebufferSize) override
            {
                m_FramebufferSize = framebufferSize; 
                m_OrthoProjection = CreateOrthoProjectionf(0.0f, m_FramebufferSize.width, 0.0f, m_FramebufferSize.height, -1.0f, 1.0f);
                // TODO: gen vertex data and upload to gl buf
            }

        private:
            Vec2i m_FramebufferSize{ 0, 0 }; 
            Mat4f m_OrthoProjection{}; 
            Shader m_RectangleShader{};

            int32_t m_VertexCount; 
    };
}

