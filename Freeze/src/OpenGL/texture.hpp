#include "shader.hpp"


class Texture{
public:
    static int m_Count;
    Texture(const std::string& texPath, const std::string& samplerName, ShaderProgram* shader_ptr);
    ~Texture();
    void Bind(unsigned int slot) const;
    void Unbind() const;
private:
    unsigned int m_RendererID;
    int m_Width, m_Height, m_Channels;
    ShaderProgram* m_ShaderPtr;
    unsigned char* LoadTexture(const std::string& path) ;
    void CreateTexture(const std::string& samplerName);
};
