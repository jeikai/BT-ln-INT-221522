#pragma once

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
using namespace std;

SDL_Renderer* Renderer = NULL;
// //Music
Mix_Chunk * transition = NULL;

class LTexture {
    //The actual hardware texture
	SDL_Texture* Texture;
	//Image dimensions
	int Width;
	int Height;
public:
		//Initializes variables
		LTexture() {
			this -> Texture = NULL;
			this -> Width = 0;
			this -> Height = 0;
		}
		//Deallocates memory
		~LTexture() {
			this -> free();
		}
		//Loads image from file
		bool loadFromFile (string path) {
			this -> free(); //free preexisting texture
			SDL_Surface* loadSurface = IMG_Load(path.c_str()); //temporary surface to load;
			if (loadSurface == NULL) {
				cout << "Unable to load image! SDL_image Error: " << endl << path << IMG_GetError();
			} else {
				SDL_SetColorKey(loadSurface, SDL_TRUE, SDL_MapRGB(loadSurface -> format, 0, 0xFF, 0xFF)); //color key image
				this -> Texture = SDL_CreateTextureFromSurface(Renderer, loadSurface); //create texture from temporary surface
				if (this -> Texture == NULL) {
					cout << "Unable to create texture from surface! SDL Error: " << endl << path << SDL_GetError(); 
				} else {
					this -> Width = loadSurface -> w;
					this -> Height = loadSurface -> h;
				}			
				SDL_FreeSurface(loadSurface); //free temporary surface
			}
			return this -> Texture != NULL;
		}
		//Creates image from font string
		bool loadFromRenderedText(string textureText, SDL_Color textColor, TTF_Font* font) {
			this -> free(); //delete preexisting texture
			SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
			if (textSurface == NULL) {
				cout << "Unable to render text surface! SDL_ttf Error: " << endl << TTF_GetError();
			} else {
				this -> Texture = SDL_CreateTextureFromSurface(Renderer, textSurface);
				if (this -> Texture == NULL) {
					cout << "Unable to create texture from rendered text! SDL Error: " << endl << SDL_GetError();
				} else {
					this -> Width = textSurface -> w;
					this -> Height = textSurface -> h;
				}
				SDL_FreeSurface(textSurface);
			}
			return this -> Texture != NULL;
		}
		//Deallocates texture
		void free() {
			if (this -> Texture == NULL) {
				SDL_DestroyTexture(this -> Texture);
				this -> Texture = NULL;
				this -> Width = 0;
				this -> Height = 0;
			}
		}
		//Renders texture at given point
		// void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) {
		// 	SDL_Rect render_space = {x, y, this -> Width, this -> Height};
		// 	if (clip != NULL) {
		// 		render_space.w = clip -> w;
		// 		render_space.h = clip -> h;
		// 	}
		// 	SDL_RenderCopyEx(Renderer, this -> Texture, clip, &render_space, angle, center, flip);
		// }
		void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) {
			SDL_Rect render_space = {x, y, this -> Width, this -> Height};
			if (clip != NULL) {
				render_space.w = clip -> w;
				render_space.h = clip -> h;
			}
			SDL_RenderCopyEx(Renderer, this -> Texture, clip, &render_space, angle, center, flip);
		}		
		//Gets image dimensions
		int getWidth() {
			return this -> Width;
		}
		int getHeight() {
			return this -> Height;
		}
};

// void LTexture::free() {
// 	//Free texture if it exists
// 	if (Texture != NULL) {
// 		SDL_DestroyTexture (Texture);
// 		Texture = NULL;
// 		Width = 0;
// 		Height = 0;
// 		transition = NULL;
// 	}
// }

// void LTexture::render (int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
// 	//Set rendering space and render to screen
// 	SDL_Rect renderQuad = {x, y, Width, Height};
// 	//Set clip rendering dimensions
// 	if(clip != NULL) {
// 		renderQuad.w = clip -> w;
// 		renderQuad.h = clip -> h;
// 	}
// 	//Render to screen
// 	SDL_RenderCopyEx(Renderer, Texture, clip, &renderQuad, angle, center, flip);
// }
