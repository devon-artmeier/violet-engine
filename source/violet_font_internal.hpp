#ifndef VIOLET_ENGINE_FONT_INTERNAL_HPP
#define VIOLET_ENGINE_FONT_INTERNAL_HPP

#include <stb_truetype.h>

namespace Violet
{
	struct FontDraw {
		std::string text;
		uint        size;
		float       x;
		float       y;
		Color       color;
	};

	class Font
	{
		public:
			Font(const std::string& id, const std::string& path);
			~Font();

			bool IsLoaded() const;
			void QueueDraw(const uint layer, const FontDraw& draw);
			void DrawLayer(const uint layer);

		private:
			std::string                                         id             { "" };
			bool                                                loaded         { false };
			stbtt_fontinfo                                      font           { { 0 } };
            Pointer<Mesh>                                       mesh           { nullptr };
			std::unordered_map<uint, Pointer<stbtt_packedchar>> packs;
			std::unordered_map<uint, std::string>               textures;
			std::vector<FontDraw>                               draw_queue[256];
	};

	extern void DrawTextLayer(uint layer);
}

#endif // VIOLET_ENGINE_FONT_INTERNAL_HPP