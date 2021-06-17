#include <iostream>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <header/SolMan.hpp>

SolMan::SolMan(const char* _title_, int _position_x_, int _position_y_, 
			   int _width_, int _height_, bool _fullscreen_) {
	/*  Intialize Variable */
	title      = _title_;
	position_x = _position_x_;
	position_y = _position_y_;
	width      = _width_;
	height     = _height_;
	fullscreen = _fullscreen_;

	/* Init SDL2 */
	/* Check fullscreen */
	int flags = 0;
	if(fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    /* Initialize SDL2  and check it's have error*/
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0) {
    	/* Intialize window and check it's have error */
    	window = SDL_CreateWindow(title.c_str(), position_x, position_y, width, height, flags);
    	if(!window) haveError = true;

    	/* Intialize renderer and check it's have error */
    	renderer = SDL_CreateRenderer(window, -1, 0);
    	if(!renderer) haveError = true;
    } else {
    	haveError = true;
    }
}

void SolMan::SetBackgroundColor(int R, int G, int B, int A) {
	/* Check renderer and set background color */
	if(renderer) {
		SDL_SetRenderDrawColor(renderer, R, G, B, A);
	}
}

void SolMan::clean() {
	/* Destory window or another name it's clean */
	SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}