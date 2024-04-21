#ifndef VIOLET_ENGINE_MESSAGE_INTERNAL_HPP
#define VIOLET_ENGINE_MESSAGE_INTERNAL_HPP

#include "violet_message.hpp"
#include "violet_types.hpp"

namespace Violet
{
    enum class MessageType {
        Info,
        Warn,
        Error,
        Fatal
    };
    
    extern void MessageLog(const MessageType type, const std::string& message);
    extern void MessageBox(const MessageType type, const std::string& message);
}

#endif // VIOLET_ENGINE_MESSAGE_INTERNAL_HPP