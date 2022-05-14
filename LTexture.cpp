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
	int w;
	int h;
	int x;
	int y;
public:
	//Initializes variables
	LTexture() {
		this->Texture = NULL;
		this -> w = 0;
		this -> h = 0;
		this->x = 0;
		this->y = 0;
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
				this -> w = loadSurface -> w;
				this -> h = loadSurface -> h;
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
				this->w = textSurface->w;
				this->h = textSurface->h;
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
			this -> w = 0;
			this -> h = 0;
		}
	}
	//Renders texture at given point
	void render(SDL_Renderer* Renderer, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE) {
		this->x = x;
		this->y = y;
		SDL_Rect render_space = {x, y, this -> w, this -> h};
		if (clip != NULL) {
			render_space.w = clip -> w;
			render_space.h = clip -> h;
		}
		SDL_RenderCopyEx(Renderer, this -> Texture, clip, &render_space, angle, center, flip);
	}		
	//Gets image dimensions
	int getW() {
		return this -> w;
	}
	int getH() {
		return this -> h;
	}
	int getX() {
		return this->x;
	}
	int getY() {
		return this->y;
	}
	SDL_Texture* getTexture() {
		return this->Texture;
	}
};