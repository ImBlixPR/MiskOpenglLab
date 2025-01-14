#pragma once
#include <filesystem>

namespace Misk {
	class Texture {
	public:
		unsigned int textureId;
		std::filesystem::path mFilePath;

		virtual void loadTexture(const char* path);

		virtual void applyTexture(unsigned int textureUnit);
	};

}