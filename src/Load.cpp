/* C++ */
#include <iostream>
#include <string>

/* SDL2 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/* Header */
#include <header/Load.hpp>

SDL_Texture* Load::LoadTexture(std::string texture, SDL_Renderer* renderer) {
	/* Script Texture Manager For Load */
    SDL_Surface* tempSurface = IMG_Load(texture.c_str());
    SDL_Texture* tex         = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    return tex;
}

float Load::get_width(std::string texture) {
	/* Script Get Width */
	float return_number = 0;
    SDL_Surface* tempSurface = IMG_Load(texture.c_str());
    return_number = tempSurface->w;
    SDL_FreeSurface(tempSurface);
    return return_number;
}

float Load::get_height(std::string texture) {
	/* Script Get Height */
	float return_number = 0;
    SDL_Surface* tempSurface = IMG_Load(texture.c_str());
    return_number = tempSurface->h;
    SDL_FreeSurface(tempSurface);
    return return_number;
}