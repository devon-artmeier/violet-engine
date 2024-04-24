#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "violet_matrix_internal.hpp"
#include "violet_window.hpp"

namespace Violet
{
    static glm::mat4 projection2D;

    void UpdateProjection()
    {
        projection2D = glm::ortho(0.0f, static_cast<float>(GetWindowWidthPixels()),
                                  static_cast<float>(GetWindowHeightPixels()), 0.0f);
    }

    const float* const Get2dProjection()
    {
        return glm::value_ptr(projection2D);
    }
}