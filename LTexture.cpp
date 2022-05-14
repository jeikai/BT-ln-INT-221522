#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
using namespace std;

class LTexture {
    //The actual hardware texture
	SDL_Texture* Texture;
	//Image dimensions
	int Width;
	int Height;
public:
		//Initializes variables
		LTexture() {
			this->Texture = NULL;
			this -> Width = 0;
			this -> Height = 0;
		}
		//Deallocates memory
		~LTexture() {
			this -> free();
		}
		//Loads image from file
		bool loadFromFile (SDL_Renderer* Renderer, string path) {
			this -> free(); //free preexisting texture
			SDL_Texture* tempTexture = NULL;
			SDL_Surface* loadSurface = IMG_Load(path.c_str()); //temporary surface to load;
			if (loadSurface == NULL) {
				cout << "Unable to load image! SDL_image Error: " << path << IMG_GetError() << endl;
			} else {
				SDL_SetColorKey (loadSurface, SDL_TRUE, SDL_MapRGB (loadSurface -> format, 0, 0xFF, 0xFF)); //color key image
				tempTexture = SDL_CreateTextureFromSurface(Renderer, loadSurface); //create texture from temporary surface
				if (tempTexture == NULL) {
					cout << "Unable to create texture from surface! SDL Error: " << path << SDL_GetError() << endl; 
				} else {
					this -> Width = loadSurface -> w;
					this -> Height = loadSurface -> h;
				}			
				SDL_FreeSurface(loadSurface); //free temporary surface
			}
			this -> Texture = tempTexture;
			return this -> Texture != NULL;
		}
		#if defined(SDL_TTF_MAJOR_VERSION)
		//Creates image from string
		bool loadFromRenderedText(SDL_Renderer* Renderer, string textureText, SDL_Color textColor, TTF_Font* font) {
			this->free(); //delete preexisting texture
			SDL_Texture* tempTexture = NULL;
			SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
			if (textSurface == NULL) {
				cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << endl;
			}
			else {
				tempTexture = SDL_CreateTextureFromSurface(Renderer, textSurface);
				if (tempTexture == NULL) {
					cout << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << endl;
				}
				else {
					this->Width = textSurface->w;
					this->Height = textSurface->h;
				}
				SDL_FreeSurface(textSurface);
			}
			this->Texture = tempTexture;
			return this -> Texture != NULL;
		}
		#endif
		//Deallocates texture
		void free() {
			if (this -> Texture != NULL) {
				SDL_DestroyTexture(this -> Texture);
				this -> Texture = NULL;
				this -> Width = 0;
				this -> Height = 0;
			}
		}
		//Renders texture at given point
		void render(SDL_Renderer* Renderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) {
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
		SDL_Texture* getTexture() {
			return this->Texture;
		}
};