#pragma once

#include <glm/glm.hpp>

#include "Shaders/Shader.h"
#include "Renderer/Opengl/Buffers.h"
#include "Core/Timestep.h"

namespace Misk {

	class Grid {
	public:
		Grid();
		void render(glm::mat4 projection, glm::vec3 cameraPostion, glm::mat4 view, float thikness);
		~Grid();
		void init();
	private:
		static glm::vec3 m_Vertices[6];
		static int m_Indices[6];
		static const char* vertexShader;
		static const char* fragmentShader;

		Shader* m_Shader;
		unsigned int m_VAO;
		VertexBuffer m_VBO;
		IndexBuffer m_EBO;
		
	};
}