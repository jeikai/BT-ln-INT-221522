#pragma once
#include <bits/stdc++.h>
#include <sstream>
#include <SDL.h>
#include "LTexture.cpp"

class TextBox {
    SDL_Rect *input_box;
    string InputText;
    LTexture Tag;
    SDL_Event* event;
    LTexture *Input;
    bool state;
public: 
    TextBox () {
        this -> InputText = "";
        this -> state = false;
    }
    void Set_TextBox_Tag (string Name_Tag, SDL_Color Text_Color, TTF_Font* Font) {
        this -> Tag.loadFromRenderedText(Name_Tag, Text_Color, Font);
    }
    void Render_TextBox_Tag (int x, int y) {
        this -> Tag.render(x, y);
    }
    LTexture getTag() {
        return this -> Tag;
    }
    void Draw_Input_Box (const int SCREEN_WIDTH, const int SCREEN_HEIGHT) {
        this -> input_box -> h = this -> Tag.getHeight();
        this -> input_box -> w = 600;
        this -> input_box -> x = (SCREEN_WIDTH - this -> Tag.getWidth() - 600)/2 + this -> Tag.getWidth();
        this -> input_box -> y = SCREEN_HEIGHT/3.0;
        SDL_SetRenderDrawColor(Renderer, 63, 59, 55, 255);
        SDL_RenderDrawRect(Renderer, this -> input_box);
    }
    int get_input_box_w () {
        return this -> input_box -> w;
    }
    int get_input_box_h () {
        return this -> input_box -> h;
    }
    int get_input_box_x () {
        return this -> input_box -> x;
    }
    int get_input_box_y () {
        return this -> input_box -> y;
    }
    bool is_mouse_inside(int &x, int &y) {
        //SDL_GetMouseState(&x, &y);
        if ((x >= this -> get_input_box_x() && x <= (this -> get_input_box_x() + this -> get_input_box_w())) && (y >= this -> get_input_box_y() && y <= (this -> get_input_box_y() + this -> get_input_box_h()))) {
            return true;
        } else {
            return false;
        }
    }
    string getInputText () {
        return this -> InputText;
    }
    void setInputText (string InputText) {
        this -> InputText = InputText;
    } 
    void inputPop() {
        this -> InputText.pop_back();
    }
    void updateInputText (char* ch) {
        this -> InputText += ch;
        std::cout << this -> InputText << endl;
    }
    void renderInputText (TTF_Font* textFont, SDL_Color textColor) {

        if (this -> InputText != "") {
            this -> Input -> loadFromRenderedText(this -> InputText, textColor, textFont);
        } else {
            this -> Input -> loadFromRenderedText(" ", textColor, textFont);
        }
        this -> Input -> render(this -> get_input_box_x(), this -> get_input_box_y());
    }
    void setState(bool state) {
        this -> state = state;
    }
    bool getState () {
        return this -> state;
    }
};
