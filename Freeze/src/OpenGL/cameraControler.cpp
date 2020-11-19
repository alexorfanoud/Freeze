#include "pch.hpp"

#include "cameraController.hpp"


CameraController::CameraController(
    GLFWwindow* window,
    float moveSpeed, float senseX , float senseY , float yaw , float pitch ,
    glm::vec3 camPos , glm::vec3 camFront , glm::vec3 worldUp , 
    glm::vec2 mousePos, glm::vec2 lastMousePos ) : 
    m_moveSpeed(moveSpeed), m_SensX(senseX), m_SensY(senseY), m_yaw(yaw), m_pitch(pitch),   
    m_cameraPos(camPos), m_cameraFront(camFront), m_worldUp(worldUp),
    m_mousePos(mousePos), m_lastMousePos(lastMousePos)
    {
        double xpos, ypos;

        glfwGetCursorPos(window, &xpos, &ypos);
        SetMousePos(glm::vec2(xpos, ypos));
        ResetMouse();
    }

void CameraController::Update(float deltaTime, GLFWwindow* window){
    UpdateRotation(deltaTime, window);
    UpdatePosition(deltaTime, window);
}

void CameraController::UpdatePosition(float deltaTime, GLFWwindow* window){

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) m_moveDirections.front = 1;    else m_moveDirections.front = 0;
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) m_moveDirections.back = 1;     else m_moveDirections.back = 0;
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) m_moveDirections.right = 1;    else m_moveDirections.right = 0;
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) m_moveDirections.left = 1;     else m_moveDirections.left = 0;

    if(m_moveDirections.front) m_cameraPos += m_cameraFront * m_moveSpeed * deltaTime;
    if(m_moveDirections.back) m_cameraPos -= m_cameraFront * m_moveSpeed * deltaTime;
    if(m_moveDirections.right) m_cameraPos += glm::normalize(glm::cross(m_cameraFront, m_worldUp)) * m_moveSpeed * deltaTime;
    if(m_moveDirections.left) m_cameraPos -= glm::normalize(glm::cross(m_cameraFront, m_worldUp)) * m_moveSpeed * deltaTime;
}

void CameraController::UpdateRotation(float deltaTime, GLFWwindow* window)
{
    static bool firstMove = true;
    double xpos, ypos;

    glfwGetCursorPos(window, &xpos, &ypos);
    SetMousePos(glm::vec2(xpos,ypos));
    if(firstMove ) {
        if(xpos==m_lastMousePos.x && ypos==m_lastMousePos.y) return;
        ResetMouse(); 
        firstMove = false;
        }
    glm::vec2 mousePosDif;
    mousePosDif = m_mousePos - m_lastMousePos;
    m_yaw += mousePosDif.x * m_SensX * deltaTime;
    m_pitch -= mousePosDif.y * m_SensY * deltaTime;
    m_lastMousePos = m_mousePos;

    m_cameraFront = glm::normalize(
        glm::vec3(
            cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch)),
            sin(glm::radians(m_pitch)),
            sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch))));
}