#include "Button.cpp"
#include "Textbox.cpp"
#include "Account.cpp"
#include <vector>

SDL_Window* Window = NULL;
SDL_Renderer* Renderer = NULL;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

TTF_Font* Title_Font = NULL;
TTF_Font* Content_Font = NULL;
TTF_Font* Warning_Font = NULL;

SDL_Color text_color = {63,59,55};
SDL_Color warning_color = { 211, 12, 7 };

LTexture Background;
LTexture Signin_Warning;
vector<LTexture> Signup_Warning(3);

Account User;

bool init() {
    bool check = true;
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << endl;
        check = false;
    }
    else {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            cout << "Warning: Linear texture filtering not enabled!" << SDL_GetError() << endl;
        }
        Window = SDL_CreateWindow("Support Assist", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (Window == NULL) {
            cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
            check = false;
        }
        else {
            Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (Renderer == NULL) {
                cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
                check = false;
            }
            else {
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

bool loadMedia() {
    if (Background.loadFromFile(Renderer, "D:/MyProject/anh/background.jpg") == false) {
        return false;
    }
    else {
        Title_Font = TTF_OpenFont("D:/MyProject/font/Roboto-Medium.ttf", 60);
        if (Title_Font == NULL) {
            cout << "Failed to load title font! SDL_ttf Error: " << TTF_GetError() << endl;
            return false;
        }
        Content_Font = TTF_OpenFont("D:/MyProject/font/Roboto-Medium.ttf", 40);
        if (Content_Font == NULL) {
            cout << "Failed to load content font! SDL_ttf Error: " << TTF_GetError() << endl;
            return false;
        }
        Warning_Font = TTF_OpenFont("D:/MyProject/font/Roboto-Medium.ttf", 30);
        if (Warning_Font == NULL) {
            cout << "Failed to load warning font! SDL_ttf Error: " << TTF_GetError() << endl;
            return false;
        }
    }
    return true;
}

enum Screen {
    Start = 0,
    SignUp = 1,
    Menu = 2
};

//Start screen's contents
LTexture Apptitle;
vector<TextBox> Start_Textbox(2);
Button sign_in;
Button sign_up;
Button toggle_password;

//Start screen's functions
void Start_Screen () {
    Apptitle.loadFromRenderedText(Renderer, "Support Assist", text_color, Title_Font);
    Start_Textbox[1].setType(1);
    sign_in.createButton(Renderer, "D:/MyProject/anh/signin.png", (SCREEN_WIDTH - 600) / 2, SCREEN_HEIGHT / 1.5);
    sign_up.createButton(Renderer, "D:/MyProject/anh/signup.png", (SCREEN_WIDTH - 600) / 2 + 400, SCREEN_HEIGHT / 1.5);
    toggle_password.createButton(Renderer, "D:/MyProject/anh/toggle_password.png", 1040, 360);
}

void Render_Start_Screen() {
    Background.render(Renderer, 0, 0);
    Apptitle.render(Renderer, (SCREEN_WIDTH - Apptitle.getW())/2, SCREEN_HEIGHT/5.5);
    Start_Textbox[0].render(Renderer, "Username: ", (SCREEN_WIDTH - Start_Textbox[0].getTag().getW() - 600) / 2, SCREEN_HEIGHT / 3.0, text_color, Content_Font);
    Start_Textbox[1].render(Renderer, "Password: ", (SCREEN_WIDTH - Start_Textbox[1].getTag().getW() - 600) / 2, SCREEN_HEIGHT / 2.0, text_color, Content_Font);    
    toggle_password.render(Renderer);
    sign_in.render(Renderer);
    sign_up.render(Renderer);
}

void Clear_Start_Screen() {
    Apptitle.free();
    for (int i = 0; i < 2; i++) {
        Start_Textbox[i].free();
    }
    Signin_Warning.free();
    toggle_password.free();
    sign_in.free();
    sign_up.free();
    SDL_RenderClear(Renderer);
}

//SignUp screen's contents
vector<TextBox> SignUp_Textbox(3);
vector<Button> Toggle_Switch(2);
Button Sign_up;

void Signup_Screen() {
    for (int i = 1; i < 3; i++) {
        SignUp_Textbox[i].setType(1);
    }
    Toggle_Switch[0].createButton(Renderer, "D:/MyProject/anh/toggle_password.png", 1040, SCREEN_HEIGHT/3);
    Toggle_Switch[1].createButton(Renderer, "D:/MyProject/anh/toggle_password.png", 1040, (11 * SCREEN_HEIGHT) / 20);
    Sign_up.createButton(Renderer, "D:/MyProject/anh/signup.png", (SCREEN_WIDTH - 600) / 2 + 400, SCREEN_HEIGHT / 1.5);
    Signup_Warning[0].loadFromRenderedText(Renderer, "Username already exits!", warning_color, Warning_Font);
    Signup_Warning[1].loadFromRenderedText(Renderer, "Password must have 5-20 letters including a special character!", warning_color, Warning_Font);
    Signup_Warning[2].loadFromRenderedText(Renderer, "Password doesn't match!", warning_color, Warning_Font);
}

void Render_Signup_Screen() {
    Background.render(Renderer, 0, 0);
    SignUp_Textbox[0].render(Renderer, "Username: ", (SCREEN_WIDTH - SignUp_Textbox[0].getTag().getW() - 600) / 2, SCREEN_HEIGHT / 4.0, text_color, Content_Font);
    SignUp_Textbox[1].render(Renderer, "Password: ", (SCREEN_WIDTH - SignUp_Textbox[1].getTag().getW() - 600) / 2, SCREEN_HEIGHT / 2.5, text_color, Content_Font);
    SignUp_Textbox[2].render(Renderer, "Password: ", (SCREEN_WIDTH - SignUp_Textbox[2].getTag().getW() - 600) / 2, (11*SCREEN_HEIGHT) / 20, text_color, Content_Font);
    for (int i = 0; i < 2; i++) {
        Toggle_Switch[i].render(Renderer);
    }
    Sign_up.render(Renderer);
}

void Clear_SignUp_Screen() {
    for (int i = 0; i < 3; i++) {
        Signup_Warning[i].free();
    }
    for (int i = 0; i < 3; i++) {
        SignUp_Textbox[i].free();
    }
    for (int i = 0; i < 2; i++) {
        Toggle_Switch[i].free();
    }
    Sign_up.free();
    SDL_RenderClear(Renderer);
}

//Menu's contents
Button Exit;

void handle_event(Screen& Current, bool& quit, SDL_Event& ev, int& pos, int& code) {
    while (SDL_PollEvent(&ev) != 0) {
        if (ev.type == SDL_QUIT) {
            quit = true;
            break;
        }
        else {
            switch (Current) {
            case Start:
                if (ev.type == SDL_MOUSEMOTION) {
                    if (sign_in.isInside(ev.button.x, ev.button.y)) {
                        sign_in.setButtonState(BUTTON_STATE_MOUSE_OVER_MOTION);
                    }
                    else {
                        sign_in.setButtonState(BUTTON_STATE_MOUSE_OUTSIDE);
                    }
                    if (sign_up.isInside(ev.button.x, ev.button.y)) {
                        sign_up.setButtonState(BUTTON_STATE_MOUSE_OVER_MOTION);
                    }
                    else {
                        sign_up.setButtonState(BUTTON_STATE_MOUSE_OUTSIDE);
                    }
                }
                else if (ev.type == SDL_MOUSEBUTTONDOWN) {
                    cout << "mouse pressed" << endl;
                    for (int i = 0; i < Start_Textbox.size(); i++) {
                        if (Start_Textbox[i].is_mouse_inside(ev.button.x, ev.button.y) == true) {
                            Start_Textbox[i].setState(true);
                            pos = i;
                            cout << pos << endl;
                        }
                        else {
                            Start_Textbox[i].setState(false);
                        }
                    }
                    if (sign_in.isInside(ev.button.x, ev.button.y)) {
                        sign_in.setButtonState(BUTTON_STATE_MOUSE_CLICK);
                        if (User.signin(Start_Textbox[0].getInputText(), Start_Textbox[1].getInputText()) == true) {
                            Current = Menu;
                            Clear_Start_Screen();
                            Background.render(Renderer, 0, 0);
                        }
                        else {
                            Signin_Warning.loadFromRenderedText(Renderer, "Invalid Username or Password!", warning_color, Warning_Font);
                        }
                    }
                    else if (sign_up.isInside(ev.button.x, ev.button.y)) {
                        sign_up.setButtonState(BUTTON_STATE_MOUSE_CLICK);
                        Current = SignUp;
                        Clear_Start_Screen();
                        Signup_Screen();
                    }
                    else if (toggle_password.isInside(ev.button.x, ev.button.y) == true) {
                        cout << "Mouse is in side toggle switch" << endl;
                        if (toggle_password.getCurrentState() == BUTTON_STATE_MOUSE_OUTSIDE) {
                            toggle_password.setButtonState(BUTTON_STATE_MOUSE_OVER_MOTION);
                            Start_Textbox[1].setType(0);
                        }
                        else if (toggle_password.getCurrentState() == BUTTON_STATE_MOUSE_OVER_MOTION) {
                            toggle_password.setButtonState(BUTTON_STATE_MOUSE_OUTSIDE);
                            Start_Textbox[1].setType(1);
                        }
                    }
                }
                else if (ev.type == SDL_MOUSEBUTTONUP) {
                    if (sign_in.isInside(ev.button.x, ev.button.y)) {
                        sign_in.setButtonState(BUTTON_STATE_MOUSE_OUTSIDE);
                    }
                    else if (sign_up.isInside(ev.button.x, ev.button.y)) {
                        sign_up.setButtonState(BUTTON_STATE_MOUSE_OUTSIDE);
                    }
                }
                else if (ev.type == SDL_KEYDOWN) {
                    if (ev.key.keysym.sym == SDLK_BACKSPACE && Start_Textbox[pos].getInputText().length() > 0) {
                        if (Start_Textbox[pos].getState() == true) {
                            Start_Textbox[pos].inputPop();
                        }
                    }
                    else if (ev.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) {
                        SDL_SetClipboardText(Start_Textbox[pos].getInputText().c_str());
                    }
                    else if (ev.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {
                        Start_Textbox[pos].setInputText(SDL_GetClipboardText());
                    }
                }
                else if (ev.type == SDL_TEXTINPUT) {
                    if (!(SDL_GetModState() & KMOD_CTRL && (ev.text.text[0] == 'c' || ev.text.text[0] == 'C' || ev.text.text[0] == 'v' || ev.text.text[0] == 'V'))) {
                        if (Start_Textbox[pos].getState() == true) {
                            Start_Textbox[pos].updateInputText(ev.text.text);
                        }
                    }
                }
                break;
            case SignUp:
                if (ev.type == SDL_MOUSEMOTION) {
                    if (Sign_up.isInside(ev.button.x, ev.button.y)) {
                        Sign_up.setButtonState(BUTTON_STATE_MOUSE_OVER_MOTION);
                    }
                    else {
                        Sign_up.setButtonState(BUTTON_STATE_MOUSE_OUTSIDE);
                    }
                }
                else if (ev.type == SDL_MOUSEBUTTONDOWN) {
                    cout << "mouse pressed" << endl;
                    for (int i = 0; i < SignUp_Textbox.size(); i++) {
                        if (SignUp_Textbox[i].is_mouse_inside(ev.button.x, ev.button.y) == true) {
                            SignUp_Textbox[i].setState(true);
                            pos = i;
                            cout << pos << endl;
                        }
                        else {
                            SignUp_Textbox[i].setState(false);
                        }
                    }
                    for (int i = 0; i < Toggle_Switch.size(); i++) {
                        if (Toggle_Switch[i].isInside(ev.button.x, ev.button.y) == true) {
                            cout << "Mouse is in side toggle switch" << endl;
                            if (Toggle_Switch[i].getCurrentState() == BUTTON_STATE_MOUSE_OUTSIDE) {
                                Toggle_Switch[i].setButtonState(BUTTON_STATE_MOUSE_OVER_MOTION);
                                SignUp_Textbox[i + 1].setType(0);
                            }
                            else {
                                Toggle_Switch[i].setButtonState(BUTTON_STATE_MOUSE_OUTSIDE);
                                SignUp_Textbox[i + 1].setType(1);
                            }
                        }
                    }
                    if (Sign_up.isInside(ev.button.x, ev.button.y)) {
                        Sign_up.setButtonState(BUTTON_STATE_MOUSE_CLICK);
                        code = User.signup(SignUp_Textbox[0].getInputText(), SignUp_Textbox[1].getInputText(), SignUp_Textbox[2].getInputText());
                        if (code == 0) {
                            Current = Menu;
                            Clear_SignUp_Screen();
                            Background.render(Renderer, 0, 0);
                        }
                    }
                }
                else if (ev.type == SDL_MOUSEBUTTONUP) {
                    if (Sign_up.isInside(ev.button.x, ev.button.y)) {
                        Sign_up.setButtonState(BUTTON_STATE_MOUSE_OUTSIDE);
                    }
                }
                else if (ev.type == SDL_KEYDOWN) {
                    if (ev.key.keysym.sym == SDLK_BACKSPACE && SignUp_Textbox[pos].getInputText().length() > 0) {
                        if (SignUp_Textbox[pos].getState() == true) {
                            SignUp_Textbox[pos].inputPop();
                        }
                    }
                    else if (ev.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) {
                        SDL_SetClipboardText(SignUp_Textbox[pos].getInputText().c_str());
                    }
                    else if (ev.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {
                        SignUp_Textbox[pos].setInputText(SDL_GetClipboardText());
                    }
                }
                else if (ev.type == SDL_TEXTINPUT) {
                    if (!(SDL_GetModState() & KMOD_CTRL && (ev.text.text[0] == 'c' || ev.text.text[0] == 'C' || ev.text.text[0] == 'v' || ev.text.text[0] == 'V'))) {
                        if (SignUp_Textbox[pos].getState() == true) {
                            SignUp_Textbox[pos].updateInputText(ev.text.text);
                        }
                    }
                }
                break;
            }
        }
    }
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
        if (!loadMedia()) {
            cout << "Failed to load media" << endl;
        } else {
            bool quit = false;
            Screen Current = Start;
            Start_Screen();
            SDL_Event ev;
            int pos = 0;
            int code = 0;
            while (quit == false) {
                if (Current == Start) {
                    Render_Start_Screen();
                    if (Signin_Warning.getTexture() != NULL) {
                        Signin_Warning.render(Renderer, (Start_Textbox[1].get_input_box_x() + Start_Textbox[1].get_input_box_w() - Signin_Warning.getW()), (Start_Textbox[1].get_input_box_y() + Start_Textbox[1].get_input_box_h()));
                    }
                }
                else if (Current == SignUp) {
                    Render_Signup_Screen();
                    if (code != 0) {
                        Signup_Warning[code - 1].render(Renderer, (SignUp_Textbox[2].get_input_box_x() + SignUp_Textbox[2].get_input_box_w() - Signup_Warning[code - 1].getW()), (SignUp_Textbox[2].get_input_box_y() + SignUp_Textbox[2].get_input_box_h()));
                    }
                }
                handle_event(Current, quit, ev, pos, code);
                if (Current == Start) {
                    for (int i = 0; i < Start_Textbox.size(); i++) {
                        if (Start_Textbox[i].getInputText().length() != 0) {
                            Start_Textbox[i].renderInputText(Renderer, Content_Font, text_color);
                        }
                    }
                }
                else if (Current == SignUp) {
                    for (int i = 0; i < SignUp_Textbox.size(); i++) {
                        if (SignUp_Textbox[i].getInputText().length() != 0) {
                            SignUp_Textbox[i].renderInputText(Renderer, Content_Font, text_color);
                        }
                    }
                }
                SDL_RenderPresent(Renderer);
            }
        }
    }
    close();
    return 0;
}