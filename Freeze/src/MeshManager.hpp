#pragma once 

#include "glm/glm.hpp"
#include <pch.hpp>

namespace Freeze {
    class MeshManager {
    public:
        static MeshManager& Get() { 
            static MeshManager instance;
            return instance;
        }
        static std::pair<std::vector<float>, std::vector<unsigned int>> CreateCubesData(unsigned int count, float length, std::vector<glm::vec3> centers);
    private:
        static std::vector<float> CreateCubeVerticesImpl(glm::vec3 center, float length);
        static std::vector<uint32_t> CreateCubeIndicesImpl();

        static std::vector<float> CreateCubeVertices(uint32_t count, float length, std::vector<glm::vec3> centers );

        static std::vector<unsigned int> CreateCubeIndices(uint32_t count);
    };
}