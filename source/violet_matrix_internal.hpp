#ifndef VIOLET_ENGINE_MATRIX_INTERNAL_HPP
#define VIOLET_ENGINE_MATRIX_INTERNAL_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Violet
{
    extern void             UpdateProjectionMatrices();
    extern const glm::mat4& Get2dProjectionMatrix();
    extern const glm::mat4  Get2dTransformMatrix(const float x, const float y, const float x_scale, const float y_scale, const float angle);
}

#endif // VIOLET_ENGINE_MATRIX_INTERNAL_HPP