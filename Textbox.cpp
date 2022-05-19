#pragma once
#include "LTexture.cpp"

class TextBox {
    LTexture Tag;
    SDL_Rect input_box;
    string InputText;
    LTexture Input;
    bool state;
    int type;
    /*
    type = 0 (public)
    type = 1 (protected)
    */
public: 
    TextBox () {
        SDL_Rect rect;
        rect.x = 0;
        rect.y = 0;
        rect.w = 0;
        rect.h = 0;
        this->input_box = rect;
        this->InputText = "";
        this->state = false;
        this->type = 0;
    }
    void Set_Tag (SDL_Renderer* Renderer, string Name_Tag, SDL_Color Text_Color, TTF_Font* Font) {
        this -> Tag.loadFromRenderedText(Renderer, Name_Tag, Text_Color, Font);
    }
    void Render_Tag (SDL_Renderer* Renderer, int x, int y) {
        this -> Tag.render(Renderer, x, y);
    }
    LTexture getTag() {
        return this -> Tag;
    }
    void Render_InputBox(SDL_Renderer* Renderer) {
        this->input_box.h = this->Tag.getH();
        this->input_box.w = 600;
        this->input_box.x = this->Tag.getX() + this->Tag.getW();
        this->input_box.y = this->Tag.getY();
        SDL_SetRenderDrawColor(Renderer, 63, 59, 55, 255);
        SDL_RenderDrawRect(Renderer, &this->input_box);
    }
    void render(SDL_Renderer* Renderer, string tag, int x, int y, SDL_Color text_color, TTF_Font* font) {
        //this->type = type;
        this->Set_Tag(Renderer, tag, text_color, font);
        this->Render_Tag(Renderer, x, y);
        this->Render_InputBox(Renderer);
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
        if (this->InputText != "") {
            if (this->type == 0) {
                this->Input.loadFromRenderedText(Renderer, this->InputText, textColor, textFont);
            }
            else {
                string temp = "";
                for (int i = 0; i < this->InputText.length(); i++) {
                    temp += '*';
                }
                this->Input.loadFromRenderedText(Renderer, temp, textColor, textFont);
            }
        }
        else {
            this->Input.loadFromRenderedText(Renderer, " ", textColor, textFont);
        }
        this->Input.render(Renderer, this->get_input_box_x(), this->get_input_box_y());
    }
    void setState(bool state) {
        this -> state = state;
    }
    bool getState () {
        return this -> state;
    }
    int getType() {
        return this->type;
    }
    void setType(int type) {
        this->type = type;
    }
    void changeType() {
        if (this->type == 0) {
            this->type == 1;
        }
        else {
            this->type == 0;
        }
    }
    void free() {
        this->Tag.free();
        this->Input.free();
        this->InputText = "";
    }
};
