#pragma once

#include "MyTexture.h"

enum ButtonState {
	BUTTON_STATE_MOUSE_OUTSIDE = 0,
	BUTTON_STATE_MOUSE_OVER_MOTION = 1,
	BUTTON_STATE_MOUSE_CLICK = 2,
	BUTTON_STATE_MOUSE_REALEASE = 3,
	BUTTON_STATE_TOTAL = 4
};

//Button constants
const int BUTTON_WIDTH = 200;
const int BUTTON_HEIGHT = 100;

class Button {

private:
	SDL_Point Position;
	ButtonState CurrentState;
	SDL_Rect Shape[BUTTON_STATE_TOTAL];
	MyTexture Texture;

public:
	Button();

	bool loadTexture(SDL_Renderer* Renderer, string path);
	
	void setPosition(double x, double y);

	void setShape();

	void setShape(int w, int h);

	ButtonState getState();

	void setState(ButtonState n);

	bool isInside(int x, int y);

	void render(SDL_Renderer* Renderer);

	bool createButton(SDL_Renderer* Renderer, string path, int x, int y);

	bool createButton(SDL_Renderer* Renderer, string path, int x, int y, int w, int h);

	void free();

	int getX();

	int getY();
};