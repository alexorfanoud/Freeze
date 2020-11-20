#include "MeshManager.hpp"
#include "pch.hpp"

namespace Freeze{
    std::vector<float> MeshManager::CreateCubeVerticesImpl(glm::vec3 center, float length)
    {
        std::vector<float> vertices(24);
        for(int i = 0; i< 8 ; i++){
            int xsign = i%2 == 0 ? 1 : -1;
            int ysign = (i/2)%2 == 0 ? 1 : -1;
            int zsign = (i/4)%2 == 0 ? 1 : -1;
            vertices[3*i] = (float)center.x + xsign * length / 2.0f;
            vertices[3*i + 1] = (float)center.y + ysign * length / 2.0f;
            vertices[3*i + 2] = (float)center.z + zsign * length / 2.0f;
        }
        return vertices;
    };

    std::vector<uint32_t> MeshManager::CreateCubeIndicesImpl(){
        std::vector<uint32_t> indices = {
            //back face
            0, 1, 2,
            2, 3, 1,
            //front face
            4, 5, 6,
            6, 7, 5,
            //top face
            0, 1, 4,
            4, 5, 1,
            //bottom face
            2, 3, 6,
            6, 7, 3,
            //right face
            0, 2, 4,
            4, 6, 2,
            //left face
            1, 3, 5,
            5, 7, 3
        };
        return indices;
    };
    std::vector<float> MeshManager::CreateCubeVertices(uint32_t count, float length, std::vector<glm::vec3> centers)
    {
        std::vector<float> vertices;
        for (auto &centerPos : centers)
        {
            for (auto &f : CreateCubeVerticesImpl(centerPos, length))
            {
                vertices.emplace_back(f);
            }
        }
        return vertices;
    }

    std::vector<unsigned int> MeshManager::CreateCubeIndices(uint32_t count)
    {
        std::vector<unsigned int> indices;
        auto baseIndices = CreateCubeIndicesImpl();
        for (int i = 0; i < count; i++)
        {
            for (auto& ui : baseIndices)
            {
                indices.emplace_back(ui + i * 8);
            }
        }
        return indices;
    }

    std::pair<std::vector<float>, std::vector<unsigned int>> MeshManager::CreateCubesData(unsigned int count, float length, std::vector<glm::vec3> centers)
    {
        return std::make_pair(CreateCubeVertices(count, length, centers), CreateCubeIndices(count));
    }
}