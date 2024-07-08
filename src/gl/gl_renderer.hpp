#pragma once

#include <iostream>
#include <vector>

#include "buf.hpp"
#include "gl_rect.hpp"

namespace {
    VML::Vec4f GenRGBA() 
    {
        return { rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, rand() / (float)RAND_MAX, 1.0f }; 
    }

    void GenRect(std::vector<GL::RectVertex>& vec, const GL::AABB2D& dim, const VML::Vec4f& rgba) 
    {
        vec.emplace_back(GL::RectVertex{{ dim.left, dim.top, 0.0f }, rgba});
        vec.emplace_back(GL::RectVertex{{ dim.left, dim.bottom, 0.0f }, rgba});
        vec.emplace_back(GL::RectVertex{{ dim.right, dim.bottom, 0.0f }, rgba});
        vec.emplace_back(GL::RectVertex{{ dim.right, dim.bottom, 0.0f }, rgba});
        vec.emplace_back(GL::RectVertex{{ dim.right, dim.top, 0.0f }, rgba});
        vec.emplace_back(GL::RectVertex{{ dim.left, dim.top, 0.0f }, rgba});
    }
}

#include <iostream>

namespace GL 
{
    std::vector<RectVertex> GenVertexData(std::vector<RectVertex>& vec, const Rectangle& rect) 
    {
        VML::Vec4f rgba = GenRGBA(); 
        GenRect(vec, rect.m_BBox, rgba); 
        return vec;
    }

    class UIRenderer
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
            }

            void DrawElements() 
            {
                m_VAO.Bind(); 
                m_RectangleShader.Bind(); 
                m_RectangleShader.SetUniformMat4f("proj", m_OrthoProjection, GL_TRUE); 
                glDrawArrays(GL_TRIANGLES, 0, m_VertexCount); 
            }

            void FlowLayout(const VML::Vec2i& framebufferSize)
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

