#include "shader.hpp"
#include "misc.hpp"
#include <glad/glad.h>

void ShaderProgram::Bind() const {
    glCall(glUseProgram(m_RendererID));
}

void ShaderProgram::Unbind() const {
    glCall(glUseProgram(0));
}

void ShaderProgram::SetUniformMatrix4fv(const std::string& name, glm::mat4 m) {
    Bind();
    if( m_Locations.find(name) != m_Locations.end() ){
        int loc = m_Locations[name];
        if(loc == -1) return;
        glCall(glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(m)));
    }
    else {
        glCall(int loc = glGetUniformLocation(m_RendererID, name.c_str()));
        if(loc == -1 ) std::cout << "Could not find uniform " + name + '.' << std::endl;
        glCall(glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(m)));
        m_Locations[name] = loc;
    }
}

void ShaderProgram::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
    Bind();
    if( m_Locations.find(name) != m_Locations.end() ){
        int loc = m_Locations[name];
        if(loc == -1) return;
        else glCall(glUniform4f(loc, v0, v1, v2, v3));
    }
    else {
        glCall(int loc = glGetUniformLocation(m_RendererID, name.c_str()));
        if(loc == -1 ) std::cout << "Could not find uniform " + name + '.' << std::endl;
        else glCall(glUniform4f(loc, v0, v1, v2, v3));
        m_Locations[name] = loc;
    }
}

void ShaderProgram::SetUniform3f(const std::string& name, float v0, float v1, float v2) {
    Bind();
    if( m_Locations.find(name) != m_Locations.end() ){
        int loc = m_Locations[name];
        if(loc == -1) return;
        else glCall(glUniform3f(loc, v0, v1, v2));
    }
    else {
        glCall(int loc = glGetUniformLocation(m_RendererID, name.c_str()));
        if(loc == -1 ) std::cout << "Could not find uniform " + name + '.' << std::endl;
        else glCall(glUniform3f(loc, v0, v1, v2));
        m_Locations[name] = loc;
    }
}

void ShaderProgram::SetUniformv3f(const std::string& name, const glm::vec3& v3){
    Bind();
    if( m_Locations.find(name) != m_Locations.end() ){
        int loc = m_Locations[name];
        if(loc == -1) return;
        else glCall(glUniform3f(loc, v3.x, v3.y, v3.z));
    }
    else {
        glCall(int loc = glGetUniformLocation(m_RendererID, name.c_str()));
        if(loc == -1 ) std::cout << "Could not find uniform " + name + '.' << std::endl;
        else glCall(glUniform3f(loc, v3.x, v3.y, v3.z));
        m_Locations[name] = loc;
    }
}

void ShaderProgram::SetUniformv4f(const std::string& name, const glm::vec4& v4){
    Bind();
    if( m_Locations.find(name) != m_Locations.end() ){
        int loc = m_Locations[name];
        if(loc == -1) return;
        else glCall(glUniform4f(loc, v4.x, v4.y, v4.z, v4.w));
    }
    else {
        glCall(int loc = glGetUniformLocation(m_RendererID, name.c_str()));
        if(loc == -1 ) std::cout << "Could not find uniform " + name + '.' << std::endl;
        else glCall(glUniform4f(loc, v4.x, v4.y, v4.z, v4.w));
        m_Locations[name] = loc;
    }
}

void ShaderProgram::SetUniform1f(const std::string& name, float v) {
    Bind();
    if( m_Locations.find(name) != m_Locations.end() ){
        int loc = m_Locations[name];
        if(loc == -1) return;
        else glCall(glUniform1f(loc, v));
    }
    else {
        glCall(int loc = glGetUniformLocation(m_RendererID, name.c_str()));
        if(loc == -1 ) std::cout << "Could not find uniform " + name + '.' << std::endl;
        else glCall(glUniform1f(loc, v));
        m_Locations[name] = loc;
    }
}

void ShaderProgram::SetUniform1i(const std::string& name, int v) {
    Bind();
    if( m_Locations.find(name) != m_Locations.end() ){
        int loc = m_Locations[name];
        if(loc == -1) return;
        else glCall(glUniform1i(loc, v));
    }
    else {
        glCall(int loc = glGetUniformLocation(m_RendererID, name.c_str()));
        if(loc == -1 ) std::cout << "Could not find uniform " + name + '.' << std::endl;
        else glCall(glUniform1i(loc, v));
        m_Locations[name] = loc;
    }
}

void ShaderProgram::SetMVP(
    const glm::mat4& model ,
    const glm::mat4& view , 
    const glm::mat4& projection ){
        SetUniformMatrix4fv("model", model);
        SetUniformMatrix4fv("view", view);
        SetUniformMatrix4fv("projection", projection);
    }

ShaderProgram::ShaderProgram(const char* vertexFilepath, const char* fragmentFilepath) : m_RendererID(0) {
    glCall(m_RendererID = glCreateProgram());
    CreateShader(vertexFilepath, fragmentFilepath);
}

ShaderProgram::~ShaderProgram(){
    glCall(glDeleteProgram(m_RendererID));
}

void ShaderProgram::CreateShader(const char* vertexFilepath, const char* fragmentFilepath) const {

    std::string vertexSource = ParseShader(vertexFilepath);
    std::string fragmentSource = ParseShader(fragmentFilepath);

    unsigned int vs = CompileShader(vertexSource, GL_VERTEX_SHADER);
    unsigned int fs = CompileShader(fragmentSource, GL_FRAGMENT_SHADER);

    glCall(glAttachShader(m_RendererID, vs));
    glCall(glAttachShader(m_RendererID, fs));
    glCall(glLinkProgram(m_RendererID));

    glCall(glDeleteShader(vs));
    glCall(glDeleteShader(fs));
}

std::string ShaderProgram::ParseShader(const char* filepath) const{
    std::ifstream stream(filepath);
    ASSERT(stream.is_open(), "Could not open file, filepath should be relative to executable location!");
    std::string line;
    std::string source;
    while(std::getline(stream, line)){
        if(line.find("//") == std::string::npos)
            source += line + '\n';
    };
    stream.close();
    return source;
    
}

unsigned int ShaderProgram::CompileShader(const std::string& source, unsigned int shaderType) const{
    glCall(unsigned int shader = glCreateShader(shaderType));
    const char* src = source.c_str();

    glCall(glShaderSource(shader, 1, &src, nullptr));
    glCall(glCompileShader(shader));

    int success;
    char infoLog[512];
    glCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &success));
    if(!success){
        glCall(glGetShaderInfoLog(shader, 512, nullptr, infoLog));
        std::cout << "[ERROR::SHADER::COMPILE::" << (shaderType==35633 ? "VERTEX" : "FRAGMENT") << "] " << std::endl << infoLog ;
        return 0;
    }

    return shader;
}