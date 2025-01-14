#pragma once


#include <string>
#include <glm/glm.hpp>




#include <glad/glad.h>

namespace Misk {

	class Shader 
	{
	public:
		Shader();

		Shader(const char* vShaderPath, const char* fShaderPath);


		void init(const char* vShaderPath, const char* fShaderPath) ;
		void directInit(const char* vShaderCode, const char* fShaderCode);
		void use() ;

		void clearShader();
		~Shader();


	public:
		//uniform set functions
		void setBool(const std::string& name, bool value) const ;
		void setInt(const std::string& name, int value) const ;
		void setFloat(const std::string& name, float value) const ;
		void setVec3f(const std::string& name, glm::vec3 value) const ;
		void setVec4f(const std::string& name, glm::vec4 value) const ;
		void setMat4f(const std::string& name, glm::mat4 value) const ;
		void setMat3f(const std::string& name, glm::mat3 value) const ;


	private:

		std::string vertexCode;
		std::string fragmentCode;

		unsigned int shaderId;

	private:
		void addShader(std::string shaderCode, GLenum shaderType);

		std::string loadShaderCode(const char* path);
	};

}
