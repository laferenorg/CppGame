#ifndef _SOLDIER_HPP_
#define _SOLDIER_HPP_

/* C++ */
#include <string>
#include <vector>

/* SDL2 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/* Header */
#include <header/Bullet.hpp>
#include <header/Grenade.hpp>
#include <header/Settings.hpp>

struct _animation_sprite_ {
	SDL_Texture* image;
	SDL_Rect     SrcR;
};

typedef struct _animation_sprite_ AnimtionSprite;

class Soldier {
public:
	bool             alive          = true;
	std::string      char_type;
	float            speed          = 0;
	int              ammo;
	int              start_ammo;
	int              grenades;
	int              health         = 100;
	int              max_health     = health;
	int              shoot_cooldown = 0;
	bool             jump           = false;
	float            vel_y          = 0;
	bool             in_air         = false;
	int              direction      = 1;
    SDL_RendererFlip flip           = SDL_FLIP_NONE;
    std::vector<std::vector<AnimtionSprite>> animation_list;
    unsigned int     frame_index    = 0;
    unsigned int     action         = 0;
	float            update_time    = SDL_GetTicks();
	SDL_Rect         DestR;
	SDL_Texture*     image;
	float            height_sc;
	std::vector<Bullet> bullet_group;
	float            scales;
public:
	Soldier(std::string char_type, int x, int y, int scale,
			float speed, int ammo, int grenades,
			SDL_Renderer* renderer);
	void update();
	void move(int command);
	void update_animation();
	void update_action(unsigned int new_action);
	void check_alive();
	void draw(SDL_Renderer* renderer);
	void shoot(SDL_Renderer* renderer);
};
	
#endif // _SOLDIER_HPP_