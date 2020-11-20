#include "glad/glad.h"

#include "Application.hpp"
#include "Core.hpp"
#include "spdlog/spdlog.h"

#include "OpenGL/attributeLayout.hpp"
#include "OpenGL/vertexArray.hpp"
#include "OpenGL/vertexBuffer.hpp"
#include "OpenGL/indexBuffer.hpp"
#include "OpenGL/shader.hpp"
#include "OpenGL/time.hpp"
#include "OpenGL/misc.hpp"
#include "OpenGL/cameraController.hpp"

namespace Freeze
{
    bool Application::OnWindowClose(WindowCloseEvent& ev){
        m_Running = false;
        return FZ_EVENT_RESOLVED;
    }
    bool Application::OnWindowResize(WindowResizeEvent& ev){
       //TODO handle window resize
        std::cout << ev.GetName() << std::endl;
        return FZ_EVENT_RESOLVED;
    }
    bool Application::OnKeyPress(KeyPressedEvent& ev){
        if(ev.GetKeyCode() == GLFW_KEY_ESCAPE) { m_Running = false; return FZ_EVENT_RESOLVED; }
        return FZ_EVENT_UNRESOLVED;
    }
    void Application::SetEventListeners(){
        EventHandler::AttachListener<WindowCloseEvent>(BIND_EVENT_FUNC(Application::OnWindowClose));
        EventHandler::AttachListener<WindowResizeEvent>(BIND_EVENT_FUNC(Application::OnWindowResize));
        EventHandler::AttachListener<KeyPressedEvent>(BIND_EVENT_FUNC(Application::OnKeyPress));
    }

    Application::Application()
    :m_Running(true),
    m_Window(new Window())
    {
        Init();
    }
    Application::~Application()
    {
        Shutdown();
    }
    void Application::Shutdown()
    {
        delete m_Window;
    }

    void Application::Run()
    {
        //TODO ABSTRACT VISUALS INTO SCENES ?
        spdlog::info("Running...");
        float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    CameraController camera;
    VertexArray VAO;
    VAO.Bind();

    VertexBuffer VBO;
    VBO.Bind();
    VBO.AddData(sizeof(vertices), vertices, 36);

    AttributeLayout layout;
    layout.AddAttribute<float>(3);
    layout.AddAttribute<float>(3);
    VAO.AddLayout(layout);
  
    
    ShaderProgram shader("../Freeze/src/resources/shaders/basic/vertex.glsl", "../Freeze/src/resources/shaders/basic/fragment.glsl");
    shader.Bind();

    
    Time time;

        while (m_Running)
        {
            m_Window->Update(); 
            float delta = time.DeltaTime();
            camera.Update(delta);
            shader.SetMVP(glm::mat4(1.0f), camera.GetViewMatrix(), glm::perspective(glm::radians(50.0f), 1.0f, 0.1f, 100.0f));
            glCall(glDrawArrays(GL_TRIANGLES, 0, 36));
            
        }
    }

    void Application::Init(){
        SetEventListeners();
        bool status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        ASSERT(status, "Failed to initialize GLAD");
    }

} // namespace Freeze