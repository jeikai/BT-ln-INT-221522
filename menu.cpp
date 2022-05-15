#pragma once
#include "Lib.cpp"

Button diagbutton, listbutton, timerbutton;

//Text
LTexture line, healthcare, background_menu;

//Loads media
bool loadMedia_menu() {
	//Background
	background_menu.loadFromFile(Renderer,"anh/background.png");
	line.loadFromFile(Renderer,"anh/line in menu.png");
	font();
	
	healthcare.loadFromRenderedText(Renderer,"HEALTHCARE", text, gFont3);
	// //Transition sound
	transition = Mix_LoadWAV("21_sound_effects_and_music/low.wav");
	//Load sprites
	
	diagbutton.createButton(Renderer,"anh/diagbutton.png", SCREEN_WIDTH/2.4, SCREEN_HEIGHT/2, 3);
	listbutton.createButton(Renderer,"anh/listbutton.png", SCREEN_WIDTH/1.7, SCREEN_HEIGHT/2, 3);
	timerbutton.createButton(Renderer,"anh/timerbutton.png",SCREEN_WIDTH/1.999, SCREEN_HEIGHT/3.6, 3 );
	return true;
}

//Frees media and shuts down SDL
int menu_event( SDL_Event e, int trans) {
	if ( timerbutton.handleEvent(&e) == 2) {
		healthcare.free();
		diagbutton.free();
		line.free();
		timerbutton.free();
		//submit.handleEvent(&e);
		trans = 1;
	} else if (	listbutton.handleEvent(&e) == 2) {
		healthcare.free();
		diagbutton.free();
		line.free();
		timerbutton.free();
		trans = 2;
	}
	return trans;
}
void menu() {
	//Start up SDL and create window
		//Load media
		bool check = loadMedia_menu();
		if (check == false) {
			cout << "Failed to load media!" << endl;
		} else {	
			//Main loop flag
			bool quit = false;
			//Event handler
			SDL_Event e;
			//While application is running
			int trans = 0;
			while (!quit) {	
				//bool check = false;
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0) {
					//User requests quit
					if(e.type == SDL_QUIT) {
						quit = true;
					}
					//Handle button events
						diagbutton.handleEvent(&e);
						listbutton.handleEvent(&e);
						timerbutton.handleEvent(&e);
						trans = menu_event(e, trans);
				}
				//Clear screen
				SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(Renderer);
				background_menu.render( Renderer,0, 0);
				healthcare.render( Renderer,SCREEN_WIDTH/9, SCREEN_HEIGHT/2);
				line.render(Renderer,0,SCREEN_HEIGHT/1.65);
			
					diagbutton.render(Renderer);
					listbutton.render(Renderer);
					timerbutton.render(Renderer);
				if ( trans == 1) {
					time();
				} else if ( trans == 2) {
					timetable();
				}
				//Update screen
				SDL_RenderPresent(Renderer);
			}
		}
	
	
	//Free resources and close SDL
	close();
	
}

