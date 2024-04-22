#include "violet_resource.hpp"

namespace Violet
{
    Resource::Resource(const std::string& id)
    {
        this->id = id;
    }
    
    ResourceGroup::~ResourceGroup()
    {
        this->DestroyAll();
    }

    Resource* ResourceGroup::Get(const std::string& id) const
    {
        auto resource = this->resources.find(id);
        if (resource != this->resources.end()) {
            return resource->second;
        }
        return nullptr;
    }

    void ResourceGroup::Add(const std::string& id, Resource* resource)
    {
        this->Destroy(id);
        this->resources.insert({id, resource});
    }
    
    void ResourceGroup::Destroy(const std::string& id)
    {
        Resource* resource = this->Get(id);
        if (resource != nullptr) {
            delete resource;
            this->resources.erase(id);
        }
    }
    
    void ResourceGroup::DestroyAll()
    {
        for (auto resource : this->resources) {
            delete resource.second;
        }
        this->resources.clear();
    }
}