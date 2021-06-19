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
#include <header/Soldier.hpp>

extern Soldier* player;
extern std::vector<Soldier*> enemy_group;

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
    if(timer <= 0 && !Boom) {
    	itsDe = !itsDe;
    	Explosion explosion(DestR.x - DestR.w, DestR.y - DestR.h, 0.5, renderer);
    	explosion_group.push_back(explosion);
    	Boom = !Boom;

    	/* Do damage to anyone that is nearby */
    	if((abs((DestR.x + (DestR.w / 2)) - (player->DestR.x + (player->DestR.w / 2))) < TILE_SIZE * 2) &&
    		(abs((DestR.y + (DestR.h / 2)) - (player->DestR.y + (player->DestR.h / 2))) < TILE_SIZE * 2)) {
    		player->health -= 50;
    	}

    	for(auto& enemy : enemy_group) {
    		if((abs((DestR.x + (DestR.w / 2)) - (enemy->DestR.x + (enemy->DestR.w / 2))) < TILE_SIZE * 2) &&
	    		(abs((DestR.y + (DestR.h / 2)) - (enemy->DestR.y + (enemy->DestR.h / 2))) < TILE_SIZE * 2)) {
	    		enemy->health -= 50;
	    	}
    	}
    }

    /* Update Section Explosion */
	{
		std::vector<Explosion> explosion_group_t;
		for(int i = 0; i < ((int)explosion_group.size()); i++) {
			if(explosion_group[i].delts == false) {
				explosion_group[i].update(delts);
				explosion_group_t.push_back(explosion_group[i]);
			}
		}

		explosion_group.clear();
		for(int i = 0; i < ((int)explosion_group_t.size()); i++) {
			explosion_group.push_back(explosion_group_t[i]);
		}
	}
}

void Grenade::draw(SDL_Renderer* renderer) {
	for(auto& explosion : explosion_group) {
		explosion.draw(renderer);
	}

	if(!itsDe) {
		SDL_RenderCopy(renderer, image, NULL, &DestR);
	}
}