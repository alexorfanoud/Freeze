#include "glm/glm.hpp"

namespace Graphs
{
    auto ripple = [](float x, float z) { return glm::vec3(x, glm::sin(5 * (glm::pow(x, 2) + glm::pow(z, 2))) / 5, z); };
    auto x3y3 = [](float x, float z) { return glm::vec3(x, glm::pow(x,3) + glm::pow(z,3) ,z); };
    auto bumps = [](float x, float z) { return glm::vec3(x, glm::sin(x) + glm::sin(z), z); };
};