#define STB_VORBIS_HEADER_ONLY
#include <stb_vorbis.c>

#define MA_NO_DEVICE_IO
#define MA_NO_RUNTIME_LINKING
#ifdef VIOLET_DEBUG
#define MA_DEBUG_OUTPUT
#endif
#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio.h>