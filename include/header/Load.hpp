#ifndef _LOAD_HPP_
#define _LOAD_HPP_

/* C++ */
#include <string>

/* SDL2 */
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Load {
public:
	static SDL_Texture* LoadTexture(std::string texture, SDL_Renderer* renderer);
	static float get_width(std::string texture);
	static float get_height(std::string texture);
};

#endif // _LOAD_HPP_