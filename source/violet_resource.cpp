#include "violet_resource.hpp"

namespace Violet
{
    Resource::Resource(const std::string& id)
    {
        this->id = id;
    }

    std::string Resource::GetId() const
    {
        return this->id;
    }
}