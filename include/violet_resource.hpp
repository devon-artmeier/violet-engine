#ifndef VIOLET_RESOURCE_HPP
#define VIOLET_RESOURCE_HPP

#include "violet_types.hpp"

namespace Violet
{
    class Resource
    {
        public:
            Resource(const std::string& id);
            virtual ~Resource() { }

            std::string GetId() const;
        
        protected:
            std::string id{ "" };
    };
    
    template<typename T>
    class ResourceGroup
    {
        public:
            virtual ~ResourceGroup()
            {
                this->DestroyAll();
            }
            
            Pointer<T> Get(const std::string& id) const
            {
                auto resource = this->resources.find(id);
                if (resource != this->resources.end()) {
                    return resource->second;
                }
                return Pointer<T>(nullptr);
            }

            void Add(const std::string& id, const Pointer<T>& resource)
            {
                this->Destroy(id);
                this->resources.insert({id, resource});
            }
            
            void Destroy(const std::string& id)
            {
                const Pointer<T>& resource = this->Get(id);
                if (resource != nullptr) {
                    this->resources.erase(id);
                }
            }
            
            void DestroyAll()
            {
                this->resources.clear();
            }
        
        protected:
            std::unordered_map<std::string, Pointer<T>> resources;
    };
}

#endif // VIOLET_RESOURCE_HPP