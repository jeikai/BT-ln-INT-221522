#include "Lib.cpp"
#include "Textbox.cpp"
#include <vector>
//Buttons objects
Button sign_in;
Button sign_up; 
Button toggle_password;
//Background
LTexture background;
//Text
LTexture APP_TITLE;
LTexture  username, password;

//Loads media
bool loadMedia() {
	//Background
	background.loadFromFile(Renderer, "anh/background.png");

	//Text
	font();
	
	SDL_Color text = {63, 59, 55};
	APP_TITLE.loadFromRenderedText(Renderer, "SUPPORT ASSIST", text, gFont1);
	
	username.loadFromRenderedText(Renderer, "Username: ", text, gFont2);
	password.loadFromRenderedText( Renderer, "Password: ", text, gFont2);
	// //Transition sound
	transition = Mix_LoadWAV("21_sound_effects_and_music/low.wav");
	//Load sprites
	sign_in.createButton(Renderer, "anh/signin.png", SCREEN_WIDTH/4, SCREEN_HEIGHT/1.7, 1);
	sign_up.createButton(Renderer, "anh/signup.png", SCREEN_WIDTH/2, SCREEN_HEIGHT/1.7, 1);
	toggle_password.createButton(Renderer, "anh/toggle_password.png", 1040, 360, 2);
	toggle_password.setButtonState(BUTTON_STATE_MOUSE_OUTSIDE);
	
	return true;
}

//Frees media and shuts down SDL

int trang_chu_event(SDL_Event e, int trans) {
	
	if (sign_in.handleEvent(&e) == 2 ) {
						sign_in.free();
						sign_up.free();
						APP_TITLE.free();
						username.free();
						password.free();
						trans = 1;
						diagbutton.handleEvent(&e);
						listbutton.handleEvent(&e);
						timerbutton.handleEvent(&e);
			
	}
	else if(sign_up.handleEvent(&e) == 2) {
						sign_in.free();
						sign_up.free();
						APP_TITLE.free();
						username.free();
						password.free();

						trans = 2;
						submit.handleEvent(&e);
	}
	return trans;
}


int main (int argc, char* args[]) {
	//Start up SDL and create window
	if (!init()) {
		cout << "Failed to initialize!" << endl;
	} else {
		//Load media
		bool check = loadMedia();
		if (check == false) {
			cout << "Failed to load media!" << endl;
		} else {	
			//Main loop flag
			bool quit = false;
			vector<TextBox> All_Textbox(2);
			All_Textbox[1].setType(1);
			//Event handler
			SDL_Event ev;
			//While application is running
			int trans = 0;
			while (!quit) {	
				//bool check = false;
				//Handle events on queue
				while (SDL_PollEvent(&ev) != 0) {
					SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(Renderer);
				background.render( Renderer, 0,0);
				APP_TITLE.render(Renderer, SCREEN_WIDTH/3, SCREEN_HEIGHT/5.75);
				All_Textbox[0].render(Renderer, "Username: ", (SCREEN_WIDTH - All_Textbox[0].getTag().getW() - 600) / 2, SCREEN_HEIGHT / 3.0, text, gFont2);
                All_Textbox[1].render(Renderer, "Password: ", (SCREEN_WIDTH - All_Textbox[1].getTag().getW() - 600) / 2, SCREEN_HEIGHT / 2.0, text, gFont2);
				toggle_password.render(Renderer);
				//Render buttons
				sign_in.render(Renderer);
				sign_up.render(Renderer);

					int pos;
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
                    sign_in.handleEvent( &ev);
                    sign_up.handleEvent( &ev);
					//Handle button events
					trans = trang_chu_event(ev, trans);
					
				}
				//Clear screen
				

				for (int i = 0; i < All_Textbox.size(); i++) {
                    if (All_Textbox[i].getInputText().length() != 0) {
                        All_Textbox[i].renderInputText(Renderer,gFont2, text);
                    }
                }

				if ( trans == 1) {
					menu();
				} else if ( trans == 2) {
					signup();
				}
				//Update screen
				SDL_RenderPresent(Renderer);
			}
		}
	}
	
	//Free resources and close SDL
	close();
	return 0;
}

