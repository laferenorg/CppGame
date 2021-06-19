#ifndef _EXPLOSION_HPP_
#define _EXPLOSION_HPP_

/* C++ */
#include <vector>

/* SDL2 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Explosion {
public:
	bool         delts       = false;
	std::vector<SDL_Texture*> images;
	unsigned int frame_index = 0;
    SDL_Texture* image;
    SDL_Rect     DestR;
    int          counter     = 0;
public:
	Explosion(int x, int y, float scale, SDL_Renderer* renderer);
	void update(bool& replace);
	void draw(SDL_Renderer* renderer);
};

#endif // _EXPLOSION_HPP_