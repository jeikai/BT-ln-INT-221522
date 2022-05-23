#pragma once

#include "MyTexture.h"

class Textbox {

private:
	MyTexture Tag, Input;
	SDL_Rect InputBox;
	string InputText;
	bool state; //active or not
	int type;
	/*
	type = 0 (public)
	type = 1 (protected)
	*/

public:
	Textbox();

	MyTexture getTag();

	void setTag(SDL_Renderer* Renderer, string tag, SDL_Color color, TTF_Font* font);

	void renderTag(SDL_Renderer* Renderer, int x, int  y);

	int getInputBoxX();

	int getInputBoxY();

	int getInputBoxW();

	int getInputBoxH();

	void renderInputBox(SDL_Renderer* Renderer);
	
	void renderInputBox(SDL_Renderer* Renderer, int w);

	void render(SDL_Renderer* Renderer, string tag, int x, int y, SDL_Color color, TTF_Font* font);

	void render(SDL_Renderer* Renderer, string tag, int x, int y, int w, SDL_Color color, TTF_Font* font);

	bool isMouseInside(int& x, int& y);

	string getInputText();

	void setInputText(string text);

	void popInputText();

	void updateInputText(char* ch);

	void renderInputText(SDL_Renderer* Renderer, TTF_Font* font, SDL_Color color);

	bool getState();

	void setState(bool State);

	int getType();

	void setType(int Type);

	void changeType();

	void free();
};