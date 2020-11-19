#pragma once

#include "../Core.hpp"
#include "pch.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ShaderProgram{
public:
    ShaderProgram(const char* vertexFilepath, const char* fragmentFilepath);
    ~ShaderProgram();
    void Bind() const;
    void Unbind() const;
    void SetUniformMatrix4fv(const std::string& name, glm::mat4 m);
    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)  ;
    void SetUniform3f(const std::string& name, float v0, float v1, float v2)  ;
    void SetUniformv3f(const std::string& name, const glm::vec3& v3);
    void SetUniformv4f(const std::string& name, const glm::vec4& v4);
    void SetUniform1f(const std::string& name, float v)  ;
    void SetUniform1i(const std::string& name, int v) ;
    void SetMVP(
        const glm::mat4& model = glm::mat4(1.0f),
        const glm::mat4& view = glm::mat4(1.0f), 
        const glm::mat4& proj = glm::perspective(glm::radians(50.0f), 1.0f, 0.1f, 100.0f));
    
private:
    unsigned int m_RendererID;
    std::unordered_map<std::string,int> m_Locations;
    void CreateShader(const char* vertexFilepath, const char* fragmentFilepath) const ;
    std::string ParseShader(const char* filepath) const ;
    unsigned int CompileShader(const std::string& source, unsigned int shaderType) const;
};