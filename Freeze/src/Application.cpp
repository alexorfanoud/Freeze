#include "glad/glad.h"

#include "Application.hpp"
#include "Core.hpp"
#include "spdlog/spdlog.h"

#include "math/math.hpp"

#include "OpenGL/attributeLayout.hpp"
#include "OpenGL/vertexArray.hpp"
#include "OpenGL/vertexBuffer.hpp"
#include "OpenGL/indexBuffer.hpp"
#include "OpenGL/shader.hpp"
#include "OpenGL/time.hpp"
#include "OpenGL/misc.hpp"
#include "OpenGL/cameraController.hpp"

#include "MeshManager.hpp"

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
        std::vector<glm::vec3> centers ;
        float res = 5.0f;
        float length = 0.05f;
        glm::vec3 steps = glm::vec3(0.02f);

        for (float x = -res/2.0f; x < res/2.0f; x += steps.x)
        {
                for (float z = -res/2.0f; z < res/2.0f; z += steps.z)
                {
                    centers.emplace_back(Graphs::ripple(x, z));
                }
        }

        const auto& [vertices, indices] = MeshManager::CreateCubesData(centers.size(), length, centers);
        
        CameraController camera;
        VertexArray VAO;
        VAO.Bind();
        VertexBuffer VBO;
        VBO.Bind();
        VBO.AddData<float>(vertices, 8 * centers.size());

        IndexBuffer IBO;
        IBO.Bind();
        IBO.AddData<unsigned int>(indices, 36 * centers.size());

        AttributeLayout layout;
        layout.AddAttribute<float>(3);
        VAO.AddLayout(layout);
    
        
        ShaderProgram shader("Freeze/src/resources/shaders/basic/vertex.glsl", "Freeze/src/resources/shaders/basic/fragment.glsl");
        shader.Bind();
        shader.SetUniform1f("resolution", res);

        
        Time time;
        float rotation = 0.0f;
            while (m_Running)
            {
                m_Window->Update(); 
                float delta = time.DeltaTime();
                camera.Update(delta);
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::rotate(model, glm::radians(rotation++), glm::vec3(0.0f, 1.0f, 0.0f));
                shader.SetMVP(model, camera.GetViewMatrix(), glm::perspective(glm::radians(50.0f), FZ_DEFAULT_WINDOW_WIDTH/FZ_DEFAULT_WINDOW_HEIGHT, 0.1f, 300.0f));
                shader.SetUniform1f("time", float(glfwGetTime()));
                glCall(glDrawElements(GL_TRIANGLES, 36 * centers.size(), GL_UNSIGNED_INT, nullptr));
                
            }
        }
    void Application::Init(){
        SetEventListeners();
        bool status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        ASSERT(status, "Failed to initialize GLAD");
    }

} // namespace Freeze