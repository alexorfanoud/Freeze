#include "pch.hpp"

#include "cameraController.hpp"
#include "Core.hpp"

namespace Freeze
{
    bool CameraController::OnMouseMove(MouseMoveEvent& ev){
        static bool firstMove = true;

        glm::vec2 CurrentMousePos = glm::vec2(ev.GetXPos(), ev.GetYPos());
        glm::vec2 PositionDif = CurrentMousePos - m_MousePos;
        m_MousePos = CurrentMousePos;

        if(firstMove) {
            firstMove = false;
            return FZ_EVENT_RESOLVED;
        }
        
        m_Yaw += m_SenseX * PositionDif.x * m_DeltaTime;
        m_Pitch -= m_SenseY * PositionDif.y * m_DeltaTime;
        if(m_Pitch > FZ_PITCH_MAX) m_Pitch = FZ_PITCH_MAX;
        if(m_Pitch < FZ_PITCH_MIN) m_Pitch = FZ_PITCH_MIN;

        return FZ_EVENT_RESOLVED;
    };

    bool CameraController::OnKeyPress(KeyPressedEvent& ev){
        if(ev.GetKeyCode() == GLFW_KEY_W) m_MoveDirections.front = 1;
        if(ev.GetKeyCode() == GLFW_KEY_S) m_MoveDirections.back = 1;
        if(ev.GetKeyCode() == GLFW_KEY_D) m_MoveDirections.right = 1;
        if(ev.GetKeyCode() == GLFW_KEY_A) m_MoveDirections.left = 1;

        return FZ_EVENT_RESOLVED;
    };
    bool CameraController::OnKeyRelease(KeyReleasedEvent& ev){
        if(ev.GetKeyCode() == GLFW_KEY_W)  m_MoveDirections.front = 0;
        if(ev.GetKeyCode() == GLFW_KEY_S)  m_MoveDirections.back = 0;
        if(ev.GetKeyCode() == GLFW_KEY_D)  m_MoveDirections.right = 0; 
        if(ev.GetKeyCode() == GLFW_KEY_A)  m_MoveDirections.left = 0; 

        return FZ_EVENT_RESOLVED;
    };

    CameraController::CameraController(
        float moveSpeed,
        float senseX, float senseY,
        float yaw, float pitch,
        glm::vec3 camPos, glm::vec3 camFront, glm::vec3 worldUp,
        glm::vec2 mousePos) :
        m_MoveSpeed(moveSpeed),
        m_SenseX(senseX), m_SenseY(senseY),
        m_Yaw(yaw), m_Pitch(pitch),
        m_CameraPos(camPos), m_CameraFront(camFront), m_WorldUp(worldUp),
        m_MousePos(mousePos)
        {
            Init();
        }

    void CameraController::UpdatePosition()
    {
        m_CameraPos += m_MoveDirections.front * m_CameraFront * m_MoveSpeed * m_DeltaTime; 
        m_CameraPos -= m_MoveDirections.back * m_CameraFront * m_MoveSpeed * m_DeltaTime;
        m_CameraPos += m_MoveDirections.right * glm::normalize(glm::cross(m_CameraFront, m_WorldUp)) * m_MoveSpeed * m_DeltaTime;
        m_CameraPos -= m_MoveDirections.left * glm::normalize(glm::cross(m_CameraFront, m_WorldUp)) * m_MoveSpeed * m_DeltaTime;
    }
    void CameraController::UpdateRotation()
    {
        m_CameraFront = glm::vec3(
            glm::cos(glm::radians(m_Pitch)) * glm::cos(glm::radians(m_Yaw)),
            glm::sin(glm::radians(m_Pitch)),
            glm::cos(glm::radians(m_Pitch)) * glm::sin(glm::radians(m_Yaw))
        );
    }
    void CameraController::Update(float deltaTime)
    {
        m_DeltaTime = deltaTime;
        UpdateRotation();
        UpdatePosition();
    }
    void CameraController::Init()
    {
        EventHandler::AttachListener<MouseMoveEvent>(BIND_EVENT_FUNC(CameraController::OnMouseMove));
        EventHandler::AttachListener<KeyPressedEvent>(BIND_EVENT_FUNC(CameraController::OnKeyPress));
        EventHandler::AttachListener<KeyReleasedEvent>(BIND_EVENT_FUNC(CameraController::OnKeyRelease));
    }

} // namespace Freeze