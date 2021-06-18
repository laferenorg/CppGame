/* C++ */
#include <iostream>
#include <string>

/* SDL2 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/* Header */
#include <header/Load.hpp>
#include <header/Settings.hpp>
#include <header/Grenade.hpp>
#include <header/Explosion.hpp>

Grenade::Grenade(int x, int y, int direction, SDL_Renderer* renderer) {
	std::string path = "assets/img/icons/grenade.png";
	DestR.x          = x;
	DestR.y          = y;
	DestR.w          = Load::get_width(path);
	DestR.h          = Load::get_height(path);
	this->direction  = direction;
	image            = Load::LoadTexture(path, renderer);
}

void Grenade::update(SDL_Renderer* renderer) {
	/* Update Section Explosion */
	{
		std::vector<Explosion> explosion_group_t;
		for(int i = 0; i < ((int)explosion_group.size()); i++) {
			if(!explosion_group[i].delts) {
				explosion_group[i].update();
				explosion_group_t.push_back(explosion_group[i]);
			}
		}
		explosion_group.clear();
		for(int i = 0; i < ((int)explosion_group_t.size()); i++) {
			explosion_group.push_back(explosion_group_t[i]);
		}
	}

	/* Update Section Grenade */
	vel_y += GRAVITY;
	float dx = direction * speed;
	float dy = vel_y;

	/* Check collision with floor */
	height_sc = DestR.h + DestR.y;
	if(height_sc + dy > 300) {
		dy    = 300 - height_sc;
		speed = 0;
	}

	/* Check coliision with walls */
	if((DestR.x + dx < 0) || ((DestR.x + 10) + dx > SCREEN_WIDTH)) {
		direction *= -1;
		dx         = direction * speed;
	}

	/* Update grenade position */
	DestR.x += dx;
	DestR.y += dy;

	/* Countdown timer */
    timer -= 1;
    if(timer <= 0) {
    	delts     = true;
    	Explosion explosion(DestR.x, DestR.y, 0.5, renderer);
    	explosion_group.push_back(explosion); 
    }
}

void Grenade::draw(SDL_Renderer* renderer) {
	for(auto& explosion : explosion_group) {
		explosion.draw(renderer);
	}

	SDL_RenderCopy(renderer, image, NULL, &DestR);
}