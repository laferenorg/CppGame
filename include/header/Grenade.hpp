#ifndef _GRENADE_HPP_
#define _GRENADE_HPP_

/* C++ */
#include <string>
#include <vector>

/* SDL2 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Grenade {
public:
	bool         delts = false;
	int          timer = 100;
    float        vel_y = -11;
    float        speed = 7;
    SDL_Texture* image;
    SDL_Rect     DestR;
    int          direction;
    float        height_sc;
public:
	Grenade(int x, int y, int direction, SDL_Renderer* renderer);
	void update();
	void draw(SDL_Renderer* renderer);
};

#endif // _GRENADE_HPP_