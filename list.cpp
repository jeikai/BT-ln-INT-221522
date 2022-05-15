#pragma once
#include "Lib.cpp"

//Background
LTexture background_list;
//Text
LTexture headtitle, add; 
//Loads media
bool loadMedia_list() {
	//Background
	background_list.loadFromFile(Renderer,"anh/background.png");
	font();
	headtitle.loadFromRenderedText(Renderer,"TITLE: ", text, gFont3);
	add.loadFromRenderedText( Renderer,"+ Add a task: ", text, gFont3);
	// //Transition sound
	transition = Mix_LoadWAV("21_sound_effects_and_music/low.wav");
	return true;
}

void timetable() {
	
		//Load media
		bool check = loadMedia_list();
		if (check == false) {
			cout << "Failed to load media!" << endl;
		} else {	
			//Main loop flag
			bool quit = false;
			vector<TextBox> All_Textbox(2);
			All_Textbox[1].setType(1);
			int pos;
			//Event handler
			SDL_Event ev;
			//While application is running
			
			while (!quit) {	
				
				
				while (SDL_PollEvent(&ev) != 0) {
					//User requests quit
					SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(Renderer);
				All_Textbox[0].render(Renderer, "TITLE: ", (SCREEN_WIDTH - All_Textbox[0].getTag().getW() - 600) / 2, SCREEN_HEIGHT / 3.0, text, gFont2);
                All_Textbox[1].render(Renderer, "+ Add a task: ", (SCREEN_WIDTH - All_Textbox[1].getTag().getW() - 600) / 2, SCREEN_HEIGHT / 2.0, text, gFont2);
				background_list.render(Renderer,0,0);
					if(ev.type == SDL_QUIT) {
						quit = true;
					} else if (ev.type == SDL_MOUSEBUTTONDOWN) {
                        cout << "mouse pressed" << endl;
                        for (int i = 0; i < All_Textbox.size(); i++) {
                            if (All_Textbox[i].is_mouse_inside(ev.button.x, ev.button.y) == true) {
                                All_Textbox[i].setState(true);
                                pos = i;
                                cout << pos << endl;
                            }
                            else {
                                All_Textbox[i].setState(false);
                            }
                        }
						if (toggle_password.isInside(ev.button.x, ev.button.y) == true) {
                            if (toggle_password.getCurrentState() == BUTTON_STATE_MOUSE_OUTSIDE) {
                                toggle_password.setButtonState(BUTTON_STATE_MOUSE_OVER_MOTION);
                                All_Textbox[1].setType(0);
                            }
                            else {
                                toggle_password.setButtonState(BUTTON_STATE_MOUSE_OUTSIDE);
                                All_Textbox[1].setType(1);
                            }
                        }
                        
                    } else if (ev.type == SDL_KEYDOWN) {
                        if (ev.key.keysym.sym == SDLK_BACKSPACE && All_Textbox[pos].getInputText().length() > 0) {
                            if (All_Textbox[pos].getState() == true) {
                                All_Textbox[pos].inputPop();
                            }
                        }
                    } else if (ev.type == SDL_TEXTINPUT) {
                        if (!(SDL_GetModState() & KMOD_CTRL && (ev.text.text[0] == 'c' || ev.text.text[0] == 'C' || ev.text.text[0] == 'v' || ev.text.text[0] == 'V'))) {
                            if (All_Textbox[pos].getState() == true) {
                                All_Textbox[pos].updateInputText(ev.text.text);
                            }
                        }
                    }

				}
				
				for (int i = 0; i < All_Textbox.size(); i++) {
                    if (All_Textbox[i].getInputText().length() != 0) {
                        All_Textbox[i].renderInputText(Renderer,gFont2, text);
                    }
                }
				//Update screen
				SDL_RenderPresent(Renderer);
			}
		}
	//Free resources and close SDL
	close();
}

