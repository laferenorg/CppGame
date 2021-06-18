/* C++ */
#include <iostream>
#include <string>
#include <vector>

/* SDL2 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/* Header */
#include <header/SolMain.hpp>
#include <header/Soldier.hpp>
#include <header/Grenade.hpp>

Soldier* player;
int      command        = 0;
bool     shoot          = false;
bool     grenade        = false;
bool     grenade_thrown = false;

std::vector<Grenade> grenade_group;

void SolMain::start(SDL_Renderer* renderer) {
	player = new Soldier("player", 200, 200, 3, 5, 20, 5, renderer);
}

void SolMain::handleEvents(SDL_Event& event) {
	switch(event.type) {
		case SDL_KEYDOWN: {
			switch(event.key.keysym.sym) {
				case SDLK_a: {
					command = 1;
				}
				break;
				case SDLK_d: {
					command = 2;
				}
				break;
				case SDLK_w: {
					if(player->alive) player->jump = true;
				}
				break;
				case SDLK_q: {
					grenade = true;
				}
				break;
				case SDLK_SPACE: {
					shoot = true;
				}
				break;
			}
		}
		break;

		case SDL_KEYUP: {
			switch(event.key.keysym.sym){
				case SDLK_a: {
					command = 0;
				}
				break;
				case SDLK_d: {
					command = 0;
				}
				break;
				case SDLK_q: {
					grenade        = false;
					grenade_thrown = false;
				}
				case SDLK_SPACE: {
					shoot = false;
				}
				break;
			}
		}
		break;
    }
}

void SolMain::update() {
	player->update();
	switch(command) {
		case 0: {
			player->update_action(0); // 1: Idle
		}
		break;
		default: {
			player->update_action(1); // 1: Run
		}
		break;
	}
	player->move(command);
	if(player->jump) player->update_action(2); // 2: Jump
}

void SolMain::render(SDL_Renderer* renderer) {
	{
		std::vector<Grenade> grenade_group_t;
		for(int i = 0; i < ((int)grenade_group.size()); i++) {
			if(!grenade_group[i].delts) {
				grenade_group[i].update(renderer);
				grenade_group_t.push_back(grenade_group[i]);
			}
		}
		grenade_group.clear();
		for(int i = 0; i < ((int)grenade_group_t.size()); i++) {
			grenade_group.push_back(grenade_group_t[i]);
		}
	}
	if(grenade && (grenade_thrown == false) && (player->grenades > 0)) {
		Grenade grenade_t(player->DestR.x + (0.5 * player->DestR.w * player->direction), 
						  player->DestR.y, player->direction, renderer);
		grenade_group.push_back(grenade_t);

		/* Reduce grenades */
        player->grenades -= 1;
        grenade_thrown    = true;
	}
	for(auto& grenades : grenade_group) {
		grenades.draw(renderer);
	}

	if(shoot) player->shoot(renderer);
	player->draw(renderer);
}