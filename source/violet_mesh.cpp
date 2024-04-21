#include "violet_mesh.hpp"
#include "violet_message.hpp"

namespace Violet
{
    static MeshManager* mesh_manager{ nullptr };

    void InitMeshManager()
    {
        mesh_manager = new MeshManager();
    }

    void CloseMeshManager()
    {
        delete mesh_manager;
    }

    void CreateMesh(const std::string& id, const bool dynamic, std::initializer_list<int> attribute_lengths)
    {
        mesh_manager->AddMesh(id, new Mesh(id, dynamic, attribute_lengths));
    }

    void DestroyMesh(const std::string& id)
    {
        mesh_manager->DestroyMesh(id);
    }

    void LoadMeshVertexData(const std::string& id, const float* const data, const int offset, const int count)
    {
        Mesh* mesh = mesh_manager->GetMesh(id);
        if (mesh != nullptr) mesh->LoadVertexData(data, offset, count);
    }

    void LoadMeshElementData(const std::string& id, const unsigned int* const data, const int offset, const int count)
    {
        Mesh* mesh = mesh_manager->GetMesh(id);
        if (mesh != nullptr) mesh->LoadElementData(data, offset, count);
    }

    void FlushMeshVertexData(const std::string& id)
    {
        Mesh* mesh = mesh_manager->GetMesh(id);
        if (mesh != nullptr) mesh->FlushVertexData();
    }

    void FlushMeshElementData(const std::string& id)
    {
        Mesh* mesh = mesh_manager->GetMesh(id);
        if (mesh != nullptr) mesh->FlushElementData();
    }
    
    int GetMeshVertexDataCount(const std::string& id)
    {
        Mesh* mesh = mesh_manager->GetMesh(id);
        if (mesh != nullptr) return mesh->GetVertexDataCount();
        return 0;
    }

    int GetMeshElementDataCount(const std::string& id)
    {
        Mesh* mesh = mesh_manager->GetMesh(id);
        if (mesh != nullptr) return mesh->GetElementDataCount();
        return 0;
    }

    int GetMeshVertexDataStride(const std::string& id)
    {
        Mesh* mesh = mesh_manager->GetMesh(id);
        if (mesh != nullptr) return mesh->GetVertexDataStride();
        return 0;
    }

    int GetMeshVertexCount(const std::string& id)
    {
        Mesh* mesh = mesh_manager->GetMesh(id);
        if (mesh != nullptr) return mesh->GetVertexCount();
        return 0;
    }

    int GetMeshPolygonCount(const std::string& id)
    {
        Mesh* mesh = mesh_manager->GetMesh(id);
        if (mesh != nullptr) return mesh->GetPolygonCount();
        return 0;
    }

    void DrawMesh(const std::string& id)
    {
        Mesh* mesh = mesh_manager->GetMesh(id);
        if (mesh != nullptr) mesh->Draw();
    }

    void DrawMeshPartial(const std::string& id, int count, const int offset)
    {
        Mesh* mesh = mesh_manager->GetMesh(id);
        if (mesh != nullptr) mesh->DrawPartial(count, offset);
    }

    Mesh::Mesh(const std::string& id, const bool dynamic, std::initializer_list<int> attribute_lengths)
    {
        this->id                = id;
        this->attribute_count   = attribute_lengths.size();
        this->attribute_lengths = new int[this->attribute_count];

        int i = 0;
        for (int it : attribute_lengths) {
            this->attribute_lengths[i++]  = it;
            this->vertex_stride          += it;
        }

        glGenVertexArrays(1, &this->vao);
        
#ifdef VIOLET_DEBUG
        LogInfo("Created mesh \"" + id + "\"");
#endif
    }

    Mesh::~Mesh()
    {
        glDeleteVertexArrays(1, &this->vao);
        glDeleteBuffers(1, &this->vbo);
        glDeleteBuffers(1, &this->ebo);

        if (this->vertices != nullptr)          delete[] this->vertices;
        if (this->elements != nullptr)          delete[] this->elements;
        if (this->attribute_lengths != nullptr) delete[] this->attribute_lengths;

#ifdef VIOLET_DEBUG
        LogInfo("Destroyed mesh \"" + id + "\"");
#endif
    }

