#include "MyTexture.h"

MyTexture::MyTexture() {
	Texture = NULL;
	x = 0;
	y = 0;
	h = 0;
	w = 0;
}

MyTexture::~MyTexture() {
	free();
}

bool MyTexture::loadFromFile(SDL_Renderer* Renderer, string path) {
	free();
	SDL_Texture* tempTexture = NULL;
	SDL_Surface* loadSurface = IMG_Load(path.c_str());
	if (loadSurface == NULL) {
		cout << "Unable to load image! SDL_image Error: " << path << IMG_GetError() << endl;
	}
	else {
		SDL_SetColorKey(loadSurface, SDL_TRUE, SDL_MapRGB(loadSurface->format, 0, 0xFF, 0xFF)); //color key image
		tempTexture = SDL_CreateTextureFromSurface(Renderer, loadSurface); //create texture from temporary surface
		if (tempTexture == NULL) {
			cout << "Unable to create texture from surface! SDL Error: " << path << SDL_GetError() << endl;
		}
		else {
			w = loadSurface->w;
			h = loadSurface->h;
		}
		SDL_FreeSurface(loadSurface); //free temporary surface
	}
	Texture = tempTexture;
	return Texture != NULL;
}

#if defined (SDL_TTF_MAJOR_VERSION) 
bool MyTexture::loadFromRenderedText(SDL_Renderer* Renderer, string textureText, SDL_Color textColor, TTF_Font* font) {
	free(); //delete preexisting texture
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
			w = textSurface->w;
			h = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
	}
	Texture = tempTexture;
	return Texture != NULL;
}
#endif

void MyTexture::render(SDL_Renderer* Renderer, int X, int Y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
	x = X;
	y = Y;
	SDL_Rect render_space = { X, Y, w, h };
	if (clip != NULL) {
		render_space.w = clip->w;
		render_space.h = clip->h;
	}
	SDL_RenderCopyEx(Renderer, Texture, clip, &render_space, angle, center, flip);
}

int MyTexture::getX() {
	return x;
}

int MyTexture::getY() {
	return y;
}

int MyTexture::getH() {
	return h;
}

int MyTexture::getW() {
	return w;
}

SDL_Texture* MyTexture::getTexture() {
	return Texture;
}

void MyTexture::free() {
	if (Texture != NULL) {
		SDL_DestroyTexture(Texture);
		Texture = NULL;
		x = 0;
		y = 0;
		w = 0;
		h = 0;
	}
}