#include <stdexcept>
#include <iostream>
#include <SDL3/SDL.h>
#include "violet_message_internal.hpp"
#include "violet_types.hpp"

namespace Violet
{
    void MessageLog(const MessageType type, const std::string& message)
    {
#ifdef VIOLET_DEBUG
        std::string build = "";
        switch (type) {
            case MessageType::Info:
                build += "[INFO]  ";
                break;
            case MessageType::Warn:
                build += "[WARN]  ";
                break;
            case MessageType::Error:
                build += "[ERROR] ";
                break;
            case MessageType::Fatal:
                build += "[FATAL] ";
                break;
        }

        size_t cursor = 0;
        while (cursor < message.length()) {
            size_t new_line = message.find('\r', cursor);
            if (new_line != std::string::npos) new_line++;
            else new_line = message.find('\n', cursor);

            if (new_line == std::string::npos) {
                build += message.substr(cursor);
                cursor = message.length();
            } else {
                build += message.substr(cursor, (new_line - cursor) + 1) + "        ";
                cursor = new_line + 1;
            }
        }
        
        std::cout << build << std::endl;
#endif
    }
    
    void MessageBox(const MessageType type, const std::string& message)
    {
        int box_type = 0;
        switch (type) {
            case MessageType::Info:
                box_type = SDL_MESSAGEBOX_INFORMATION;
                break;
            case MessageType::Warn:
                box_type = SDL_MESSAGEBOX_WARNING;
                break;
            case MessageType::Error:
            case MessageType::Fatal:
                box_type = SDL_MESSAGEBOX_ERROR;
                break;
        }
        
        SDL_ShowSimpleMessageBox(box_type, "", message.c_str(), nullptr);
    }
    
    void LogInfo(const std::string& message)
    {
        MessageLog(MessageType::Info, message);
    }
        
    void LogWarn(const std::string& message)
    {
        MessageLog(MessageType::Warn, message);
    }
        
    void LogError(const std::string& message)
    {
        MessageLog(MessageType::Error, message);
    }
    
    void MessageBoxInfo(const std::string& message)
    {
#ifdef VIOLET_DEBUG
        MessageLog(MessageType::Info, message);
#endif
        MessageBox(MessageType::Info, message);
    }
            
    void MessageBoxWarn(const std::string& message)
    {
#ifdef VIOLET_DEBUG
        MessageLog(MessageType::Warn, message);
#endif
        MessageBox(MessageType::Warn, message);
    }

    void MessageBoxError(const std::string& message)
    {
#ifdef VIOLET_DEBUG
        MessageLog(MessageType::Error, message);
#endif
        MessageBox(MessageType::Error, message);
    }
    
    void Fatal(const std::string& message)
    {
        throw std::runtime_error(message);
    }
}