#ifndef VIOLET_ENGINE_SHADER_HPP
#define VIOLET_ENGINE_SHADER_HPP

#include "violet_types.hpp"

namespace Violet
{
    typedef void (*ShaderCallback)(void* user_data);

    extern void LoadShader          (const std::string& id, const std::string& vertex_code, const std::string& frag_code);
    extern void DestroyShader       (const std::string& id);
    extern void SetShaderFloat      (const std::string& name, const float value);
    extern void SetShaderInt        (const std::string& name, const int value);
    extern void SetShaderUInt       (const std::string& name, const uint value);
    extern void SetShaderVec2       (const std::string& name, const float value[2]);
    extern void SetShaderIVec2      (const std::string& name, const int value[2]);
    extern void SetShaderUIVec2     (const std::string& name, const uint value[2]);
    extern void SetShaderVec3       (const std::string& name, const float value[3]);
    extern void SetShaderIVec3      (const std::string& name, const int value[3]);
    extern void SetShaderUIVec3     (const std::string& name, const uint value[3]);
    extern void SetShaderVec4       (const std::string& name, const float value[4]);
    extern void SetShaderIVec4      (const std::string& name, const int value[4]);
    extern void SetShaderUIVec4     (const std::string& name, const uint value[4]);
    extern void SetShaderFloatArray (const std::string& name, const uint count, const float* const value);
    extern void SetShaderIntArray   (const std::string& name, const uint count, const int* const value);
    extern void SetShaderUIntArray  (const std::string& name, const uint count, const uint* const value);
    extern void SetShaderVec2Array  (const std::string& name, const uint count, const float* const value);
    extern void SetShaderIVec2Array (const std::string& name, const uint count, const int* const value);
    extern void SetShaderUIVec2Array(const std::string& name, const uint count, const uint* const value);
    extern void SetShaderVec3Array  (const std::string& name, const uint count, const float* const value);
    extern void SetShaderIVec3Array (const std::string& name, const uint count, const int* const value);
    extern void SetShaderUIVec3Array(const std::string& name, const uint count, const uint* const value);
    extern void SetShaderVec4Array  (const std::string& name, const uint count, const float* const value);
    extern void SetShaderIVec4Array (const std::string& name, const uint count, const int* const value);
    extern void SetShaderUIVec4Array(const std::string& name, const uint count, const uint* const value);
    extern void SetShaderMatrix2x2  (const std::string& name, const bool swap, const uint count, const float* const value);
    extern void SetShaderMatrix3x3  (const std::string& name, const bool swap, const uint count, const float* const value);
    extern void SetShaderMatrix4x4  (const std::string& name, const bool swap, const uint count, const float* const value);
    extern void SetShaderMatrix2x3  (const std::string& name, const bool swap, const uint count, const float* const value);
    extern void SetShaderMatrix3x2  (const std::string& name, const bool swap, const uint count, const float* const value);
    extern void SetShaderMatrix2x4  (const std::string& name, const bool swap, const uint count, const float* const value);
    extern void SetShaderMatrix4x2  (const std::string& name, const bool swap, const uint count, const float* const value);
    extern void SetShaderMatrix3x4  (const std::string& name, const bool swap, const uint count, const float* const value);
    extern void SetShaderMatrix4x3  (const std::string& name, const bool swap, const uint count, const float* const value);
    extern void SetShaderTexture    (const std::string& texture, const uint slot);
}

#endif // VIOLET_ENGINE_SHADER_HPP