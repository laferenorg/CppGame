/* C++ */
#include <iostream>
#include <string>
#include <cstring>
#include <vector>

/* SDL2 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/* Header */
#include <header/Load.hpp>
#include <header/Settings.hpp>
#include <header/Explosion.hpp>

Explosion::Explosion(int x, int y, float scale, SDL_Renderer* renderer) {
	/* Intialize variable */
	DestR.x = x;
	DestR.y = y;
	for(int i = 1; i < 6; i++) {
		std::string path = "assets/img/explosion/exp" + std::to_string(i) + ".png";
		images.push_back(Load::LoadTexture(path, renderer));
		DestR.w = Load::get_width(path) * scale;
		DestR.h = Load::get_height(path) * scale;
	}
	image = images[frame_index];
}

void Explosion::update(bool& replace) {
	unsigned int EXPLOSION_SPEED = 4;
	/* Update explosion animation */
	counter += 1;
	if(counter >= EXPLOSION_SPEED) {
        counter = 0;
        frame_index += 1;
        
        /* If the animation is complete then delete the explosion */
        if(frame_index >= ((int)images.size())) {
            delts   = true;
            replace = true;
        } else {
        	image = images[frame_index];
        }
	}
}

void Explosion::draw(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, image, NULL, &DestR);
}