#include "violet_message.hpp"
#include "violet_resource.hpp"

namespace Violet
{
    Resource::Resource(const std::string& id)
    {
        this->resource_id = id;
    }

    Resource::~Resource()
    {
        if (this->loaded) {
            this->Info("Destroyed");
        }
    }

    std::string Resource::GetResourceId() const
    {
        return this->resource_id;
    }

    bool Resource::IsLoaded() const
    {
        return this->loaded;
    }

    bool Resource::Info(const std::string& message, bool condition) const
    {
#ifdef VIOLET_DEBUG
        if (condition) {
            LogInfo(this->resource_id + ": " + message);
        }
#endif
        return condition;
    }

    bool Resource::Warn(const std::string& message, bool condition) const
    {
#ifdef VIOLET_DEBUG
        if (condition) {
            LogWarn(this->resource_id + ": " + message);
        }
#endif
        return condition;
    }

    bool Resource::Error(const std::string& message, bool condition) const
    {
#ifdef VIOLET_DEBUG
        if (condition) {
            LogError(this->resource_id + ": " + message);
        }
#endif
        return condition;
    }
}