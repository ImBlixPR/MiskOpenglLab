#include "mkpch.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <iostream>


#include "Application.h"
#include "Game/Game.h"


int main() {
	Misk::Log::init();

	MK_INFO("Its working");

	
	Misk::Application* game = new Game();
	game->run();
	delete game;



	return 0;
}