#pragma once

#include <glad/glad.h>

namespace GL
{
    enum class BufferType : int
    {
        ARRAY,
        ATOMIC_COUNTER,
        COPY_READ,
        COPY_WRITE,
        DISPATCH_INDIRECT,
        DRAW_INDIRECT,
        ELEMENT_ARRAY,
        PIXEL_PACK,
        PIXEL_UNPACK,
        QUERY,
        SHADER_STORAGE,
        TEXTURE,
        TRANSFORM_FEEDBACK,
        UNIFORM
    };

    class VertexArray
    {
        public:
            VertexArray();
            ~VertexArray(); 

            void Bind() const;

        private:
            GLuint m_ID; 
    };

    class VertexBuffer
    {
        public:
            VertexBuffer();
            ~VertexBuffer(); 

            void Bind(BufferType type) const; 

        private:
            GLuint m_ID; 
    };
}