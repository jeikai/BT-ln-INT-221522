#include "Button.h"

Button::Button() {
	Position.x = 0;
	Position.y = 0;
	CurrentState = BUTTON_STATE_MOUSE_OUTSIDE;
}

bool Button::loadTexture(SDL_Renderer* Renderer, string path) {
	return Texture.loadFromFile(Renderer, path);
}
	
//Sets top left position
void Button::setPosition(double x, double y) {
	Position.x = x;
	Position.y = y;
}

void Button::setShape () {
	for (int i = 0; i < 3; i++) {
		Shape[i].x = 0;
		Shape[i].y = i*100;
		Shape[i].w = BUTTON_WIDTH;
		Shape[i].h = BUTTON_HEIGHT;
	}
}

void Button::setShape(int w, int h) {
	for (int i = 0; i < 3; i++) {
		Shape[i].x = 0;
		Shape[i].y = i * h;
		Shape[i].w = w;
		Shape[i].h = h;
	}
}
	
ButtonState Button::getState() {
	return CurrentState;
}
	
void Button::setState(ButtonState n) {
	CurrentState = n;
}
	
bool Button::isInside(int x, int y) {
	if (x < Position.x || x > Position.x + Shape[0].w || y < Position.y || y > Position.y + Shape[0].h) {
		return false;
	}
	return true;
}

//Shows button sprite
void Button::render(SDL_Renderer* Renderer) {
	Texture.render(Renderer, this -> Position.x, this -> Position.y, &this -> Shape[CurrentState]);
}
	
bool Button::createButton (SDL_Renderer* Renderer, string path, int x, int y) {
	if (!loadTexture(Renderer, path)) {
		cout << "Failed to load button sprite texture!" << endl;
		return false;
	} 
	else {
		setShape();
		setPosition(x, y);
	}
	return true;
}
	
bool Button::createButton(SDL_Renderer* Renderer, string path, int x, int y, int w, int h) {
	if (!loadTexture(Renderer, path)) {
		cout << "Failed to load button sprite texture!" << endl;
		return false;
	}
	else {
		setShape(w, h);
		setPosition(x, y);
	}
	return true;
}

void Button::free() {
	Texture.free();
}

int Button::getX() {
	return Position.x;
}

int Button::getY() {
	return Position.y;
}