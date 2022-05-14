#include "Button.cpp"
#include "Textbox.cpp"
#include <vector>

SDL_Window* Window = NULL;
SDL_Renderer* Renderer = NULL;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

LTexture Background;
LTexture Apptitle;

TTF_Font* Title_Font = NULL;
TTF_Font* Content_Font = NULL;

SDL_Color text_color = {63,59,55};

Button sign_in;
Button sign_up;
Button toggle_password;

bool init() {
    bool check = true;
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
        check = false;
    } else {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            cout << "Warning: Linear texture filtering not enabled!" << SDL_GetError() << endl;
        } 
        Window = SDL_CreateWindow("Support Assist", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (Window == NULL) {
            cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
            check = false;
        } else {
            Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (Renderer == NULL) {
                cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
                check = false;
            } else {
                SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
                int imgFlag = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlag) & imgFlag)) {
                    cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError << endl;
                    check = false;
                }
                if (TTF_Init() == -1) {
                    cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << endl;
                    check = false;
                }
                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
                    cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
                    check = false;
                }
            }
        }
    }
    return check;
}

bool Start_Screen () {
    bool check = true;
    Background.loadFromFile(Renderer, "D:/MyProject/anh/background.jpg");
    Title_Font = TTF_OpenFont("D:/MyProject/font/Roboto-Medium.ttf", 60);
    Content_Font = TTF_OpenFont("D:/MyProject/font/Roboto-Medium.ttf", 40);
    if (Title_Font == NULL || Content_Font == NULL) {
        cout << "Failed to load text font! SDL_ttf Error: " << TTF_GetError() << endl;
        check = false;
    } else {
        Apptitle.loadFromRenderedText(Renderer, "Support Assist", text_color, Title_Font);
        sign_in.createButton(Renderer, "D:/MyProject/anh/signin.png", (SCREEN_WIDTH - 600)/2, SCREEN_HEIGHT/1.5);
        sign_up.createButton(Renderer, "D:/MyProject/anh/signup.png", (SCREEN_WIDTH - 600)/2 + 400, SCREEN_HEIGHT/1.5);
        toggle_password.createButton(Renderer, "D:/MyProject/anh/toggle_password.png", 1040, 360);
        toggle_password.setButtonState(BUTTON_STATE_MOUSE_OUTSIDE);
    }
    return check;
}

void close() {
    SDL_StopTextInput();
    sign_in.free();
    sign_up.free();
    TTF_CloseFont(Title_Font);
    Title_Font = NULL;
    TTF_CloseFont(Content_Font);
    Content_Font = NULL;
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    Window = NULL;
    Renderer = NULL;
    Mix_Quit();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

int main(int argc, char* args[]) {
    if (!init()) {
        cout << "Failed to initialize" << endl;
    } else {
        if (!Start_Screen()) {
            cout << "Failed to load start screen" << endl;
        } else {
            bool quit = false;
            SDL_Event ev;
            vector<TextBox> All_Textbox(2);
            All_Textbox[1].setType(1);
            while (quit == false) {
                //SDL_RenderClear(Renderer);
                Background.render(Renderer, 0, 0);
                Apptitle.render(Renderer, (SCREEN_WIDTH - Apptitle.getW())/2, SCREEN_HEIGHT/5.5);
                All_Textbox[0].render(Renderer, "Username: ", (SCREEN_WIDTH - All_Textbox[0].getTag().getW() - 600) / 2, SCREEN_HEIGHT / 3.0, text_color, Content_Font);
                All_Textbox[1].render(Renderer, "Password: ", (SCREEN_WIDTH - All_Textbox[1].getTag().getW() - 600) / 2, SCREEN_HEIGHT / 2.0, text_color, Content_Font);
                int pos;
                toggle_password.render(Renderer);
                sign_in.render(Renderer);
                sign_up.render(Renderer);
                while (SDL_PollEvent(&ev) != 0) {
                    if (ev.type == SDL_QUIT) {
                        quit = true;
                    } else if (ev.type == SDL_MOUSEBUTTONDOWN) {
                        cout << "mouse pressed" << endl;
                        for (int i = 0; i < All_Textbox.size(); i++) {
                            if (All_Textbox[i].is_mouse_inside(ev.button.x, ev.button.y) == true) {
                                All_Textbox[i].setState(true);
                                pos = i;
                                cout << pos << endl;
                            }
                            else {
                                All_Textbox[i].setState(false);
                            }
                        }
                        if (toggle_password.isInside(ev.button.x, ev.button.y) == true) {
                            if (toggle_password.getCurrentState() == BUTTON_STATE_MOUSE_OUTSIDE) {
                                toggle_password.setButtonState(BUTTON_STATE_MOUSE_OVER_MOTION);
                                All_Textbox[1].setType(0);
                            }
                            else {
                                toggle_password.setButtonState(BUTTON_STATE_MOUSE_OUTSIDE);
                                All_Textbox[1].setType(1);
                            }
                        }
                    } else if (ev.type == SDL_KEYDOWN) {
                        if (ev.key.keysym.sym == SDLK_BACKSPACE && All_Textbox[pos].getInputText().length() > 0) {
                            if (All_Textbox[pos].getState() == true) {
                                All_Textbox[pos].inputPop();
                            }
                        }
                    } else if (ev.type == SDL_TEXTINPUT) {
                        if (!(SDL_GetModState() & KMOD_CTRL && (ev.text.text[0] == 'c' || ev.text.text[0] == 'C' || ev.text.text[0] == 'v' || ev.text.text[0] == 'V'))) {
                            if (All_Textbox[pos].getState() == true) {
                                All_Textbox[pos].updateInputText(ev.text.text);
                            }
                        }
                    }
                    sign_in.handleEvent(Renderer, &ev);
                    sign_up.handleEvent(Renderer, &ev);
                }
                for (int i = 0; i < All_Textbox.size(); i++) {
                    if (All_Textbox[i].getInputText().length() != 0) {
                        All_Textbox[i].renderInputText(Renderer, Content_Font, text_color);
                    }
                }
                SDL_RenderPresent(Renderer);
            }
        }
    }
    close();
    return 0;
}