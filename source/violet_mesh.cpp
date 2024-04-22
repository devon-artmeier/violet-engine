#include "violet_mesh_internal.hpp"
#include "violet_message_internal.hpp"

namespace Violet
{
    Mesh::Mesh(const bool dynamic, const uint vertex_count, const uint element_count, std::initializer_list<uint> attribute_lengths)
    {
        this->attribute_count   = attribute_lengths.size();
        this->attribute_lengths = new uint[this->attribute_count];

        int i = 0;
        for (uint it : attribute_lengths) {
            this->attribute_lengths[i++]  = it;
            this->vertex_stride          += it;
        }

        glGenVertexArrays(1, &this->vao);
        glGenBuffers(1, &this->vbo);
        glGenBuffers(1, &this->ebo);
        
        glBindVertexArray(this->vao);
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
    
        intptr_t attribute_offset = 0;
        for (int i = 0; i < this->attribute_count; i++) {
            uint length = this->attribute_lengths[i];
            glVertexAttribPointer(i, length, GL_FLOAT, GL_FALSE, this->vertex_stride * sizeof(float),
                                  reinterpret_cast<void*>(attribute_offset));
            glEnableVertexAttribArray(i);
            attribute_offset += length * sizeof(float);
        }
        glBindVertexArray(0);

        this->ResizeVertexBuffer(vertex_count, 0);
        this->ResizeElementBuffer(element_count, 0);
    }

    Mesh::~Mesh()
    {
        glDeleteVertexArrays(1, &this->vao);
        glDeleteBuffers(1, &this->vbo);
        glDeleteBuffers(1, &this->ebo);
    }

    Pointer<float> Mesh::GetVertexBuffer() const
    {
        return this->vertex_buffer;
    }

    Pointer<uint> Mesh::GetElementBuffer() const
    {
        return this->element_buffer;
    }

    void Mesh::RefreshVertexBuffer()
    {
        glBindVertexArray(this->vao);
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, this->GetVertexBufferLengthBytes(), this->vertex_buffer.Raw());
        glBindVertexArray(0);
    }

    void Mesh::RefreshElementBuffer()
    {
        glBindVertexArray(this->vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, this->GetElementBufferLengthBytes(), this->element_buffer.Raw());
        glBindVertexArray(0);
    }

    void Mesh::ResizeVertexBuffer(const uint count, const uint offset)
    {
        if (count > 0) {
            float* new_buffer = new float[count * this->vertex_stride];
            memset(new_buffer, 0, count * this->vertex_stride * sizeof(float));
            if (this->vertex_buffer != nullptr) {
                if (offset < count) {
                    uint space = ((count - offset) > this->vertex_count) ? this->vertex_count : (count - offset);
                    memcpy(new_buffer + (offset * this->vertex_stride), this->vertex_buffer.Raw(), 
                           space * this->vertex_stride * sizeof(float));
                }
            }
            this->vertex_buffer = new_buffer;
        } else if (this->vertex_buffer != nullptr) {
            this->vertex_buffer = nullptr;
        }
        
        this->vertex_count = count;

        glBindVertexArray(this->vao);
        glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
        glBufferData(GL_ARRAY_BUFFER, this->GetVertexBufferLengthBytes(), this->vertex_buffer.Raw(),
                     this->dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
    }

    void Mesh::ResizeElementBuffer(const uint count, const uint offset)
    {
        if (count > 0) {
            uint* new_buffer = new uint[count];
            memset(new_buffer, 0, count * sizeof(uint));
            if (this->element_buffer != nullptr) {
                if (offset < count) {
                    uint space = ((count - offset) > this->element_count) ? this->element_count : (count - offset);
                    memcpy(new_buffer + offset, this->element_buffer.Raw(), space * sizeof(uint));
                }
            }
            this->element_buffer = new_buffer;
        } else if (this->element_buffer != nullptr) {
            this->element_buffer = nullptr;
        }

        this->element_count = count;

        glBindVertexArray(this->vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->GetElementBufferLengthBytes(), this->element_buffer.Raw(),
                     this->dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
        glBindVertexArray(0);
    }
    
    void Mesh::AddVertexBufferSpace(const uint count, const bool before)
    {
        this->ResizeVertexBuffer(this->vertex_count + count, before ? count : 0);
    }

    void Mesh::AddElementBufferSpace(const uint count, const bool before)
    {
        this->ResizeElementBuffer(this->element_count + count, before ? count : 0);
    }

    void Mesh::ClearVertexBuffer()
    {
        if (this->vertex_buffer != nullptr) {
            memset(this->vertex_buffer.Raw(), 0, this->vertex_count * this->vertex_stride * sizeof(float));
            this->RefreshVertexBuffer();
        }
    }

    void Mesh::ClearElementBuffer()
    {
        if (this->element_buffer != nullptr) {
            memset(this->element_buffer.Raw(), 0, this->element_count* sizeof(uint));
            this->RefreshElementBuffer();
        }
    }

    uint Mesh::GetVertexCount() const
    {
        return this->vertex_count;
    }

    uint Mesh::GetVertexBufferLength() const
    {
        return this->GetVertexCount() * this->vertex_stride;
    }

    uint Mesh::GetVertexBufferLengthBytes() const
    {
        return this->GetVertexBufferLength() * sizeof(float);
    }

    uint Mesh::GetVertexStride() const
    {
        return this->vertex_stride;
    }

    uint Mesh::GetVertexStrideBytes() const
    {
        return this->GetVertexStride() * sizeof(float);
    }

    uint Mesh::GetElementCount() const
    {
        return this->element_count;
    }

    uint Mesh::GetElementBufferLength() const
    {
        return this->GetElementCount();
    }

    uint Mesh::GetElementBufferLengthBytes() const
    {
        return this->GetElementBufferLength() * sizeof(uint);
    }

    uint Mesh::GetAttributeLength(const uint index) const
    {
        return (index < this->attribute_count) ? this->attribute_lengths[index] : 0;
    }

    uint Mesh::GetAttributeLengthBytes(const uint index) const
    {
        return this->GetAttributeLength(index) * sizeof(float);
    }

    uint Mesh::GetVertexDrawCount() const
    {
        return (this->element_count > 0) ? this->element_count : this->vertex_count;
    }

    uint Mesh::GetPolygonDrawCount() const
    {
        return this->GetVertexDrawCount() / 3;
    }

    void Mesh::Draw() const
    {
        this->DrawPartial(this->GetPolygonDrawCount());
    }

    void Mesh::DrawPartial(uint count, const uint offset) const
    {
        uint poly_count = this->GetPolygonDrawCount();
        if (offset < poly_count) {
            if ((offset + count) > poly_count) {
                count = poly_count - offset;
            }

            if (count > 0) {
                glBindVertexArray(this->vao);
                if (this->element_count > 0) {
                    glDrawElements(GL_TRIANGLES, count * 3, GL_UNSIGNED_INT, reinterpret_cast<void*>(offset * 3 * sizeof(uint)));
                } else {
                    glDrawArrays(GL_TRIANGLES, offset * 3, count * 3);
                }
                glBindVertexArray(0);
            }
        }
    }
}