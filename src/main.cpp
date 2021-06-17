/* C++ */
#include <iostream>

/* SDL2 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/* Header */
#include <header/SolMan.hpp>
#include <header/SolMain.hpp>
#include <header/Settings.hpp>

int main(int argc, const char* argv[]) {
	SolMan S_main("SolMan", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
				  SCREEN_WIDTH, SCREEN_HEIGHT, false);
	S_main.SetBackgroundColor(144, 201, 120, 0);
	S_main.run<SolMain>();
	S_main.clean();
	{
		(void)argc;
		(void)argv;
	}
	return 0;
}