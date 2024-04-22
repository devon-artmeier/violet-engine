#include "violet_file_internal.hpp"
#include "violet_message_internal.hpp"

namespace Violet
{
    File::File(const std::string& path, const bool write_mode)
    {
        this->path       = path;
        this->write_mode = write_mode;
        
        this->file.open(path, std::ios::binary | (write_mode ? std::ios::out : std::ios::in));
#ifdef VIOLET_DEBUG
        if (!this->IsOpen()) {
            if (!write_mode) {
                LogError("Failed to open \"" + this->path + "\" for reading");
            } else {
                LogError("Failed to open \"" + this->path + "\" for writing");
            }
        } else {
            if (!write_mode) {
                LogInfo("Opened file \"" + this->path + "\" for reading");
            } else {
                LogInfo("Opened file \"" + this->path + "\" for writing");
            }
        }
#endif
    }
    
    File::~File()
    {
        if (this->IsOpen()) {
#ifdef VIOLET_DEBUG
            LogInfo("Closed file \"" + this->path + "\"");
#endif
        }
        this->file.close();
    }
    
    bool File::IsOpen() const
    {
        return this->file.is_open();
    }
    
    bool File::AtEnd() const
    {
        return this->file.eof();
    }
    
    bool File::Failed() const
    {
        return this->file.fail();
    }
    
    static bool CheckInvalidRead(std::fstream& file, const std::string& path, const std::string& type_name, const bool write_mode)
    {
        if (!file.is_open()) {
#ifdef VIOLET_DEBUG
            LogError("Tried to read " + type_name + " while file \"" + path + "\" is not open.");
#endif
            return true;
        } else if (file.eof()) {
#ifdef VIOLET_DEBUG
            LogError("Tried to read " + type_name + " while at end of file \"" + path + "\"");
#endif
            return true;
        } else if (write_mode) {
#ifdef VIOLET_DEBUG
            LogError("Tried to read " + type_name + " while file \"" + path + "\" is in write mode.");
#endif
            return true;
        }
        return false;
    }
    
    static bool CheckReadFail(std::fstream& file, const std::string& path, const std::string& type_name)
    {
        if (file.fail()) {
#ifdef VIOLET_DEBUG
            LogError("Failed to read " + type_name + " from file \"" + path + "\"");
#endif
            return true;
        }
        return false;
    }
    
    static bool CheckReadEndOfFile(std::fstream& file, const std::string& path, const std::string& type_name)
    {
        if (file.eof()) {
#ifdef VIOLET_DEBUG
            std::string type_name_fix = type_name;
            type_name_fix[0] = std::toupper(type_name_fix[0]);
            LogWarn(type_name_fix +  " read from file \"" + path + "\" ended prematurely due to end of file being reached");
#endif
            return true;
        }
        return false;
    }
    
    template<typename T>
    static T ReadValue(std::fstream& file, const std::string& path, const std::string& type_name, const bool big_endian, const bool write_mode)
    {
        if (CheckInvalidRead(file, path, type_name, write_mode)) {
            return 0;
        }
        
        T value = 0;
        char buffer;

        for (int i = 0; i < sizeof(T); i++) {
            file.read(&buffer, sizeof(char));
            value |= static_cast<T>(buffer & 0xFF) << ((big_endian ? ((sizeof(T) - i) - 1) : i) << 3);
            if (i != (sizeof(T) - 1)) {
                if (CheckReadEndOfFile(file, path, type_name)) {
                    break;
                }
            } else if (CheckReadFail(file, path, type_name)) {
                break;
            }
        }
        return value;
    }
    
    char File::ReadChar()
    {
        if (CheckInvalidRead(this->file, this->path, "char", this->write_mode)) {
            return 0;
        }
        
        char buffer;
        file.read(&buffer, sizeof(char));
        CheckReadFail(this->file, this->path, "char");
        
        return buffer;
    }
    
    uchar File::ReadUChar() 
    {
        if (CheckInvalidRead(this->file, this->path, "unsigned char", this->write_mode)) {
            return 0;
        }
        
        char buffer;
        file.read(&buffer, sizeof(char));
        CheckReadFail(this->file, this->path, "unsigned char");
        
        return static_cast<uchar>(buffer);
    }
    
    schar File::ReadSChar() 
    {
        if (CheckInvalidRead(this->file, this->path, "signed char", this->write_mode)) {
            return 0;
        }
        
        char buffer;
        file.read(&buffer, sizeof(char));
        CheckReadFail(this->file, this->path, "signed char");
        
        return static_cast<schar>(buffer);
    }
    
    short File::ReadShortLE() 
    {
        return ReadValue<short>(this->file, this->path, "little-endian short", false, this->write_mode);
    }
    
    ushort File::ReadUShortLE() 
    {
        return ReadValue<ushort>(this->file, this->path, "little-endian unsigned short", false, this->write_mode);
    }
    
    int File::ReadIntLE() 
    {
        return ReadValue<int>(this->file, this->path, "little-endian int", false, this->write_mode);
    }
    
    uint File::ReadUIntLE() 
    {
        return ReadValue<uint>(this->file, this->path, "little-endian unsigned int", false, this->write_mode);
    }
    
    long File::ReadLongLE() 
    {
        return ReadValue<long>(this->file, this->path, "little-endian long", false, this->write_mode);
    }
    
    ulong File::ReadULongLE() 
    {
        return ReadValue<ulong>(this->file, this->path, "little-endian unsigned long", false, this->write_mode);
    }
    
    longlong File::ReadLongLongLE() 
    {
        return ReadValue<longlong>(this->file, this->path, "little-endian long long", false, this->write_mode);
    }
    
