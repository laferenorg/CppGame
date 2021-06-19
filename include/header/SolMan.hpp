#ifndef _SOLMAN_HPP_
#define _SOLMAN_HPP_

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class SolMan {
private:
	/* Settings variable */
	std::string title;
	int position_x, position_y;
	int width, height;
	bool fullscreen;

	bool haveError = false;
public:
	/* Public variable of this class */
	SDL_Window *window;
	SDL_Renderer* renderer;
public:
	SolMan(const char* _title_, int _position_x_, int _position_y_,
		   int _width_, int _height_, bool _fullscreen_); // Contructor
	void SetBackgroundColor(int R, int G, int B, int A); // Set Background Color
	void clean(); // Clean Window
	template <class _c_class_>
	void run() { 
		{
			/* Intialize variable class */
			_c_class_ _call_function_;

			/* Run looping of this program */
			bool its_run = (haveError) ? 0 : 1;

			/* Start */
			_call_function_.start(renderer);
			while(its_run) {
				Uint64 start = SDL_GetPerformanceCounter();
				/* Start handle event */
				SDL_Event event;
			    SDL_PollEvent(&event);
			    
			    switch(event.type) {
			        case SDL_QUIT: {
			            its_run = false;
			        }
			        break;
			    }
				_call_function_.handleEvents(event);
				/* End handle event */
				
				/* Start handle update */
				_call_function_.update();
				/* End handle update */
				
				/* Start handle render */
				SDL_RenderClear(renderer);
				_call_function_.render(renderer);
				SDL_RenderPresent(renderer);
				/* End handle render */

				/* Set FPS */
				Uint64 end = SDL_GetPerformanceCounter();
				float elapsedMS = (end - start) / (float)SDL_GetPerformanceFrequency() * 1000.0f;
				// Cap to 60 FPS
				if(floor(16.666f - elapsedMS) < 0) {
					SDL_Delay((floor(16.666f - elapsedMS) * -1));
				} else {
					SDL_Delay(floor(16.666f - elapsedMS));
				}
			}
		}
	} // Run looping
};

#endif // _SOLMAN_HPP_