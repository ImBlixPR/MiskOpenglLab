#include "mkpch.h"

#include <iostream>


#include "Application.h"


int main() {
	Misk::Log::init();

	MK_INFO("Its working");

	
	Application* game = new Application();
	game->run();
	delete game;



	return 0;
}