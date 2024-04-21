#ifndef VIOLET_ENGINE_MESSAGE_HPP
#define VIOLET_ENGINE_MESSAGE_HPP

#include "violet_types.hpp"

namespace Violet
{
    extern void LogInfo        (const std::string& message);
    extern void LogWarn        (const std::string& message);
    extern void LogError       (const std::string& messages);
    extern void MessageBoxInfo (const std::string& message);
    extern void MessageBoxWarn (const std::string& message);
    extern void MessageBoxError(const std::string& message);
    extern void Fatal          (const std::string& message);
}

#endif // VIOLET_ENGINE_MESSAGE_HPP