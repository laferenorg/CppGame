#ifndef _BULLET_HPP_
#define _BULLET_HPP_

/* C++ */
#include <string>
#include <vector>

/* SDL2 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Bullet {
public:
	bool         delts = false;
	float        speed = 10;
    SDL_Texture* image;
    SDL_Rect     DestR;
    int          direction;
public:
	Bullet(int x, int y, int direction, SDL_Renderer* renderer);
	void update();
	void draw(SDL_Renderer* renderer);
};

#endif // _BULLET_HPP_