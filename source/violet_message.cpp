#include <stdexcept>
#include <iostream>
#include <SDL3/SDL.h>
#include "violet_engine.hpp"
#include "violet_message_internal.hpp"

namespace Violet
{
    void MessageLog(const MessageType type, const std::string& message)
    {
        std::string build = "";
        switch (type) {
            case MessageType::Info:
                build += "[INFO]    ";
                break;
            case MessageType::Warn:
                build += "[Warn] ";
                break;
            case MessageType::Error:
                build += "[ERROR]   ";
                break;
            case MessageType::Fatal:
                build += "[FATAL]   ";
                break;
        }
        build += message;
        
        std::cout << build << std::endl;
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
        MessageLog(MessageType::Info, message);
        MessageBox(MessageType::Info, message);
    }
            
    void MessageBoxWarn(const std::string& message)
    {
        MessageLog(MessageType::Warn, message);
        MessageBox(MessageType::Warn, message);
    }

    void MessageBoxError(const std::string& message)
    {
        MessageLog(MessageType::Error, message);
        MessageBox(MessageType::Error, message);
    }
    
    void Fatal(const std::string& message)
    {
        throw std::runtime_error(message);
    }
}