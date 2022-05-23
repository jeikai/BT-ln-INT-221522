#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

using namespace std;

class MyTexture {

private:
	SDL_Texture* Texture;
	int x, y, w, h;

public:
	MyTexture();

	~MyTexture();

	bool loadFromFile(SDL_Renderer* Renderer, string path);

#if defined(SDL_TTF_MAJOR_VERSION)
	bool loadFromRenderedText(SDL_Renderer* Renderer, string text, SDL_Color color, TTF_Font* font);
#endif

	void render(SDL_Renderer* Renderer, int X, int Y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	int getX();

	int getY();

	int getW();

	int getH();

	SDL_Texture* getTexture();

	void free();
};
