#include "violet_engine_internal.hpp"

namespace Violet
{
    File::File(const std::string& path, const bool write_mode)
    {
        this->path       = path;
        this->write_mode = write_mode;
        this->file.open(path, std::ios::binary | (write_mode ? std::ios::out : std::ios::in));
    }
    
    File::~File()
    {
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

    
    template<typename T>
    static T ReadValue(std::fstream& file, const bool big_endian)
    {
        T value = 0;
        char buffer;

        for (int i = 0; i < sizeof(T); i++) {
            file.read(&buffer, sizeof(char));
            if (file.fail()) return 0;
            value |= static_cast<T>(buffer & 0xFF) << ((big_endian ? ((sizeof(T) - i) - 1) : i) << 3);
        }
        return value;
    }
    
    char File::ReadChar()
    {
        char buffer = 0;
        this->file.read(&buffer, sizeof(char));
        return this->file.fail() ? 0 : buffer;
    }
    
    uchar File::ReadUChar() 
    {
        return static_cast<uchar>(this->ReadChar());
    }
    
    schar File::ReadSChar() 
    {
        return static_cast<schar>(this->ReadChar());
    }
    
    short File::ReadShortLE() 
    {
        return ReadValue<short>(this->file, false);
    }
    
    ushort File::ReadUShortLE() 
    {
        return ReadValue<ushort>(this->file, false);
    }
    
    int File::ReadIntLE() 
    {
        return ReadValue<int>(this->file, false);
    }
    
    uint File::ReadUIntLE() 
    {
        return ReadValue<uint>(this->file, false);
    }
    
    long File::ReadLongLE() 
    {
        return ReadValue<long>(this->file, false);
    }
    
    ulong File::ReadULongLE() 
    {
        return ReadValue<ulong>(this->file, false);
    }
    
    longlong File::ReadLongLongLE() 
    {
        return ReadValue<longlong>(this->file, false);
    }
    
    ulonglong File::ReadULongLongLE() 
    {
        return ReadValue<ulonglong>(this->file, false);
    }

    short File::ReadShortBE() 
    {
        return ReadValue<short>(this->file, true);
    }
    
    ushort File::ReadUShortBE() 
    {
        return ReadValue<ushort>(this->file, true);
    }
    
    int File::ReadIntBE() 
    {
        return ReadValue<int>(this->file, true);
    }
    
    uint File::ReadUIntBE() 
    {
        return ReadValue<uint>(this->file, true);
    }
    
    long File::ReadLongBE() 
    {
        return ReadValue<long>(this->file, true);
    }
    
    ulong File::ReadULongBE() 
    {
        return ReadValue<ulong>(this->file, true);
    }
    
    longlong File::ReadLongLongBE() 
    {
        return ReadValue<longlong>(this->file, true);
    }
    
    ulonglong File::ReadULongLongBE() 
    {
        return ReadValue<ulonglong>(this->file, true);
    }
    
    std::string File::ReadString(const uint size) 
    {
        if (size == 0) {
            std::string str = "";
            char buffer = ' ';

            while (buffer != '\0') {
                this->file.read(&buffer, sizeof(char));
                if (this->file.fail()) return "";
                if (buffer != '\0')    str += buffer;
            }
            return str;
        } 
    
        Pointer<char> buffer = new char[size + 1];
        memset(buffer.Raw(), 0, (size + 1) * sizeof(char));
        
        this->file.read(buffer.Raw(), size * sizeof(char));
        return this->file.fail() ? "" : buffer.Raw();
    }
    
    template<typename T>
    static void WriteValue(std::fstream& file, const T value, const bool big_endian)
    {
        for (int i = 0; i < sizeof(T); i++) {
            char buffer = (value >> ((big_endian ? ((sizeof(T) - i) - 1) : i) << 3)) & 0xFF;
            file.write(&buffer, sizeof(char));
            if (file.fail()) break;
        }
    }
    
    void File::WriteChar(const char value) 
    {
        file.write(&value, sizeof(char));
    }
    
    void File::WriteShortLE(const short value) 
    {
        WriteValue<short>(this->file, value, false);
    }
    
    void File::WriteIntLE(const int value) 
    {
        WriteValue<int>(this->file, value, false);
    }
    
    void File::WriteLongLE(const long value) 
    {
        WriteValue<long>(this->file, value, false);
    }
    
    void File::WriteLongLongLE(const longlong value) 
    {
        WriteValue<longlong>(this->file, value, false);
    }
    
    void File::WriteShortBE(const short value) 
    {
        WriteValue<short>(this->file, value, true);
    }
    
    void File::WriteIntBE(const int value) 
    {
        WriteValue<int>(this->file, value, true);
    }
    
    void File::WriteLongBE(const long value) 
    {
        WriteValue<long>(this->file, value, true);
    }
    
    void File::WriteLongLongBE(const longlong value) 
    {
        WriteValue<longlong>(this->file, value, true);
    }
    
    void File::WriteString(const std::string& str, const bool terminate) 
    {
        file.write(str.c_str(), (str.length() + (terminate ? 1 : 0)) * sizeof(char));
    }
}