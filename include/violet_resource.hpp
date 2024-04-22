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
        
        protected:
            std::string id{ "" };
    };
    
    class ResourceGroup
    {
        public:
            virtual ~ResourceGroup();
            
            Resource* Get       (const std::string& id) const;
            void      Add       (const std::string& id, Resource* resource);
            void      Destroy   (const std::string& id);
            void      DestroyAll();
        
        protected:
            std::unordered_map<std::string, Resource*> resources;
    };
}

#endif // VIOLET_RESOURCE_HPP