    ulonglong File::ReadULongLongLE() 
    {
        return ReadValue<ulonglong>(this->file, this->path, "little-endian unsigned long long", false, this->write_mode);
    }

    short File::ReadShortBE() 
    {
        return ReadValue<short>(this->file, this->path, "big-endian short", true, this->write_mode);
    }
    
    ushort File::ReadUShortBE() 
    {
        return ReadValue<ushort>(this->file, this->path, "big-endian unsigned short", true, this->write_mode);
    }
    
    int File::ReadIntBE() 
    {
        return ReadValue<int>(this->file, this->path, "big-endian int", true, this->write_mode);
    }
    
    uint File::ReadUIntBE() 
    {
        return ReadValue<uint>(this->file, this->path, "big-endian unsigned int", true, this->write_mode);
    }
    
    long File::ReadLongBE() 
    {
        return ReadValue<long>(this->file, this->path, "big-endian long", true, this->write_mode);
    }
    
    ulong File::ReadULongBE() 
    {
        return ReadValue<ulong>(this->file, this->path, "big-endian unsigned long", true, this->write_mode);
    }
    
    longlong File::ReadLongLongBE() 
    {
        return ReadValue<longlong>(this->file, this->path, "big-endian long long", true, this->write_mode);
    }
    
    ulonglong File::ReadULongLongBE() 
    {
        return ReadValue<ulonglong>(this->file, this->path, "big-endian unsigned long long", true, this->write_mode);
    }
    
    std::string File::ReadString(const uint size) 
    {
        if (CheckInvalidRead(this->file, this->path, "string", this->write_mode)) {
            return "";
        }
        
        std::string str = "";
        if (size == 0) {
            char buffer = ' ';
            while (buffer != '\0') {
                file.read(&buffer, sizeof(char));
                if (CheckReadEndOfFile(this->file, this->path, "string")) {
                    break;
                } else if (CheckReadFail(this->file, this->path, "string")) {
                    break;
                } else if (buffer != '\0') {
                    str += buffer;
                }
            }
        } else {
            char* buffer = new char[size + 1];
            memset(buffer, 0, (size + 1) * sizeof(char));
            
            file.read(buffer, size * sizeof(char));
            CheckReadFail(this->file, this->path, "string");
            
            str = buffer;
            delete[] buffer;
        }
        return str;
    }
    
    static bool CheckInvalidWrite(std::fstream& file, const std::string& path, const std::string& type_name, const bool write_mode)
    {
        if (!file.is_open()) {
#ifdef VIOLET_DEBUG
            LogError("Tried to write " + type_name + " while file \"" + path + "\" is not open.");
#endif
            return true;
        } else if (!write_mode) {
#ifdef VIOLET_DEBUG
            LogError("Tried to write " + type_name + " while file \"" + path + "\" is in read mode.");
#endif
            return true;
        }
        return false;
    }
    
    static bool CheckWriteFail(std::fstream& file, const std::string& path, const std::string& type_name)
    {
        if (file.fail()) {
#ifdef VIOLET_DEBUG
            LogError("Failed to write " + type_name + " to file \"" + path + "\"");
#endif
            return true;
        }
        return false;
    }
    
    template<typename T>
    static void WriteValue(std::fstream& file, const std::string& path, const T value, const std::string& type_name, const bool big_endian, const bool write_mode)
    {
        if (!CheckInvalidWrite(file, path, type_name, write_mode)) {
            for (int i = 0; i < sizeof(T); i++) {
                char buffer = (value >> ((big_endian ? ((sizeof(T) - i) - 1) : i) << 3)) & 0xFF;
                file.write(&buffer, sizeof(char));
                if (CheckWriteFail(file, path, type_name)) {
                    break;
                }
            }
        }
    }
    
    void File::WriteChar(const char value) 
    {
        if (!CheckInvalidWrite(this->file, this->path, "char", this->write_mode)) {
            file.write(&value, sizeof(char));
            CheckWriteFail(this->file, this->path, "char");
        }
    }
    
    void File::WriteShortLE(const short value) 
    {
        WriteValue<short>(this->file, this->path, value, "little-endian short", false, this->write_mode);
    }
    
    void File::WriteIntLE(const int value) 
    {
        WriteValue<int>(this->file, this->path, value, "little-endian int", false, this->write_mode);
    }
    
    void File::WriteLongLE(const long value) 
    {
        WriteValue<long>(this->file, this->path, value, "little-endian long", false, this->write_mode);
    }
    
    void File::WriteLongLongLE(const longlong value) 
    {
        WriteValue<longlong>(this->file, this->path, value, "little-endian long long", false, this->write_mode);
    }
    
    void File::WriteShortBE(const short value) 
    {
        WriteValue<short>(this->file, this->path, value, "big-endian short", true, this->write_mode);
    }
    
    void File::WriteIntBE(const int value) 
    {
        WriteValue<int>(this->file, this->path, value, "big-endian int", true, this->write_mode);
    }
    
    void File::WriteLongBE(const long value) 
    {
        WriteValue<long>(this->file, this->path, value, "big-endian long", true, this->write_mode);
    }
    
    void File::WriteLongLongBE(const longlong value) 
    {
        WriteValue<longlong>(this->file, this->path, value, "big-endian long long", true, this->write_mode);
    }
    
    void File::WriteString(const std::string& str, const bool terminate) 
    {
        if (!CheckInvalidWrite(this->file, this->path, "string", this->write_mode)) {
            file.write(str.c_str(), (str.length() + (terminate ? 1 : 0)) * sizeof(char));
            CheckWriteFail(this->file, this->path, "string");
        }
    }
}