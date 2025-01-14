#include "mkpch.h"
#include "SkyBox.h"

#include "Renderer/Opengl/Buffers.h"
#include "stb_image.h"


namespace SkyboxProp {
	const char* vertShader = R"(
	#version 400
	layout (location = 0) in vec3 aPos;

	out vec3 TexCoords;

	uniform mat4 projection;
	uniform mat4 view;

	void main()
	{
		TexCoords = aPos;
		gl_Position = projection * view * vec4(aPos, 1.0);
	}  
)";

	const char* fragShader = R"(
	#version 400
	out vec4 FragColor;

	in vec3 TexCoords;

	uniform samplerCube skybox;

	void main()
	{    
		FragColor = texture(skybox, TexCoords);
	} 
)";

    float skyboxVertices[] = {
        // positions          
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };
};

namespace Misk {

	void Skybox::init()
	{
		
		m_Shader.directInit(SkyboxProp::vertShader, SkyboxProp::fragShader);

        VertexBuffer m_VBO;

        glGenVertexArrays(1, &this->m_VAO);
        m_VBO.GenBuffer();


        glBindVertexArray(this->m_VAO);

        // Vertex buffer object
        m_VBO.SetData(&SkyboxProp::skyboxVertices, sizeof(SkyboxProp::skyboxVertices));

        // Element buffer object
       // m_EBO.SetData(&m_Indices[0], sizeof(Grid::m_Indices));

        // Vertex positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, (void*)0);

        glBindVertexArray(0);
	}


    void Skybox::loadCubemap(std::string skyboxName, std::vector<std::string> faces)
    {

        //if (m_SkyboxTextureId.empty())
        //{
        //    // The unordered_map is empty
        //    MK_CORE_ASSERT(false, "there is no skybox are add!");
        //    return;
        //}

        auto it = m_SkyboxTextureId.find(skyboxName);
        if (it != m_SkyboxTextureId.end() && it->second == 0)
        {
            // The vector exists and is not empty
            MK_CORE_ASSERT(false, "the {0} skybox do not exist!", skyboxName);
            return;
        }

        const std::string basePath = "Media/resources/skyboxs/";


        unsigned int textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

        int width, height, nrChannels;

        for (unsigned int i = 0; i < faces.size(); i++)
        {
            std::string fullPath = basePath + faces[i];
            unsigned char* data = stbi_load(fullPath.c_str(), &width, &height, &nrChannels, 0);
            if (data)
            {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                    0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
                );
                stbi_image_free(data);
            }
            else
            {
                std::cout << "Cubemap tex failed to load at path: " << fullPath << std::endl;
                stbi_image_free(data);
            }
        }
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        m_SkyboxTextureId[skyboxName] = textureID;

    }

    void Skybox::renderSkybox(std::string skyboxName, glm::mat4 projection, glm::mat4 view)
    {
        glDepthMask(GL_FALSE);
        m_Shader.use();
        // ... set view and projection matrix
        m_Shader.setMat4f("projection", projection);
        glm::mat4 cubeView = glm::mat4(glm::mat3(view));
        m_Shader.setMat4f("view", cubeView);
        glBindVertexArray(m_VAO);
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_SkyboxTextureId[skyboxName]);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glDepthMask(GL_TRUE);

    }
    Skybox::~Skybox()
    {
       
    }
}

