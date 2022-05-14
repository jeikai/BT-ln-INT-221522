#pragma once
#include <iostream>
#include <SDL.h>
#include "LTexture.cpp"
using namespace std;

class TextBox {
    SDL_Rect input_box;
    LTexture box;
    string InputText;
    LTexture Tag;
    LTexture Input;
    bool state;
public: 
    TextBox () {
        SDL_Rect rect;
        rect.x = 0;
        rect.y = 0;
        rect.w = 0;
        rect.h = 0;
        this->input_box = rect;
        this -> InputText = "";
        this -> state = false;
    }
    void Set_TextBox_Tag (SDL_Renderer* Renderer, string Name_Tag, SDL_Color Text_Color, TTF_Font* Font) {
        this -> Tag.loadFromRenderedText(Renderer, Name_Tag, Text_Color, Font);
    }
    void Render_TextBox_Tag (SDL_Renderer* &Renderer, int x, int y) {
        this -> Tag.render(Renderer, x, y);
    }
    LTexture getTag() {
        return this -> Tag;
    }
    //void Draw_Input_Box (SDL_Renderer* &Renderer, string path, const int SCREEN_WIDTH, const int SCREEN_HEIGHT, int y) {
    //    this -> input_box.h = this -> Tag.getHeight();
    //    this -> input_box.w = 600;
    //    this -> input_box.x = (SCREEN_WIDTH - this -> Tag.getWidth() - 600)/2 + this -> Tag.getWidth();
    //    this -> input_box.y = y;
    //    if (this->box.loadFromFile(Renderer, path) == false) {
    //        cout << "Could not draw text box from file" << endl;
    //    } else {
    //        SDL_RenderCopy(Renderer, this->box.getTexture(), NULL, &this->input_box);
    //    }
    //}
    void Draw_Input_Box(SDL_Renderer* Renderer, const int SCREEN_WIDTH, const int SCREEN_HEIGHT, int y) {
        this->input_box.h = this->Tag.getHeight();
        this->input_box.w = 600;
        this->input_box.x = (SCREEN_WIDTH - this->Tag.getWidth() - 600) / 2 + this->Tag.getWidth();
        this->input_box.y = y;
        SDL_SetRenderDrawColor(Renderer, 63, 59, 55, 255);
        SDL_RenderDrawRect(Renderer, &this->input_box);
    }
    int get_input_box_w () {
        return this -> input_box.w;
    }
    int get_input_box_h () {
        return this -> input_box.h;
    }
    int get_input_box_x () {
        return this -> input_box.x;
    }
    int get_input_box_y () {
        return this -> input_box.y;
    }
    bool is_mouse_inside(int &x, int &y) {
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
    void renderInputText (SDL_Renderer* Renderer, TTF_Font* textFont, SDL_Color textColor) {

        if (this -> InputText != "") {
            this -> Input.loadFromRenderedText(Renderer, this -> InputText, textColor, textFont);
        } else {
            this -> Input.loadFromRenderedText(Renderer, " ", textColor, textFont);
        }
        this -> Input.render(Renderer, this -> get_input_box_x(), this -> get_input_box_y());
    }
    void setState(bool state) {
        this -> state = state;
    }
    bool getState () {
        return this -> state;
    }
};
