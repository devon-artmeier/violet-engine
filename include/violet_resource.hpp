#ifndef VIOLET_ENGINE_RESOURCE_HPP
#define VIOLET_ENGINE_RESOURCE_HPP

namespace Violet
{
    extern void LoadShader            (const std::string& id, const std::string& vertex_code, const std::string& frag_code);
    extern void DestroyShader         (const std::string& id);
    extern void DestroyAllShaders     ();
    extern void LoadSound             (const std::string& id, const std::string& path);
    extern void DestroySound          (const std::string& id);
    extern void DestroyAllSounds      ();
    extern void LoadSpriteSheet       (const std::string& id, const std::string& path, const std::string& texture);
    extern void DestroySpriteSheet    (const std::string& id);
    extern void DestroyAllSpriteSheets();
    extern void LoadTexture           (const std::string& id, const std::string& path);
    extern void DestroyTexture        (const std::string& id);
    extern void DestroyAllTextures    ();
    extern void LoadFont              (const std::string& id, const std::string& path);
    extern void DestroyFont           (const std::string& id);
    extern void DestroyAllFonts       ();
}

#endif // VIOLET_ENGINE_RESOURCE_HPP