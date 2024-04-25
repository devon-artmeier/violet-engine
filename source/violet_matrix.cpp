#include "violet_matrix_internal.hpp"
#include "violet_window.hpp"

namespace Violet
{
    static glm::mat4 projection2D;

    void UpdateProjectionMatrices()
    {
        projection2D = glm::ortho(0.0f, static_cast<float>(GetWindowWidthPixels()),
                                  static_cast<float>(GetWindowHeightPixels()), 0.0f);
    }

    const glm::mat4& Get2dProjectionMatrix()
    {
        return projection2D;
    }

    const glm::mat4 Get2dTransformMatrix(const Point2D<float> position, const Point2D<float> scale, const float angle)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.0f));
        transform           = glm::rotate(transform, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
        transform           = glm::scale(transform, glm::vec3(scale.x, scale.y, 1.0f));
        return transform;
    }
}