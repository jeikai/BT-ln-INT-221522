#include <SDL.h>
#include <iostream>
using namespace std;

const int height = 1920;
const int width = 1920;

enum Func {
	demo, demo1, demo2, demo3 
};
SDL_Window * window = NULL;
SDL_Surface * surface = NULL;
SDL_Surface * loadSurface(string path);
SDL_Surface * current = NULL;
SDL_Surface * Key[demo3];

SDL_Surface * loadSurface(string path) {
	SDL_Surface * loadSurface = SDL_LoadBMP( path.c_str() );
	return loadSurface;
}

void gan() {
	Key[demo] = loadSurface("anh/demo.bmp");
	Key[demo1] = loadSurface("anh/demo1.bmp");
	Key[demo2] = loadSurface("anh/demo2.bmp");
}
int main(int argc, char* args[]) {
	
	
	bool check = false;

	SDL_Event e;
	gan();
	
	if(SDL_Init(SDL_INIT_EVERYTHING) !=0) {
		cout<<"Error";
	} else {
		window = SDL_CreateWindow("Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_FOREIGN);
		surface = SDL_GetWindowSurface( window);
		SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 236, 188, 208));
		SDL_UpdateWindowSurface( window);
		
		while(!check ) {
			while( SDL_PollEvent( &e) !=0) {
				if( e.type == SDL_QUIT) {
					check = true;
				} else if(e.type == SDL_KEYDOWN) {
					switch (e.key.keysym.sym)
					{
					case SDLK_UP:
						current = Key[demo1];
						break;
					case SDLK_DOWN:
						current = Key[demo2];
						break;
					default:
						current = Key[demo];
						break;
					}
				}
			}
			SDL_BlitSurface(current, NULL, surface, NULL);
			SDL_UpdateWindowSurface( window);
		}

	}
	SDL_DestroyWindow( window);
	SDL_Quit();
	return 0;
}