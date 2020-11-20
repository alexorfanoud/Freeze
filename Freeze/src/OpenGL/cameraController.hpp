#pragma once

#include "Core.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include "EventSystem/KeyEvent.hpp"
#include "EventSystem/MouseEvent.hpp"


#include "EventSystem/EventHandler.hpp"
namespace Freeze
{
    struct Directions {
        Directions(float f = 0.0f, float b = 0.0f, float r = 0.0f, float l = 0.0f) : front(f), back(b), right(r), left(l) {};
        inline void Reset() { front = back = right = left = 0.0f; }
        float front, back, right, left;
    };

    class CameraController
    {
    public:
        CameraController(
            float moveSpeed = FZ_DEFAULT_CAM_MOVESPEED,
            float senseX = FZ_DEFAULT_SENS_X, float senseY = FZ_DEFAULT_SENS_Y,
            float yaw = -90.0f, float pitch = 0.0f,
            glm::vec3 camPos = glm::vec3(0.0f,0.0f,3.0f), glm::vec3 camFront = glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f),
            glm::vec2 mousePos = glm::vec2(0.0f, 0.0f));

        inline glm::mat4 GetViewMatrix() const { return glm::lookAt( m_CameraPos, m_CameraPos + m_CameraFront, m_WorldUp); };
        void Update(float deltaTime);

    private:
        float m_DeltaTime;
        float m_SenseX, m_SenseY;
        float m_MoveSpeed;
        float m_Yaw, m_Pitch;
        glm::vec3 m_CameraPos, m_CameraFront, m_WorldUp;
        glm::vec2 m_MousePos;
        Directions m_MoveDirections;

    private:
        void Init();
        void UpdatePosition();
        void UpdateRotation();
        bool OnKeyPress(KeyPressedEvent& ev);
        bool OnKeyRelease(KeyReleasedEvent& ev);
        bool OnMouseMove(MouseMoveEvent& ev);
    };
} // namespace Freeze