    void Mesh::CreateVBO()
    {
        if (this->vbo == 0 && this->vertex_count > 0) {
            glBindVertexArray(this->vao);

            glGenBuffers(1, &this->vbo);
            glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
            glBufferData(GL_ARRAY_BUFFER, this->vertex_count * this->vertex_stride * sizeof(float),
                         this->vertices, this->dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);

            intptr_t offset = 0;
            for (int i = 0; i < this->attribute_count; i++) {
                int length = this->attribute_lengths[i];
                glVertexAttribPointer(i, length, GL_FLOAT, GL_FALSE, this->vertex_stride * sizeof(float),
                                      reinterpret_cast<void*>(offset));
                glEnableVertexAttribArray(i);
                offset += length * sizeof(float);
            }
            
            glBindVertexArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
    }

    void Mesh::CreateEBO()
    {
        if (this->ebo == 0 && this->element_count > 0) {
            glBindVertexArray(this->vao);

            glGenBuffers(1, &this->ebo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->element_count * sizeof(unsigned int),
                         this->elements, this->dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
            
            glBindVertexArray(0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
    }

    template<typename T>
    static void SetData(const T* const src_data, T*& dest_data, const int offset, const int src_count, int& dest_count, const int stride)
    {
        int mem_stride = stride * sizeof(T);

        if (src_data != nullptr && offset >= 0) {
            if (dest_data != nullptr) {
                if ((offset + src_count) > dest_count) {
                    int new_dest_count = offset + src_count;
                    T*  new_dest_data  = new T[new_dest_count * stride];

                    memset(new_dest_data, 0, new_dest_count * mem_stride);
                    memcpy(new_dest_data, dest_data, ((offset > dest_count) ? dest_count : offset) * mem_stride);
                    memcpy(new_dest_data + (offset * stride), src_data, src_count * mem_stride);
                    
                    delete[] dest_data;
                    dest_data  = new_dest_data;
                    dest_count = new_dest_count;
                } else {
                    memcpy(dest_data + (offset * stride), src_data, src_count * mem_stride);
                }
            } else {
                dest_count = offset + src_count;
                dest_data = new T[dest_count * stride];
                
                memset(dest_data, 0, offset * mem_stride);
                memcpy(dest_data + (offset * stride), src_data, src_count * mem_stride);
            }
        }
    }

    void Mesh::LoadVertexData(const float* const data, const int offset, const int count)
    {
        SetData<float>(data, this->vertices, offset, count, this->vertex_count, this->vertex_stride);
    }

    void Mesh::LoadElementData(const unsigned int* const data, const int offset, const int count)
    {
        SetData<unsigned int>(data, this->elements, offset, count, this->element_count, 1);
    }

    static void FlushData(GLuint& object, const GLenum type, const void* const data, const int count, int& prev_count, const int stride, const bool dynamic)
    {
        if (object != 0) {
            if (count > 0) {
                glBindBuffer(type, object);
                if (count == prev_count) {
                    glBufferSubData(type, 0, count * stride, data);
                } else {
                    glBufferData(type, count * stride, data, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
                }
                glBindBuffer(type, 0);
            } else {
                glDeleteBuffers(1, &object);
                object = 0;
            }
        }
        prev_count = count;
    }

    void Mesh::FlushVertexData()
    {
        FlushData(this->vbo, GL_ARRAY_BUFFER, this->vertices, this->vertex_count,
                  this->prev_vbo_count, this->vertex_stride * sizeof(float), dynamic);
        this->CreateVBO();
    }

    void Mesh::FlushElementData()
    {
        FlushData(this->ebo, GL_ELEMENT_ARRAY_BUFFER, this->elements, this->element_count,
                  this->prev_ebo_count, sizeof(unsigned int), dynamic);
        this->CreateEBO();
    }

    int Mesh::GetVertexDataCount() const
    {
        return this->vertex_count;
    }

    int Mesh::GetElementDataCount() const
    {
        return this->element_count;
    }

    int Mesh::GetVertexDataStride() const
    {
        return this->vertex_stride;
    }

    int Mesh::GetVertexCount() const
    {
        return (this->ebo != 0) ? this->element_count : this->vertex_count;
    }

    int Mesh::GetPolygonCount() const
    {
        return GetVertexCount() / 3;
    }

    void Mesh::Draw() const
    {
        this->DrawPartial(0);
    }

    void Mesh::DrawPartial(int count, const int offset) const
    {
        int max_count = this->GetPolygonCount();
        if (offset >= 0 && offset < max_count) {
            if (count <= 0) {
                count = max_count;
            }
            if ((offset + count) > max_count) {
                count = max_count - offset;
            }

            if (this->vbo != 0 && count > 0) {
                glBindVertexArray(this->vao);
                if (this->ebo != 0) {
                    glDrawElements(GL_TRIANGLES, count * 3, GL_UNSIGNED_INT,
                                   reinterpret_cast<void*>(offset * 3 * sizeof(unsigned int)));
                } else {
                    glDrawArrays(GL_TRIANGLES, offset * 3, count * 3);
                }
                glBindVertexArray(0);
            }
        }
    }

    MeshManager::~MeshManager()
    {
        this->DestroyAllMeshes();
    }

    Mesh* MeshManager::GetMesh(const std::string& id) const
    {
        auto Mesh = this->meshes.find(id);
        if (Mesh != this->meshes.end()) {
            return Mesh->second;
        }
        return nullptr;
    }

    void MeshManager::AddMesh(const std::string& id, Mesh* Mesh)
    {
        this->DestroyMesh(id);
        this->meshes.insert({id, Mesh});
    }
    
    void MeshManager::DestroyMesh(const std::string& id)
    {
        Mesh* Mesh = GetMesh(id);
        if (Mesh != nullptr) {
            delete Mesh;
            this->meshes.erase(id);
        }
    }
    
    void MeshManager::DestroyAllMeshes()
    {
        for (auto Mesh : this->meshes) {
            delete Mesh.second;
        }
        this->meshes.clear();
    }
}