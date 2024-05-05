#ifndef VIOLET_ENGINE_TEXT_INTERNAL_HPP
#define VIOLET_ENGINE_TEXT_INTERNAL_HPP

#include <stb_truetype.h>

namespace Violet
{
	struct FontDraw {
		std::string text;
		uint        size;
		Vector2D    pos;
		Color       color;
	};

	class Font
	{
		public:
			typedef std::unordered_map<uint, Pointer<stbtt_packedchar>> PackMap;
			typedef std::unordered_map<uint, Pointer<Texture>>          TextureMap;
			typedef std::unordered_map<uint, float>                     HeightMap;

			Font(const std::string& id, const std::string& path);
			~Font();

			std::string           id             { "" };
			bool                  loaded         { false };
			stbtt_fontinfo        font           { { 0 } };
            Pointer<Mesh>         mesh           { nullptr };
			PackMap               packs;
			TextureMap            textures;
			HeightMap             heights;
			std::vector<FontDraw> draw_queue[256];
	};

	extern void InitFontGroup   ();
	extern void DestroyFontGroup();
	extern void DrawTextLayer   (uint layer);
}

#endif // VIOLET_ENGINE_TEXT_INTERNAL_HPP