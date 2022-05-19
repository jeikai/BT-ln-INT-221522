#pragma once
#include "LTexture.cpp"

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

//The mouse button
class Button {
	SDL_Point Position;
	//Currently used global sprite
	ButtonState CurrentState;
	SDL_Rect Shape[BUTTON_STATE_TOTAL];
	LTexture TEXTURE;
public:
	//Initializes internal variables
	Button() {
		this -> Position.x = 0;
		this -> Position.y = 0;
		this -> CurrentState = BUTTON_STATE_MOUSE_OUTSIDE;
	}
	bool loadTexture(SDL_Renderer* Renderer, string path) {
		return this -> TEXTURE.loadFromFile(Renderer, path);
	}
	//Sets top left position
	void setPosition(double x, double y) {
		this -> Position.x = x;
		this -> Position.y = y;
	}
	void setShape () {
		for (int i = 0; i < 3; i++) {
			this -> Shape[i].x = 0;
			this -> Shape[i].y = i*100;
			this -> Shape[i].w = BUTTON_WIDTH;
			this -> Shape[i].h = BUTTON_HEIGHT;
		}
	}
	void setShape(int w, int h) {
		for (int i = 0; i < 3; i++) {
			this->Shape[i].x = 0;
			this->Shape[i].y = i * 100;
			this->Shape[i].w = w;
			this->Shape[i].h = h;
		}
	}
	ButtonState getCurrentState() {
		return this->CurrentState;
	}
	void setButtonState(ButtonState n) {
		this->CurrentState = n;
	}
	bool isInside(int x, int y) {
		if (x < this->Position.x || x > this->Position.x + BUTTON_WIDTH
			|| y < this->Position.y
			|| y > this->Position.y + BUTTON_HEIGHT) {
			return false;
		}
		return true;
	}
	//Handles mouse event
	void handleEvent(SDL_Renderer* Renderer, SDL_Event* event) {
		if (event -> type == SDL_MOUSEMOTION || event -> type == SDL_MOUSEBUTTONDOWN
										     || event -> type == SDL_MOUSEBUTTONUP) {
			int x, y;
			SDL_GetMouseState (&x, &y);
			if (this->isInside(x, y) == true) {
				switch (event -> type) {
					case SDL_MOUSEMOTION:
						CurrentState = BUTTON_STATE_MOUSE_OVER_MOTION;
						break;
					case SDL_MOUSEBUTTONDOWN:
						CurrentState = BUTTON_STATE_MOUSE_CLICK;
						break;
					case SDL_MOUSEBUTTONUP:
						CurrentState = BUTTON_STATE_MOUSE_REALEASE;
						this -> free();
						break;
				}
			}
		}
	}
	//Shows button sprite
	void render(SDL_Renderer* Renderer) {
		this -> TEXTURE.render(Renderer, this -> Position.x, this -> Position.y, &this -> Shape[CurrentState]);
	}
	void free() {
		this -> TEXTURE.free();
 	}
	bool createButton (SDL_Renderer* Renderer, string path, double x, double y) {
		if (!this -> loadTexture(Renderer, path)) {
			cout << "Failed to load button sprite texture!" << endl;
			return false;
		} else {
			this -> setShape();
			this -> setPosition(x, y);
		}
		return true;
	}
	bool createButton(SDL_Renderer* Renderer, string path, double x, double y, int w, int h) {
		if (!this->loadTexture(Renderer, path)) {
			cout << "Failed to load button sprite texture!" << endl;
			return false;
		}
		else {
			this->setShape(w, h);
			this->setPosition(x, y);
		}
		return true;
	}
};