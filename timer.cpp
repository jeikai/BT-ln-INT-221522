#pragma once
#include "Lib.cpp"
#include <ctime>
#include <sstream>

//Background
LTexture background_timer;
//Text
LTexture timer;
LTexture hour, minute, second;
//Loads media
bool loadMedia_timer() {
	//Background
	background_timer.loadFromFile(Renderer,"anh/background.png");
	font();
	timer.loadFromRenderedText(Renderer,"Timer: ", text, gFont2);
	// //Transition sound
	transition = Mix_LoadWAV("21_sound_effects_and_music/low.wav");
	return true;
}

void time() {
	
		//Load media
		bool check = loadMedia_timer();
		if (check == false) {
			cout << "Failed to load media!" << endl;
		} else {	
			//Main loop flag
			bool quit = false;
			//Event handler
			SDL_Event e;
			//While application is running
			Uint32 startTime = 0;
            SDL_Color text = {63, 59, 55};
            stringstream timeText;
			
			//Timer
			time_t now = time(0);
			tm* ltm = localtime(&now);
			while (!quit) {	
				//bool check = false;
				//Handle events on queue
				
				while (SDL_PollEvent(&e) != 0) {
					//User requests quit
					if(e.type == SDL_QUIT) {
						quit = true;
					} 
                    else if( e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN )
					{
						startTime = SDL_GetTicks();
					}	
				}
				SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(Renderer);
                timeText.str( "" );
				timeText << "Milliseconds since start time " << SDL_GetTicks() - startTime;
				timer.loadFromRenderedText(Renderer, timeText.str().c_str(), text, gFont2);

				string gio = to_string( ltm->tm_hour);
				hour.loadFromRenderedText( Renderer,gio, text, gFont2);
				string phut = to_string( ltm->tm_min);
				minute.loadFromRenderedText( Renderer,phut, text, gFont2);
				string demogiay = to_string( ltm->tm_sec);
				second.loadFromRenderedText(Renderer,demogiay, text, gFont2);
				
                //Clear screen
				
				background_timer.render(Renderer,0,0);
				timer.render(Renderer,SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
				
				hour.render(Renderer,100,0);
				minute.render(Renderer, 50, 50);
				second.render(Renderer, 100, 100);	
				
				//Update screen
				SDL_RenderPresent(Renderer);
			}
		}
	
	
	//Free resources and close SDL
	close();
}

