#pragma once
#include "Textbox.h"

Textbox::Textbox () {
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = 0;
    rect.h = 0;
    InputBox = rect;
    InputText = "";
    state = false;
    type = 0;
}

MyTexture Textbox::getTag() {
    return Tag;
}

void Textbox::setTag (SDL_Renderer* Renderer, string Name_Tag, SDL_Color Text_Color, TTF_Font* Font) {
    Tag.loadFromRenderedText(Renderer, Name_Tag, Text_Color, Font);
}

void Textbox::renderTag (SDL_Renderer* Renderer, int x, int y) {
    Tag.render(Renderer, x, y);
}

int Textbox::getInputBoxX() {
    return InputBox.x;
}

int Textbox::getInputBoxY() {
    return InputBox.y;
}

int Textbox::getInputBoxW() {
    return InputBox.w;
}

int Textbox::getInputBoxH() {
    return InputBox.h;
}

void Textbox::renderInputBox(SDL_Renderer* Renderer) {
    InputBox.h = Tag.getH();
    InputBox.w = 600;
    InputBox.x = Tag.getX() + Tag.getW();
    InputBox.y = Tag.getY();
    SDL_SetRenderDrawColor(Renderer, 63, 59, 55, 255);
    SDL_RenderDrawRect(Renderer, &InputBox);
}

void Textbox::renderInputBox(SDL_Renderer* Renderer, int w) {
    InputBox.h = Tag.getH();
    InputBox.w = w;
    InputBox.x = Tag.getX() + Tag.getW();
    InputBox.y = Tag.getY();
    SDL_SetRenderDrawColor(Renderer, 63, 59, 55, 255);
    SDL_RenderDrawRect(Renderer, &InputBox);
}

void Textbox::render(SDL_Renderer* Renderer, string tag, int x, int y, SDL_Color text_color, TTF_Font* font) {
    setTag(Renderer, tag, text_color, font);
    renderTag(Renderer, x, y);
    renderInputBox(Renderer);
}

void Textbox::render(SDL_Renderer* Renderer, string tag, int x, int y, int w, SDL_Color text_color, TTF_Font* font) {
    setTag(Renderer, tag, text_color, font);
    renderTag(Renderer, x, y);
    renderInputBox(Renderer, w);
}

bool Textbox::isMouseInside(int &x, int &y) {
    if ((x >= getInputBoxX() && x <= (getInputBoxX() + getInputBoxW())) && (y >= getInputBoxY() && y <= (getInputBoxY() + getInputBoxH()))) {
        return true;
    } else {
        return false;
    }
}

string Textbox::getInputText () {
    return InputText;
}

void Textbox::setInputText (string text) {
    InputText = text;
}

void Textbox::popInputText() {
    InputText.pop_back();
}

void Textbox::updateInputText (char* ch) {
    InputText += ch;
    std::cout << InputText << endl;
}

void Textbox::renderInputText (SDL_Renderer* Renderer, TTF_Font* textFont, SDL_Color textColor) {
    if (InputText != "") {
        if (type == 0) {
            Input.loadFromRenderedText(Renderer, InputText, textColor, textFont);
        }
        else {
            string temp = "";
            for (int i = 0; i < InputText.length(); i++) {
                temp += '*';
            }
            Input.loadFromRenderedText(Renderer, temp, textColor, textFont);
        }
    }
    else {
        Input.loadFromRenderedText(Renderer, " ", textColor, textFont);
    }
    Input.render(Renderer, getInputBoxX(), getInputBoxY());
}

bool Textbox::getState() {
    return state;
}

void Textbox::setState(bool State) {
    state = State;
}

int Textbox::getType() {
    return type;
}

void Textbox::setType(int Type) {
    type = Type;
}

void Textbox::changeType() {
    if (type == 0) {
        type = 1;
    }
    else {
        type = 0;
    }
}
void Textbox::free() {
    Tag.free();
    Input.free();
    InputText = "";
}
