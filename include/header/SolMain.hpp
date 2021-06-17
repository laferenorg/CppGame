#ifndef _SOLMAIN_HPP_
#define _SOLMAIN_HPP_

class SolMain {
public:
	void start(SDL_Renderer* renderer);
	void handleEvents(SDL_Event& event);
	void update();
	void render(SDL_Renderer* renderer);
};

#endif // _SOLMAIN_HPP_