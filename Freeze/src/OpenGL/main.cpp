#include <iostream>
#include <math.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image/stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.hpp"
#include "misc.hpp"
#include "texture.hpp"
#include "cameraController.hpp"
#include "vertexBuffer.hpp"
#include "indexBuffer.hpp"
#include "vertexArray.hpp"
#include "attributeLayout.hpp"
#include "renderer.hpp"
#include "time.hpp"

int main()
{

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
    float vertices2[] = {
        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f,     //bottom left
        -0.5f, 0.5f, 0.0f,      0.0f, 1.0f,     //top left
        0.5f, 0.5f, 0.0f,       1.0f, 1.0f,     //top right
        0.5f, -0.5f, 0.0f,      1.0f, 0.0f     //bottom right
    };
    unsigned int indices[] = {
    0, 1, 2,
    2, 3, 0
};

    Renderer renderer;
    if(renderer.Setup() == -1) return -1;

    CameraController mainCamera(renderer.GetWindow());

    VertexArray VAO;
    VAO.Bind();

    VertexBuffer VBO;
    VBO.Bind();
    VBO.AddData(sizeof(vertices), vertices, 36);


    IndexBuffer IBO;
    IBO.Bind();
    IBO.AddData(sizeof(indices), indices, 6);

    AttributeLayout layout;
    layout.AddAttribute<float>(3);
    layout.AddAttribute<float>(3);
    VAO.AddLayout(layout);
  
    
    ShaderProgram shaderTarget("../resources/shaders/lighting_0/target/vertex.glsl", "../resources/shaders/lighting_0/target/fragment.glsl");
    ShaderProgram shaderSource("../resources/shaders/lighting_0/source/vertex.glsl",  "../resources/shaders/lighting_0/source/fragment.glsl");

    
    Time time;

    while(!glfwWindowShouldClose(renderer.GetWindow()))
    {   
        if(glfwGetKey(renderer.GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS){
            glfwSetWindowShouldClose(renderer.GetWindow(), true);
        }
        renderer.Clear();
        mainCamera.Update(time.DeltaTime(), renderer.GetWindow());
        // glm::vec3 lightPos = glm::vec3(-1.2f, 0.0f, -1.0f);
        float radius = 3.0f;
        glm::vec3 lightPos = glm::vec3(cos(glfwGetTime()), 0, sin(glfwGetTime())) * radius;

        shaderTarget.Bind();
        {
            shaderTarget.SetMVP(glm::mat4(1.0f), mainCamera.GetViewMat());
            shaderTarget.SetUniform4f("objectColor", 1.0f, 0.5f, 0.31f, 1.0f);
            shaderTarget.SetUniform4f("lightColor", 1.0f, 1.0f, 1.0f, 1.0f);
            shaderTarget.SetUniformv3f("lightPos", lightPos);
            shaderTarget.SetUniformv3f("viewPos", mainCamera.GetPosition());
            renderer.Draw(VAO,VBO);
        }
        shaderSource.Bind();
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, lightPos);
            model = glm::scale(model, glm::vec3(0.5f,0.5f, 0.5f));
            shaderSource.SetMVP(model, mainCamera.GetViewMat());
            renderer.Draw(VAO,VBO);
        }

        glfwSwapBuffers(renderer.GetWindow());
        glfwPollEvents();    
    }
    return 0;
}

