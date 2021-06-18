/* C++ */
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <fstream>
#include <experimental/filesystem>
#include <cstring>

/* SDL2 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/* Header */
#include <header/Soldier.hpp>
#include <header/Load.hpp>
#include <header/Bullet.hpp>
#include <header/Settings.hpp>

Soldier::Soldier(std::string char_type, int x, int y, int scale,
				 float speed, int ammo, int grenades,
				 SDL_Renderer* renderer) {
	this->char_type  = char_type;
	SrcR.x     = x;
	SrcR.y     = y;
	DestR.x    = 0;
	DestR.y    = 0;
	this->speed      = speed;
	this->ammo       = ammo;
	this->start_ammo = this->ammo;
	this->grenades   = grenades;
	
	/* Load all images for the players */
    std::array<std::string, 4> animation_types = { "Idle", "Run", "Jump", "Death" };
    for(unsigned int animation = 0; animation < ((int)animation_types.size()); animation++) {
    	std::vector<SDL_Texture*> temp_list;
    	unsigned int num_of_frames = 0;

		{
			std::string path_location = "assets/img/" + char_type + "/" + animation_types[animation];
			std::experimental::filesystem::path path(path_location.c_str());
			for (auto& count : std::experimental::filesystem::directory_iterator(path)) {
				num_of_frames += 1;
			}
		}

		for(int i = 0; i < num_of_frames; i++) {
			std::string path_image = "assets/img/" + char_type + "/" + 
									 animation_types[animation] + "/" + std::to_string(i) +
									 ".png";
			SrcR.w = Load::get_width(path_image);
			SrcR.h = Load::get_height(path_image);
			temp_list.push_back(Load::LoadTexture(path_image, renderer));
		}
		animation_list.push_back(temp_list);
    }
    DestR.w = SrcR.w * scale;
    DestR.h = SrcR.h * scale;
    image = animation_list[action][frame_index];
    height_sc = DestR.h;
}

void Soldier::update() {
	update_animation();
	check_alive();

	/* Update cooldown */
	if(shoot_cooldown > 0) {
		shoot_cooldown -= 1;
	}

	/* Bullet Update */
	{
		std::vector<Bullet> bullet_group_temp;
		for(int i = 0; i < ((int)bullet_group.size()); i++) {
			if(!bullet_group[i].delts) {
				bullet_group[i].update();
				bullet_group_temp.push_back(bullet_group[i]);
			}
		}
		bullet_group.clear();
		for(int i = 0; i < ((int)bullet_group_temp.size()); i++) {
			bullet_group.push_back(bullet_group_temp[i]);
		}
	}
}

void Soldier::move(int command) {
	/* Reset movement variables */
	float dx = 0;
	float dy = 0;

	/* Assign movement varibales if moving left or right */
	switch(command) {
		case 1: {
			dx        = -speed;
			flip      = SDL_FLIP_HORIZONTAL;
			direction = -1;
		}
		break;
		case 2: {
			dx        = speed;
			flip      = SDL_FLIP_NONE;
			direction = 1;
		}
		break;
	}

	/* Jump */
	if((jump == true) && (in_air == false)) {
		vel_y  = -12;
        jump   = false;
        in_air = true;
	}

	/* Apply gravity */
	vel_y += GRAVITY;
	dy += vel_y;

	height_sc = DestR.h + DestR.y;
	/* Check collision with floor */
	if(height_sc + dy > 300) {
		dy     = 300 - height_sc;
		in_air = false;
	}

	/* Update rectangle position */
	DestR.x += dx;
	DestR.y += dy;
}

void Soldier::shoot(SDL_Renderer* renderer) {
	if((shoot_cooldown == 0) && (ammo > 0)) {
		shoot_cooldown = 20;
		Bullet bullet((DestR.x + (DestR.w / 2)) + (0.6 * DestR.w * direction),
					  (DestR.y + (DestR.h / 2)), direction, renderer);
		bullet_group.push_back(bullet);

		ammo -= 1;
	}
}

void Soldier::update_animation() {
	/* Update animation */
	float ANIMATION_COOLDOWN = 100;
	image = animation_list[action][frame_index];

	if(SDL_GetTicks() - update_time > ANIMATION_COOLDOWN) {
		update_time = SDL_GetTicks();
		frame_index += 1; 
	}

	if(frame_index >= ((int)animation_list[action].size())) {
		if(action == 3) {
			frame_index = ((int)animation_list[action].size()) - 1;
		} else {
			frame_index = 0;
		}
	}
}

void Soldier::update_action(unsigned int new_action) {
	/* Check if the new action is different to the previous one */
	if(new_action != action) {
		action = new_action;

		/* Update the animation settings */
		frame_index = 0;
        update_time = SDL_GetTicks();
	}
}

void Soldier::check_alive() {
	if(health <= 0) {
		health = 0;
		speed  = 0;
		alive  = 0;
		update_action(3); // 3: death
	}
}

void Soldier::draw(SDL_Renderer* renderer) {
	/* Bullet Draw */
	for(int i = 0; i < ((int)bullet_group.size()); i++) {
		if(!bullet_group[i].delts) bullet_group[i].draw(renderer);
	}
	SDL_RenderCopyEx(renderer, image, NULL, &DestR, 0, NULL, flip);
}