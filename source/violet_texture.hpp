#ifndef VIOLET_ENGINE_TEXTURE_HPP
#define VIOLET_ENGINE_TEXTURE_HPP

#include <glad.h>

namespace Violet
{
    class Texture
    {
        public:
            void Bind();

        private:
            GLuint id{ 0 };
    }
}

#endif // VIOLET_ENGINE_TEXTURE_HPP