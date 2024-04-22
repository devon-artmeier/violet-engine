#ifndef VIOLET_ENGINE_FILE_INTERNAL_HPP
#define VIOLET_ENGINE_FILE_INTERNAL_HPP

#include <fstream>
#include "violet_types.hpp"

namespace Violet
{
    class File
    {
        public:
            File(const std::string& path, const bool write_mode);
            ~File();
            
            bool        IsOpen          () const;
            bool        AtEnd           () const;
            bool        Failed          () const;
            char        ReadChar        ();
            uchar       ReadUChar       ();
            schar       ReadSChar       ();
            short       ReadShortLE     ();
            ushort      ReadUShortLE    ();
            int         ReadIntLE       ();
            uint        ReadUIntLE      ();
            long        ReadLongLE      ();
            ulong       ReadULongLE     ();
            longlong    ReadLongLongLE  ();
            ulonglong   ReadULongLongLE ();
            short       ReadShortBE     ();
            ushort      ReadUShortBE    ();
            int         ReadIntBE       ();
            uint        ReadUIntBE      ();
            long        ReadLongBE      ();
            ulong       ReadULongBE     ();
            longlong    ReadLongLongBE  ();
            ulonglong   ReadULongLongBE ();
            std::string ReadString      (const uint size = 0);
            void        WriteChar       (const char value);
            void        WriteShortLE    (const short value);
            void        WriteIntLE      (const int value);
            void        WriteLongLE     (const long value);
            void        WriteLongLongLE (const longlong value);
            void        WriteShortBE    (const short value);
            void        WriteIntBE      (const int value);
            void        WriteLongBE     (const long value);
            void        WriteLongLongBE (const longlong value);
            void        WriteString     (const std::string& str, const bool terminate = true);

        private:
            bool CheckError();
        
            std::fstream file;
            std::string  path      { "" };
            bool         write_mode{ false };
    };

}

#endif // VIOLET_ENGINE_FILE_INTERNAL_HPP