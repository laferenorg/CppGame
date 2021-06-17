/* C++ */
#include <iostream>
#include <string>

/* SDL2 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/* Header */
#include <header/Load.hpp>
#include <header/Settings.hpp>
#include <header/Bullet.hpp>

Bullet::Bullet(int x, int y, int direction, SDL_Renderer* renderer) {
	std::string path = "assets/img/icons/bullet.png";
	image            = Load::LoadTexture(path, renderer);
	DestR.x          = x;
	DestR.y          = y;
	DestR.w          = Load::get_width(path);
	DestR.h          = Load::get_height(path);
	this->direction  = direction;
}

void Bullet::update() {
	DestR.x += (this->direction * speed);

	if(((DestR.x + 10) < 0) || (DestR.x > SCREEN_WIDTH)) {
		delts = true;
	}
}

void Bullet::draw(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, image, NULL, &DestR);
}