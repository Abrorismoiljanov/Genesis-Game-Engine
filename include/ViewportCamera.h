#include "glm/glm.hpp"

struct Camera {
    glm::vec3 Position;
    glm::vec3 Rotation;
    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix(float aspectRatio);
};

