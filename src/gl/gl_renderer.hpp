#pragma once

#include <iostream>
#include <vector>

#include "buf.hpp"
#include "gl_rect.hpp"
#include "ui/rect.hpp"
#include "ui/ui_renderer.hpp"

namespace {
    VML::Vec4f GenRGBA() 
    {
        return { rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, 1.0f }; 
    }

    void GenRect(std::vector<GL::RectVertex>& vec, VML::Vec4f dim, VML::Vec4f rgba, VML::Vec2f center, VML::Vec4f borderRadius) 
    {
        VML::Vec2f extents = { (dim.y - dim.x) / 2.0f, (dim.z - dim.w) / 2.0f };
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
    std::vector<RectVertex> GenVertexData(std::vector<RectVertex>& vec, const GLRectangle& rect) 
    {
        auto dimensions = rect.GetBoundingBox().GetDimensions(); 
        auto halfWidth = (dimensions.right - dimensions.left) / 2.0f;
        auto halfHeight = (dimensions.top - dimensions.bottom) / 2.0f; 
        auto radius = rect.GetRadius(); 
        
        VML::Vec4f rgba = GenRGBA(); 
        GenRect(vec, VML::Vec4f{ dimensions.left, dimensions.right, dimensions.top, dimensions.bottom }, 
            rgba, VML::Vec2f{ dimensions.left + halfWidth, dimensions.top - halfHeight }, 
            { radius.topLeft, radius.topRight, radius.bottomLeft, radius.bottomRight }); 

        return vec;
    }

    class UIRenderer : public UI::UIRenderer 
    {
        public:
            UIRenderer(const VML::Vec2i& framebufferSize) : m_FramebufferSize(framebufferSize)
            {
                m_RectangleShader.AttachShader(GL::RECT_VERTEX_SHADER, GL_VERTEX_SHADER);
                m_RectangleShader.AttachShader(GL::RECT_VERTEX_SHADER, GL_FRAGMENT_SHADER); 
                assert(m_RectangleShader.CompileProgram()); 
                m_OrthoProjection = VML::CreateOrthoProjectionf(0.0f, m_FramebufferSize.width, 0.0f, m_FramebufferSize.height, -1.0f, 1.0f);

                // create VAO format
                constexpr size_t vertexSize = sizeof(RectVertex);
                m_VAO.SetFormat(0, 3, GL_FLOAT, GL_FALSE, vertexSize, (void*)0);
                m_VAO.SetFormat(0, 4, GL_FLOAT, GL_FALSE, vertexSize, (void*)(offsetof(RectVertex, rgba)));
                m_VAO.SetFormat(0, 2, GL_FLOAT, GL_FALSE, vertexSize, (void*)(offsetof(RectVertex, center)));
                m_VAO.SetFormat(0, 2, GL_FLOAT, GL_FALSE, vertexSize, (void*)(offsetof(RectVertex, extents)));
                m_VAO.SetFormat(0, 4, GL_FLOAT, GL_FALSE, vertexSize, (void*)(offsetof(RectVertex, radius)));
            }

            void DrawElements() override 
            {
                m_VAO.Bind(); 
                m_RectangleShader.Bind(); 
                m_RectangleShader.SetUniformMat4f("proj", m_OrthoProjection, GL_TRUE); 
                glDrawArrays(GL_TRIANGLES, 0, m_VertexCount); 
            }

            void FlowLayout(const VML::Vec2i& framebufferSize) override
            {
                m_FramebufferSize = framebufferSize; 
                m_OrthoProjection = VML::CreateOrthoProjectionf(0.0f, m_FramebufferSize.width, 0.0f, m_FramebufferSize.height, -1.0f, 1.0f);
                std::vector<RectVertex> data{}; 
                m_VBO.Bind(BufferType::ARRAY);
                // realloc buf
                glBufferData(GL_ARRAY_BUFFER, sizeof(RectVertex) * data.size(), &data[0], GL_STATIC_DRAW); 
            }

        private:
            VML::Vec2i m_FramebufferSize{ 0, 0 }; 
            VML::Mat4f m_OrthoProjection{}; 
            Shader m_RectangleShader{};

            VertexArray m_VAO{};
            VertexBuffer m_VBO{};   
            int32_t m_VertexCount = 0; 
    };
}

