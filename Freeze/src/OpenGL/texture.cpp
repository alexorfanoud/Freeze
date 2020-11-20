#include "Core.hpp"

#include "texture.hpp"
#include "misc.hpp"
#include "stb_image/stb_image.h"

#include <glad/glad.h>

namespace Freeze
{

    int Texture::m_Count = 0;

    Texture::Texture(const std::string &texPath, const std::string &samplerName, ShaderProgram *shader_ptr) : m_RendererID(0), m_Width(0), m_Height(0), m_Channels(0), m_ShaderPtr(shader_ptr)
    {
        ASSERT(m_Count < 16, "Texture count exceeds limit of 16.");
        CreateTexture(samplerName);
        LoadTexture(texPath);
    }

    Texture::~Texture()
    {
        glCall(glDeleteTextures(1, &m_RendererID));
        m_Count--;
    }

    void Texture::Bind(unsigned int slot) const
    {
        ASSERT(slot < 16, "Only 16 slots available");
        glCall(glActiveTexture(GL_TEXTURE0 + slot));
        glCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
    }

    void Texture::Unbind() const
    {
        glCall(glBindTexture(GL_TEXTURE_2D, 0));
    }

    void Texture::CreateTexture(const std::string &samplerName)
    {
        glCall(glGenTextures(1, &m_RendererID));
        Bind(m_Count);

        m_ShaderPtr->SetUniform1i(samplerName, m_Count);
        m_Count++;

        glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
        glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT););
        glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    }

    unsigned char *Texture::LoadTexture(const std::string &path)
    {
        stbi_set_flip_vertically_on_load(true);
        std::string postfix = path.substr(path.size() - 3, 3);
        unsigned int mode = postfix == "png" ? GL_RGBA : GL_RGB;
        unsigned char *data = stbi_load(path.c_str(), &m_Width, &m_Height, &m_Channels, 0);
        if (!data)
            std::cout << "Could not load texture: " << path << std::endl;
        else
        {
            glCall(glTexImage2D(GL_TEXTURE_2D, 0, mode, m_Width, m_Height, 0, mode, GL_UNSIGNED_BYTE, data));
            glCall(glGenerateMipmap(GL_TEXTURE_2D));
            stbi_image_free(data);
        }
        return data;
    }
} // namespace Freeze