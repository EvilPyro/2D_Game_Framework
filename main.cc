#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <chrono>
#include <thread>
#include "ObjectManager.h"
#include <memory>
#include "Player.h"
#include "Map.h"
#include "MediaLoader.h"
int main() {
	int SizeX = 2048;
	int SizeY = 1024;
	bool quit = false;
	bool term_output = false;
	const int max_fps = 144;

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	IMG_Init(IMG_INIT_PNG);
	SDL_Window* Window;
	SDL_Renderer* Renderer;

	SDL_CreateWindowAndRenderer(SizeX, SizeY, 0, &Window, &Renderer);
	MediaLoader ML(Renderer);
	SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);


	/*
	ObjectManager Test;
	std::unique_ptr<Object> P = std::make_unique<Player>();
	Test.Add(P);
	*/
	// TESTING BGN
	//SDL_Texture* texture = ML.GetTexture("sprite.png");

	//TODO:::

	// ML.GetTexture retorna nullptr!!!? tmb se jode la destructora por que no puede destruir nullptr?


	auto texture = ML.GetTexture("sprite.png");
	
	//Map MyMap("Map.tmx");
	//auto Level = MyMap.getLevel(0);
	//for (int i = 0; i < (Level->Tiles).size(); ++i)
	//	std::cout << (Level->Tiles)[i] << std::endl;

	// TESTING END

	while (!quit) {
		auto frame_start = std::chrono::steady_clock::now();

		int seconds = SDL_GetTicks()/1000;
		int sprite = seconds % 4;


		//TESTING BGN


		//TESTING END




		SDL_Rect srcrect = { sprite * 32, 0, 32, 64 };
        SDL_Rect dstrect = { 10, 10, 32, 64 };

		SDL_RenderClear(Renderer);
		SDL_RenderCopy(Renderer, texture, &srcrect, &dstrect);
		// Render
		/*Test.Run();*/
		SDL_RenderPresent(Renderer);







		// Time Management
		std::chrono::duration<double> frame_timelength;
		do {  // frame length correction
			std::this_thread::sleep_for(std::chrono::microseconds(100));
			frame_timelength = (std::chrono::steady_clock::now() - frame_start)*1000;
		}
		while (frame_timelength.count() < 1000/(float)(max_fps));








		// Log
		if (term_output)
			std::cout << "\r\033[K" << 1000/frame_timelength.count() << " FPS" << std::flush;









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
}
