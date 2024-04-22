#ifndef VIOLET_ENGINE_MESH_INTERNAL_HPP
#define VIOLET_ENGINE_MESH_INTERNAL_HPP

#include <glad.h>
#include "violet_types.hpp"

namespace Violet
{
    class Mesh
    {
        public:
            Mesh(const bool dynamic, const uint vertex_count, const uint element_count, std::initializer_list<uint> attribute_lengths);
            ~Mesh();

            float* GetVertexBuffer            () const;
            uint*  GetElementBuffer           () const;
            void   RefreshVertexBuffer        ();
            void   RefreshElementBuffer       ();
            void   ResizeVertexBuffer         (const uint count, const uint offset);
            void   ResizeElementBuffer        (const uint count, const uint offset);
            void   AddVertexBufferSpace       (const uint count, const bool before = false);
            void   AddElementBufferSpace      (const uint count, const bool before = false);
            void   ClearVertexBuffer          ();
            void   ClearElementBuffer         ();
            uint   GetVertexCount             () const;
            uint   GetVertexBufferLength      () const;
            uint   GetVertexBufferLengthBytes () const;
            uint   GetVertexStride            () const;
            uint   GetVertexStrideBytes       () const;
            uint   GetElementCount            () const;
            uint   GetElementBufferLength     () const;
            uint   GetElementBufferLengthBytes() const;
            uint   GetAttributeLength         (const uint index) const;
            uint   GetAttributeLengthBytes    (const uint index) const;
            uint   GetVertexDrawCount         () const;
            uint   GetPolygonDrawCount        () const;
            void   Draw                       () const;
            void   DrawPartial                (uint count, const uint offset = 0) const;

        private:
            bool        dynamic          { false };
            uint        attribute_count  { 0 };
            uint*       attribute_lengths{ nullptr };
            float*      vertex_buffer    { nullptr };
            uint        vertex_count     { 0 };
            uint        vertex_stride    { 0 };
            uint*       element_buffer   { nullptr };
            uint        element_count    { 0 };
            GLuint      vbo              { 0 };
            GLuint      ebo              { 0 };
            GLuint      vao              { 0 };
    };
}

#endif // VIOLET_ENGINE_MESH_INTERNAL_HPP