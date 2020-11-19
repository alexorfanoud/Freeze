#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

const float D_SENSX = 10.0f;
const float D_SENSY = 10.0f;
const float D_MOVESPEED = 10.0f;
const float D_YAW = -90.0f, D_PITCH = 0.0F;
const glm::vec3 D_CAMPOS = glm::vec3(0.0f, 0.0f, 3.0f);
const glm::vec3 D_CAMFRONT = glm::vec3(0.0f, 0.0f, -1.0f);
const glm::vec3 D_WORLDUP = glm::vec3(0.0f, 1.0f, 0.0f);
const glm::vec2 D_LASTMOUSEPOS = glm::vec2(300.0f, 400.0f);
const glm::vec2 D_MOUSEPOS = glm::vec2(300.0f, 400.0f);

struct Directions{
    float front = 0, back = 0, right = 0, left = 0;
    Directions(float f = 0, float b = 0, float r = 0, float l = 0) : front(f), back(b), right(r), left(l) {}
};

class CameraController{
public:

    CameraController(
        GLFWwindow* window,
        float moveSpeed = D_MOVESPEED, float senseX = D_SENSX, float senseY = D_SENSY, float yaw = D_YAW, float pitch = D_PITCH,
        glm::vec3 camPos = D_CAMPOS, glm::vec3 camFront = D_CAMFRONT, glm::vec3 worldUp = D_WORLDUP, 
        glm::vec2 mousePos = D_MOUSEPOS, glm::vec2 lastMousePos = D_LASTMOUSEPOS);

    void Update(float deltaTime, GLFWwindow* window);
    inline glm::mat4 GetViewMat() const { return glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_worldUp); }
    inline void ResetMouse() { m_lastMousePos = m_mousePos; }
    inline void SetMousePos(glm::vec2 mousePos) { m_mousePos = mousePos; }
    inline void SetMoveDirections(Directions moveDir = {0.0f, 0.0f, 0.0f, 0.0f}) { m_moveDirections = moveDir; }
    inline glm::vec3 GetPosition() const { return m_cameraPos; };
    
private:
    float m_SensX, m_SensY;
    float m_moveSpeed;
    float m_yaw, m_pitch;
    glm::vec3 m_cameraPos, m_cameraFront, m_worldUp;
    glm::vec2 m_mousePos, m_lastMousePos;
    Directions m_moveDirections;
    void UpdatePosition(float deltaTime, GLFWwindow* window);
    void UpdateRotation(float deltaTime, GLFWwindow* window);
};













