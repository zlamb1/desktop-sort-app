#include "buf.hpp"

namespace GL
{
    VertexArray::VertexArray()
    {
        glGenVertexArrays(1, &m_ID); 
    }

    VertexArray::~VertexArray()
    {
        if (m_ID) glDeleteVertexArrays(1, &m_ID); 
    }
    
    void VertexArray::SetFormat(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset)
    {
        glEnableVertexAttribArray(index); 
        glVertexAttribPointer(index, size, type, normalized, stride, offset); 
    }

    void VertexArray::Bind() const
    {
        glBindVertexArray(m_ID); 
    }

    VertexBuffer::VertexBuffer()
    {
        glGenBuffers(1, &m_ID); 
    }

    VertexBuffer::~VertexBuffer()
    {
        if (m_ID) glDeleteBuffers(1, &m_ID); 
    }

    void VertexBuffer::Bind(BufferType type) const
    {
        GLenum target;
        switch (type)
        {
            default:
            case BufferType::ARRAY: target = GL_ARRAY_BUFFER;
            case BufferType::ATOMIC_COUNTER: target = GL_ATOMIC_COUNTER_BUFFER;
            case BufferType::COPY_READ: target = GL_COPY_READ_BUFFER;
            case BufferType::COPY_WRITE: target = GL_COPY_WRITE_BUFFER;
            case BufferType::DISPATCH_INDIRECT: target = GL_DISPATCH_INDIRECT_BUFFER;
            case BufferType::DRAW_INDIRECT: target = GL_DRAW_INDIRECT_BUFFER;
            case BufferType::ELEMENT_ARRAY: target = GL_ELEMENT_ARRAY_BUFFER;
            case BufferType::PIXEL_PACK: target = GL_PIXEL_PACK_BUFFER;
            case BufferType::PIXEL_UNPACK: target = GL_PIXEL_UNPACK_BUFFER;
            case BufferType::QUERY: target = GL_QUERY_BUFFER;
            case BufferType::SHADER_STORAGE: target = GL_SHADER_STORAGE_BUFFER;
            case BufferType::TEXTURE: target = GL_TEXTURE_BUFFER;
            case BufferType::TRANSFORM_FEEDBACK: target = GL_TRANSFORM_FEEDBACK;
            case BufferType::UNIFORM: target = GL_UNIFORM_BUFFER;
        }

        glBindBuffer(target, m_ID); 
    }
}