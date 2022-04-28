#include "Lib.cpp"

//Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

//The window we'll be rendering to
SDL_Window* Window = NULL;

//Buttons objects
Button sign_in;
Button sign_up; 

//Font
TTF_Font* gFont1 = NULL;
TTF_Font* gFont2 = NULL;

//Starts up SDL and creates window
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
			TTF_Init();
			Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
		}
	}
	return true;
}

//Background
LTexture background;
//Text
LTexture APP_TITLE;

//Loads media
bool loadMedia() {
	//Background
	background.loadFromFile("anh/background.jpg");
	//Text
	gFont1 = TTF_OpenFont("font/Roboto-Medium.ttf", 60);
	SDL_Color text = {63, 59, 55};
	APP_TITLE.loadFromRenderedText("SUPPORT ASSIST", text, gFont1);
	gFont2 = TTF_OpenFont("font/Qarolina.ttf", 20);
	// //Transition sound
	transition = Mix_LoadWAV("21_sound_effects_and_music/low.wav");
	//Load sprites
	sign_in.createButton("anh/signin.png", SCREEN_WIDTH/2, SCREEN_HEIGHT/2);
	sign_up.createButton("anh/signup.png", SCREEN_WIDTH/1.35, SCREEN_HEIGHT/2);
	return true;
}

//Frees media and shuts down SDL
void close() {
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
			//Main loop flag
			bool quit = false;
			//Event handler
			SDL_Event e;
			//While application is running
			while (!quit) {	
				bool check = false;
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0) {
					//User requests quit
					if(e.type == SDL_QUIT) {
						quit = true;
					}
					//Handle button events
					sign_in.handleEvent(&e);
					sign_up.handleEvent(&e);
				}
				//Clear screen
				SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(Renderer);
				background.render(0,0);
				APP_TITLE.render(SCREEN_WIDTH/1.75, SCREEN_HEIGHT/3.5);
				//Render buttons
				sign_in.render();
				sign_up.render();
				//Update screen
				SDL_RenderPresent(Renderer);
			}
		}
	}
	//Free resources and close SDL
	close();
	return 0;
}
