#ifndef VIOLET_ENGINE_MESH_HPP
#define VIOLET_ENGINE_MESH_HPP

#include <string>
#include <unordered_map>
#include "glad/glad.h"

namespace Violet
{
    class Mesh
    {
        public:
            Mesh(const std::string& id, const bool dynamic, std::initializer_list<int> attribute_lengths);
            ~Mesh();

            void SetVertexData      (const float* const data, const int offset, const int count);
            void SetElementData     (const unsigned int* const data, const int offset, const int count);
            void FlushVertexData    ();
            void FlushElementData   ();
            int  GetVertexDataCount ();
            int  GetElementDataCount();
            int  GetVertexDataStride();
            int  GetVertexCount     ();
            int  GetPolygonCount    ();
            void Draw               ();
            void DrawPartial        (int count, const int offset = 0);

        private:
            void CreateVBO();
            void CreateEBO();

            std::string   id               { "" };
            bool          dynamic          { false };
            int           attribute_count  { 0 };
            int*          attribute_lengths{ nullptr };
            float*        vertices         { nullptr };
            int           vertex_count     { 0 };
            int           vertex_stride    { 0 };
            unsigned int* elements         { nullptr };
            int           element_count    { 0 };
            GLuint        vbo              { 0 };
            GLuint        ebo              { 0 };
            GLuint        vao              { 0 };
            int           prev_vbo_count   { 0 };
            int           prev_ebo_count   { 0 };
    };

    class MeshManager
    {
        public:
            ~MeshManager();

            Mesh* GetMesh         (const std::string& id);
            void  AddMesh         (const std::string& id, Mesh* Mesh);
            void  DestroyMesh     (const std::string& id);
            void  DestroyAllMeshes();

        private:
            std::unordered_map<std::string, Mesh*> meshes;
    };

    extern void InitMeshManager        ();
    extern void CloseMeshManager       ();
    extern void DestroyMesh            (const std::string& id);
    extern void SetMeshVertexData      (const std::string& id, const float* const data, const int offset, const int count);
    extern void SetMeshElementData     (const std::string& id, const float* const data, const int offset, const int count);
    extern void FlushMeshVertexData    (const std::string& id);
    extern void FlushMeshElementData   (const std::string& id);
    extern int  GetMeshVertexDataCount (const std::string& id);
    extern int  GetMeshElementDataCount(const std::string& id);
    extern int  GetMeshVertexDataStride(const std::string& id);
    extern int  GetMeshVertexCount     (const std::string& id);
    extern int  GetMeshPolygonCount    (const std::string& id);
    extern void DrawMesh               (const std::string& id);
    extern void DrawMeshPartial        (const std::string& id, int count, const int offset = 0);
}

#endif // VIOLET_ENGINE_MESH_HPP