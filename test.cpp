#include "Lib.cpp"
#include "Textbox.cpp"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
SDL_Window* Window = NULL;
//Background
LTexture background;
//App Title
LTexture APP_TITLE;
//Font and Color
TTF_Font* Title_Font = NULL;
TTF_Font* Sub_Font = NULL;
SDL_Color text_color = {63, 59, 55};
//Buttons objects
Button sign_in;
Button sign_up; 

//Starts SDL and creates window
bool init() {
	//Initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		cout << "SDL could not initialize! SDL Error: " << endl << SDL_GetError();
		return false;
	} else {
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			cout << "Warning: Linear texture filtering not enabled!" << endl;
		}
		//Create window
		Window = SDL_CreateWindow("SUPPORT ASSIST", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (Window == NULL) {
			cout << "Window could not be created! SDL Error: " << endl << SDL_GetError();
			return false;
		} else {
			//Create vsynced renderer for window
			Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
			if (Renderer == NULL) {
				cout << "Renderer could not be created! SDL Error: " << endl << SDL_GetError();
				return false;
			} else {
				//Initialize renderer color
				SDL_SetRenderDrawColor( Renderer, 0xFF, 0xFF, 0xFF, 0xFF );
				//Initialize PNG loading
				if (!IMG_Init(IMG_INIT_PNG)) {
					cout << "SDL_image could not initialize! SDL_image Error: " << endl << IMG_GetError();
					return false;
				}
			}
			SDL_StartTextInput();
			TTF_Init();
			Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
		}
	}
	return true;
}

//Loads media
bool loadMedia() {
	//Background
	background.loadFromFile("anh/background.jpg");
	//Render Title
	Title_Font = TTF_OpenFont("font/Roboto-Medium.ttf", 60);
	Sub_Font = TTF_OpenFont("font/Roboto-Medium.ttf", 40);
	APP_TITLE.loadFromRenderedText("SUPPORT ASSIST", text_color, Title_Font);
	//Load button
	sign_in.createButton("anh/signin.png", (SCREEN_WIDTH - 600)/2, SCREEN_HEIGHT/1.5);
	sign_up.createButton("anh/signup.png", (SCREEN_WIDTH - 600)/2 + 400, SCREEN_HEIGHT/1.5);
	return true;
}

//Free resources and shut down SDL
void close() {
	SDL_StopTextInput();
	//Free loaded images
	sign_in.free();
	sign_up.free();
	//Destroy window	
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);
	Window = NULL;
	Renderer = NULL;
	//Quit SDL subsystems
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
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
			bool quit = false;
			SDL_Event ev;
				bool check = false;
				// background.render(0,0);
				// APP_TITLE.render((SCREEN_WIDTH - APP_TITLE.getWidth())/2, SCREEN_HEIGHT/5.5);
				TextBox User_Name;
				// User_Name.Set_TextBox_Tag("Username: ", text_color, Sub_Font);
				// User_Name.Render_TextBox_Tag((SCREEN_WIDTH - User_Name.getTag().getWidth() - 600)/2, SCREEN_HEIGHT/3.0);
				// User_Name.Draw_Input_Box(SCREEN_WIDTH, SCREEN_HEIGHT);
				vector<TextBox> All_Text_Box;
				All_Text_Box.push_back(User_Name);
			while (quit == false) {	
				// bool check = false;
				SDL_RenderClear(Renderer);
				background.render(0,0);
				APP_TITLE.render((SCREEN_WIDTH - APP_TITLE.getWidth())/2, SCREEN_HEIGHT/5.5);
				// TextBox User_Name;
				User_Name.Set_TextBox_Tag("Username: ", text_color, Sub_Font);
				User_Name.Render_TextBox_Tag((SCREEN_WIDTH - User_Name.getTag().getWidth() - 600)/2, SCREEN_HEIGHT/3.0);
				User_Name.Draw_Input_Box(SCREEN_WIDTH, SCREEN_HEIGHT);
				// vector<TextBox> All_Text_Box;
				// All_Text_Box.push_back(User_Name);
				int pos;
				//Render buttons
				sign_in.render();
				sign_up.render();
				bool renderText = false;
				while (SDL_PollEvent(&ev) != 0) {
					//User requests quit
					if (ev.type == SDL_QUIT) {
						quit = true;
					} else if (ev.type == SDL_MOUSEBUTTONDOWN) {
						cout << "mouse pressed" << endl;
						for (int i = 0; i < All_Text_Box.size(); i++) {
							if (All_Text_Box[i].is_mouse_inside(ev.button.x, ev.button.y) == true) {
								All_Text_Box[i].setState(true);
								pos = i;
								cout << "mouse is inside" << endl;
							} else {
								All_Text_Box[i].setState(false);
								cout << "mouse is outside" << endl;
							}
						}
					} else if (ev.type == SDL_KEYDOWN) {
						if (ev.key.keysym.sym == SDLK_BACKSPACE && All_Text_Box[pos].getInputText().length() > 0) {
							All_Text_Box[pos].inputPop();
							renderText = true;
						// } else if (ev.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) {
						// 	//SDL_SetClipboardText(All_Text_Box[pos].getInputText().c_str());
						// 	continue;
						// } else if (ev.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {
						// 	All_Text_Box[pos].setInputText(SDL_GetClipboardText());
						// 	renderText = true;
						// }
						}
					} else if (ev.type == SDL_TEXTINPUT) {
						if (!(SDL_GetModState() & KMOD_CTRL && (ev.text.text[0] == 'c' || ev.text.text[0] == 'C' || ev.text.text[0] == 'v' || ev.text.text[0] == 'V'))) {
							All_Text_Box[pos].updateInputText(ev.text.text);
							renderText = true;
						}
					}
					sign_in.handleEvent(&ev);
					sign_up.handleEvent(&ev);
				}
				All_Text_Box[pos].renderInputText(Sub_Font, text_color);
				SDL_RenderPresent(Renderer);
			}
		}
	}
	close();
	return 0;
}
