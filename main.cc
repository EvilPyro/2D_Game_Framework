#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <chrono>
#include <thread>
#include "ObjectManager.h"
#include <memory>
#include "Player.h"
#include "Map.h"
#include "RenderScheduler.h"
#include "Camera.h"
#include "ExtraTypes.h"
#include "Event.h"
#include "Engine.h"


int main() {
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	IMG_Init(IMG_INIT_PNG);
	SDL_Window* Window;
	SDL_Renderer* Renderer;
	SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_RESIZABLE, &Window, &Renderer);
	//Engine Engine(Window, Renderer);
	Engine* Engine = Engine::Construct(Window, Renderer);
	Engine->Run();

	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);
	SDL_Quit();
/*
	Map MyMap("Map.tmx", &RS);
	Position P = std::make_tuple(32,0,-1);
	Camera cam(P, SizeX, SizeY, 2);
*/
/*
	while (!quit) {
		auto frame_start = std::chrono::steady_clock::now();

		//int seconds = SDL_GetTicks()/1000;
		//int sprite = seconds % 4;

		//SDL_Rect srcrect = { 0, 0, 32, 32 };
        //SDL_Rect dstrect = { 0, 0, 32, 32 };

		MyMap.Update(cam);

		RS.Draw();
		SDL_RenderPresent(Renderer);
		SDL_RenderClear(Renderer);





		// Time Management
		std::chrono::duration<double> frame_timelength;
		do {  // frame length correction
			std::this_thread::sleep_for(std::chrono::microseconds(100));
			frame_timelength = (std::chrono::steady_clock::now() - frame_start)*1000;
		}
		while (frame_timelength.count() < 1000/(float)(max_fps));








		// Log
		//std::cout << "\r\033[K" << 1000/frame_timelength.count() << " FPS" << std::flush;









		// Handle Events
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					quit = true;
					break;

				case SDL_MOUSEBUTTONDOWN:
					switch ((event.button).button) {
						case SDL_BUTTON_LEFT:
							break;
						case SDL_BUTTON_RIGHT:
							break;
					}
					break;

				case SDL_KEYDOWN:
					switch (((event.key).keysym).sym) {
						case SDLK_UP:
						break;
					case SDLK_DOWN:
						break;
					case SDLK_LEFT:
						break;
					case SDLK_RIGHT:
						break;
					}
					break;
			}
		}
	}
	*/
}
