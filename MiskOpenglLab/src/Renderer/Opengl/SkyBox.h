#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <Shaders/Shader.h>
#include <glm/glm.hpp>

namespace Misk {

	class Skybox
	{
	public:
		Skybox() {};
		void init();
		
		void loadCubemap(std::string skyboxName, std::vector<std::string> faces);
		void renderSkybox(std::string skyboxName, glm::mat4 projection, glm::mat4 view);
		~Skybox();

	private:
		std::unordered_map<std::string, unsigned int> m_SkyboxTextureId;
		Shader m_Shader;
		GLuint m_VAO;
	};
}