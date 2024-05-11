#include "violet_engine_internal.hpp"

#ifdef WIN32
#ifdef APIENTRY
#undef APIENTRY
#endif
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#ifdef MessageBox
#undef MessageBox
#endif
#endif

namespace Violet
{
    enum class LogColor {
        Black = 0,
        DarkBlue,
        DarkGreen,
        DarkCyan,
        DarkRed,
        DarkMagenta,
        DarkYellow,
        LightGray,
        DarkGray,
        Blue,
        Green,
        Cyan,
        Red,
        Magenta,
        Yellow,
        White
    };

    static void SetLogColor(const LogColor color_fg, const LogColor color_bg)
    {
#ifdef WIN32
        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(console, static_cast<int>(color_fg) + (static_cast<int>(color_bg) << 4));
#else
        int code_fg = static_cast<int>(color_fg) + 30;
        if (code_fg >= 38) {
            code_fg += 90 - 38;
        }
        int code_bg = static_cast<int>(color_bg) + 40;
        if (code_bg >= 48) {
            code_bg += 100 - 48;
        }
        std::cout << "\[" + code_fg + ";" + code_bg + "m";
#endif
    }

    void MessageLog(const MessageType type, const std::string& message)
    {
#ifdef VIOLET_DEBUG
        switch (type) {
            case MessageType::Info:
                SetLogColor(LogColor::LightGray, LogColor::Black);
                std::cout << "[INFO]  ";
                break;
            case MessageType::Warn:
                SetLogColor(LogColor::Yellow, LogColor::Black);
                std::cout << "[WARN]  ";
                break;
            case MessageType::Error:
                SetLogColor(LogColor::Red, LogColor::Black);
                std::cout << "[ERROR] ";
                break;
            case MessageType::Fatal:
                SetLogColor(LogColor::White, LogColor::DarkRed);
                std::cout << "[FATAL] ";
                break;
        }

        std::string build = "";
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
        SetLogColor(LogColor::LightGray, LogColor::Black);
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