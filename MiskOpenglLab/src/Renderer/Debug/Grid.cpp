#include "mkpch.h"
#include "Grid.h"


#include <glm/gtc/matrix_transform.hpp>

namespace Misk {

    const char* Grid::vertexShader = R"(#version 400 

    layout (location = 0) in vec3 aPos;

    uniform mat4 projection;
    uniform vec3 cameraPos;

    out vec3 FragPos;  


    void main()
    {
        vec3 vPos3 = aPos;
        
        vPos3.x += cameraPos.x;
        vPos3.z += cameraPos.z;

        vec4 vPos4 = vec4(vPos3, 1.0);
        gl_Position = projection * vPos4;
    }
    )";

    const char* Grid::fragmentShader = R"(#version 400 

    out vec4 FragColor;

    void main()
    {
        FragColor = vec4(1.0, 0.0, 0.0, 1.0);
    }
    )";

    glm::vec3 Grid::m_Vertices[6] = {
        glm::vec3(-1.0, 0.0, 1.0),
        glm::vec3(1.0, 0.0, -1.0),
        glm::vec3(1.0, 0.0, 1.0), //end of first tringale
        glm::vec3(1.0, 0.0, -1.0),
        glm::vec3(-1.0, 0.0, 1.0),
        glm::vec3(-1.0, 0.0, -1.0)
    };
    int Grid::m_Indices[6] = { 0, 2, 1, 2, 0, 3 };

    Grid::Grid()
    {
        m_Shader = new Shader();
        MK_CORE_ASSERT(m_Shader, "Shader is not initilize!");
        m_Shader->init("src/Shaders/glsl/grid.vert", "src/Shaders/glsl/grid.frag");
    }

    void Grid::render(glm::mat4 projection, glm::vec3 cameraPosition, glm::mat4 view, float thikness)
    {
        m_Shader->use();
        m_Shader->setMat4f("projection", projection);
        m_Shader->setVec3f("cameraPos", cameraPosition);
        m_Shader->setMat4f("view", view);
        m_Shader->setFloat("gGridCellSize", thikness);
        
        
        glm::mat4 model(1.0f);
        model = glm::scale(model, glm::vec3(35.0f, 0.0f, 35.0f));
        m_Shader->setMat4f("model", model);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        MK_CORE_ASSERT(this->m_VAO, "the buffer not initilize!");
        glBindVertexArray(this->m_VAO);
        //glDrawArrays(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }

    Grid::~Grid()
    {
        delete m_Shader;
    }

    void Grid::init()
    {
        glGenVertexArrays(1, &this->m_VAO);
        m_VBO.GenBuffer();
        m_EBO.GenBuffer();


        glBindVertexArray(this->m_VAO);

        // Vertex buffer object
        m_VBO.SetData(&m_Vertices[0], sizeof(Grid::m_Vertices));

        // Element buffer object
       // m_EBO.SetData(&m_Indices[0], sizeof(Grid::m_Indices));

        // Vertex positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

        glBindVertexArray(0);
    }
}
