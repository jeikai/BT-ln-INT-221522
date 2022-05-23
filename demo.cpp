#include "Button.h"
#include "Textbox.h"
#include "Account.h"
#include "Timer.h"
#include <ctime>

SDL_Window* Window = NULL;
SDL_Renderer* Renderer = NULL;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

TTF_Font* Title_Font = NULL;
TTF_Font* Content_Font = NULL;
TTF_Font* Warning_Font = NULL;
TTF_Font* Description_Font = NULL;
TTF_Font* Time_Font = NULL;

SDL_Color text_color = { 63, 59, 55 };
SDL_Color warning_color = { 211, 12, 7 };

MyTexture Background;
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
        Description_Font = TTF_OpenFont("D:/MyProject/font/Roboto-Medium.ttf", 20);
        if (Description_Font == NULL) {
            cout << "Failed to load description font! SDL_ttf Error: " << TTF_GetError() << endl;
            return false;
        }
        Time_Font = TTF_OpenFont("D:/MyProject/font/Roboto-BoldCondensed.ttf", 150);
        if (Time_Font == NULL) {
            cout << "Failed to load time font! SDL_ttf Error: " << TTF_GetError() << endl;
            return false;
        }
    }
    return true;
}

enum Screen {
    Start = 0,
    SignUp = 1,
    Menu = 2,
    Focus = 3,
    Training = 4,
    Todo = 5
};

//Start screen's contents
MyTexture Apptitle;
vector<Textbox> Start_Textbox(2);
Button sign_in;
Button sign_up;
int SignIn_Pos = 0;
Button toggle_password;
MyTexture Signin_Warning;

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
    Start_Textbox[0].render(Renderer, "Username: ", (SCREEN_WIDTH - Start_Textbox[0].getTag().getW() - 600) / 2, SCREEN_HEIGHT / 3, text_color, Content_Font);
    Start_Textbox[1].render(Renderer, "Password: ", (SCREEN_WIDTH - Start_Textbox[1].getTag().getW() - 600) / 2, SCREEN_HEIGHT / 2, text_color, Content_Font);    
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
//

//SignUp screen's contents
vector<Textbox> SignUp_Textbox(3);
vector<Button> Toggle_Switch(2);
Button Sign_up;
Button SignUp_Back;
vector<MyTexture> Signup_Warning(3);

//SignUp screen's functions
void Signup_Screen() {
    for (int i = 1; i < 3; i++) {
        SignUp_Textbox[i].setType(1);
    }
    Toggle_Switch[0].createButton(Renderer, "D:/MyProject/anh/toggle_password.png", 1040, SCREEN_HEIGHT/3);
    Toggle_Switch[1].createButton(Renderer, "D:/MyProject/anh/toggle_password.png", 1040, (11 * SCREEN_HEIGHT) / 20);
    Sign_up.createButton(Renderer, "D:/MyProject/anh/signup.png", (SCREEN_WIDTH - 600) / 2 + 400, SCREEN_HEIGHT / 1.5);
    SignUp_Back.createButton(Renderer, "D:/MyProject/anh/back.png", 0, 0, 50, 50);
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
    SignUp_Back.render(Renderer);
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
    SignUp_Back.free();
    SDL_RenderClear(Renderer);
}
//

//Menu's contents
Button Exit, focus, training, todo;

//Menu's functions
void Menu_Screen() {
    Exit.createButton(Renderer, "D:/MyProject/anh/back.png", 0, 0, 50, 50);
    focus.createButton(Renderer, "D:/MyProject/anh/timerbutton.png", (SCREEN_WIDTH - 200) / 2, (SCREEN_HEIGHT - 350)/2, 200, 200);
    training.createButton(Renderer, "D:/MyProject/anh/trainingbutton.png", (SCREEN_WIDTH - 400) / 2 - 25, (SCREEN_HEIGHT)/2, 200, 200);
    todo.createButton(Renderer, "D:/MyProject/anh/Todobutton.png", SCREEN_WIDTH / 2 + 25, (SCREEN_HEIGHT)/2, 200, 200);
}

void Render_Menu_Screen() {
    Background.render(Renderer, 0, 0);
    Exit.render(Renderer);
    focus.render(Renderer);
    training.render(Renderer);
    todo.render(Renderer);
}

void Clear_Menu_Screen() {
    Exit.free();
    focus.free();
    training.free();
    todo.free();
    SDL_RenderClear(Renderer);
}
//

//Focus's contents
vector<MyTexture> Description_Text(4);
vector<MyTexture> Time_Options(4);
vector<MyTexture> Time_Options_Description(4);
vector<vector<Timer>> Timer_Options(4);
int current_time_option = 0;
vector<Button> Arrows(2);
Button Start_Stop;
Button Focus_Back;
bool session_in_progress = false;
int Pos = 0;

//Focus's functions
void Focus_Screen() {
    Description_Text[0].loadFromRenderedText(Renderer, "Ready, set, focus!", text_color, Content_Font);
    Description_Text[1].loadFromRenderedText(Renderer, "Achieve your goals and get more done with focus sessions.", text_color, Description_Font);
    for (int i = 0; i < 4; i++) {
        Time_Options[i].loadFromRenderedText(Renderer, to_string((i + 1) * 15), text_color, Time_Font);
        if (i < 2) {
            Timer temp((i + 1) * 15 * 60);
            if (Timer_Options[i].size() == 0) {
                Timer_Options[i].push_back(temp);
            }
            else {
                Timer_Options[i][0] = temp;
            }
        }
        else {
            Timer temp1(((i + 1) * 2 * 60 - (i - 1) * 2 * 60) / 2);
            Timer temp2((i - 1) * 2 * 60);
            Timer temp3(((i + 1) * 2 * 60 - (i - 1) * 2 * 60) / 2);
            if (Timer_Options[i].size() == 0) {
                Timer_Options[i].push_back(temp1);
                Timer_Options[i].push_back(temp2);
                Timer_Options[i].push_back(temp3);
            }
            else {
                Timer_Options[i][0] = temp1;
                Timer_Options[i][1] = temp2;
                Timer_Options[i][2] = temp3;
            }
        }
    }
    for (int i = 0; i < 2; i++) {
        Time_Options_Description[i].loadFromRenderedText(Renderer, "You'll have no breaks.", text_color, Description_Font);
    }
    for (int i = 2; i < 4; i++) {
        Time_Options_Description[i].loadFromRenderedText(Renderer, "You'll have 1 breaks.", text_color, Description_Font);
    }
    Arrows[0].createButton(Renderer, "D:/MyProject/anh/up.png", 800, 250, 76, 75);
    Arrows[1].createButton(Renderer, "D:/MyProject/anh/down.png", 400, 250, 76, 75);
    Start_Stop.createButton(Renderer, "D:/MyProject/anh/Start_Stop.png", (SCREEN_WIDTH - 106)/2, 380, 106, 305 / 3);
    Focus_Back.createButton(Renderer, "D:/MyProject/anh/back.png", 0, 0, 50, 50);
}

void Render_Focus_Screen() {
    Background.render(Renderer, 0, 0);
    if (session_in_progress == false) {
        Description_Text[0].render(Renderer, (SCREEN_WIDTH - Description_Text[0].getW())/2, 100);
        Description_Text[1].render(Renderer, (SCREEN_WIDTH - Description_Text[1].getW())/2, 150);
        Time_Options[current_time_option].render(Renderer, (SCREEN_WIDTH - Time_Options[current_time_option].getW())/2, 200);
        Time_Options_Description[current_time_option].render(Renderer, (SCREEN_WIDTH - Time_Options_Description[current_time_option].getW())/2, 360);
        for (int i = 0; i < 2; i++) {
            Arrows[i].render(Renderer);
        }
    }
    else {
        if (Timer_Options[current_time_option].size() == 1) {
            if (Timer_Options[current_time_option][0].isStarted() == false) {
                session_in_progress = false;
                Start_Stop.setState(BUTTON_STATE_MOUSE_OUTSIDE);
            }
            else {
                Description_Text[2].loadFromRenderedText(Renderer, "Focus 1 of 1", text_color, Content_Font);
                Description_Text[2].render(Renderer, (SCREEN_WIDTH - Description_Text[2].getW())/2, 100);
                Timer_Options[current_time_option][0].renderCountdown(Renderer, text_color, Time_Font, SCREEN_WIDTH);
            }
        }
        else {
            Description_Text[2].loadFromRenderedText(Renderer, "Focus " + to_string(Pos + 1) + " of " + to_string(Timer_Options[current_time_option].size()), text_color, Content_Font);
            Description_Text[2].render(Renderer, (SCREEN_WIDTH - Description_Text[2].getW()) / 2, 100);
            if (Pos < Timer_Options[current_time_option].size() - 1) {
                if (Timer_Options[current_time_option][Pos].isStarted() == true) {
                    Timer_Options[current_time_option][Pos].renderCountdown(Renderer, text_color, Time_Font, SCREEN_WIDTH);
                }
                else {
                    Timer_Options[current_time_option][Pos + 1].Start();
                    Pos++;
                }
            }
            else {
                if (Timer_Options[current_time_option][Pos].isStarted() == true) {
                    Timer_Options[current_time_option][Pos].renderCountdown(Renderer, text_color, Time_Font, SCREEN_WIDTH);
                }
                else {
                    session_in_progress = false;
                    Start_Stop.setState(BUTTON_STATE_MOUSE_OUTSIDE);
                    Pos = 0;
                }
            }
        }
    }
    Start_Stop.render(Renderer);
    Focus_Back.render(Renderer);
}

void Clear_Focus_Screen() {
    Focus_Back.free();
    for (int i = 0; i < 4; i++) {
        Description_Text[i].free();
    }
    for (int i = 0; i < 4; i++) {
        Time_Options[i].free();
        Time_Options_Description[i].free();
        for (int j = 0; j < Timer_Options[i].size(); j++) {
            Timer_Options[i][j].free();
        }
    }
    for (int i = 0; i < 2; i++) {
        Arrows[i].free();
    }
    Start_Stop.setState(BUTTON_STATE_MOUSE_OUTSIDE);
    Start_Stop.free();
    Focus_Back.free();
    current_time_option = 0;
    session_in_progress = false;
    SDL_RenderClear(Renderer);
}
//

//Training's contents
vector<Textbox> Body(2);
int Training_Pos = 0;
vector<MyTexture> Units(2);
MyTexture BMI;
double BMI_level[5] = {0, 18.5, 25, 30, 40};
string Level[4] = { "Underweight", "Normal", "Overweight", "Obese" };
Button Training_Back;
Button Calculate;
vector<Button> Exercises(3);
vector<MyTexture> Recomended_Exercises(3);
vector<bool> Choose_Exercises(3, false);

//Training's functions

void Calculate_BMI() {
    double a = 0;
    for (int i = 0; i < Body[0].getInputText().length(); i++) {
        a = a + (Body[0].getInputText()[i] - '0') * pow(10, Body[0].getInputText().length() - i - 1);
    }
    double b = 0;
    for (int i = 0; i < Body[1].getInputText().length(); i++) {
        b = b + (Body[1].getInputText()[i] - '0') * pow(10, Body[1].getInputText().length() - i - 1);
    }
    cout << a << " " << b << endl;
    double bmi = a / pow(b/100, 2);
    string level = "";
    for (int i = 0; i < 4; i++) {
        if (BMI_level[i] <= bmi && bmi <= BMI_level[i + 1]) {
            level = Level[i];
            break;
        }
    }
    BMI.loadFromRenderedText(Renderer, (to_string(bmi) + " - " + level).c_str(), text_color, Title_Font);
    if (bmi > 22.9) {
        double stable_weight = pow(22.9, 2) * pow(b / 100, 2);
        int hour_jogging = int(((stable_weight - a) * 7700) / (200 * 365))%24;
        Recomended_Exercises[0].loadFromRenderedText(Renderer, to_string(hour_jogging) + "h per day", text_color, Content_Font);
        int hour_running = int(((stable_weight - a) * 7700) / (1000 * 365))%24;
        Recomended_Exercises[1].loadFromRenderedText(Renderer, to_string(hour_running) + "h per day", text_color, Content_Font);
        int hour_cycling = int(((stable_weight - a) * 7700) / (400 * 365))%24;
        Recomended_Exercises[2].loadFromRenderedText(Renderer, to_string(hour_cycling) + "h per day", text_color, Content_Font);
    } 
}

void Training_Screen() {
    Units[0].loadFromRenderedText(Renderer, "kg", text_color, Content_Font);
    Units[1].loadFromRenderedText(Renderer, "cm", text_color, Content_Font);
    Training_Back.createButton(Renderer, "D:/MyProject/anh/back.png", 0, 0, 50, 50);
    Calculate.createButton(Renderer, "D:/MyProject/anh/BMI.png", 270, SCREEN_HEIGHT / 3, 102, 101);
    BMI.loadFromRenderedText(Renderer, "0.0", text_color, Content_Font);
    Exercises[0].createButton(Renderer, "D:/MyProject/anh/Jogging.png", (SCREEN_WIDTH - 800) / 2, 350, 200, 200);
    Exercises[1].createButton(Renderer, "D:/MyProject/anh/Running.png", (SCREEN_WIDTH - 800) / 2 + 300, 350, 200, 200);
    Exercises[2].createButton(Renderer, "D:/MyProject/anh/bicycle.png", (SCREEN_WIDTH - 800) / 2 + 600, 350, 200, 200);
}

void Render_Training_Screen() {
    Background.render(Renderer, 0, 0);
    Body[0].render(Renderer, "Weight: ", (SCREEN_WIDTH - Body[0].getTag().getW() - 600) / 2, SCREEN_HEIGHT / 6, text_color, Content_Font);
    Body[1].render(Renderer, "Height: ", (SCREEN_WIDTH - Body[1].getTag().getW() - 600) / 2, SCREEN_HEIGHT / 4, text_color, Content_Font);
    Units[0].render(Renderer, 1020, SCREEN_HEIGHT / 6);
    Units[1].render(Renderer, 1020, SCREEN_HEIGHT / 4);
    Training_Back.render(Renderer);
    Calculate.render(Renderer);
    BMI.render(Renderer, 380, SCREEN_HEIGHT / 3);
    for (int i = 0; i < 3; i++) {
        Exercises[i].render(Renderer);
        if (Choose_Exercises[i] == true) {
            Recomended_Exercises[i].render(Renderer, Exercises[i].getX(), Exercises[i].getY() + 210);
        }
    }
}

void Clear_Training_Screen() {
    for (int i = 0; i < 2; i++) {
        Body[i].free();
        Units[i].free();
    }
    BMI.free();
    Calculate.free();
    Training_Back.free();
    for (int i = 0; i < 3; i++) {
        Exercises[i].free();
        Recomended_Exercises[i].free();
        Choose_Exercises[i] = false;
    }
}
//

//Todo's Content
vector<Textbox> task(100);
int Count = 0, Todo_Pos = 0;
Button Todo_Back, ADD, Save;
MyTexture noti_check;
vector<Button> check(100);

//Todo's functions

//void readTask(Account User, vector<Textbox> todo_list, int& count) {
//    for (int i = 0; i < All_Account.size(); i++) {
//        if (User.getUserName() == All_Account[i][0]) {
//            if (All_Account[i].size() >= 3) {
//                for (int j = 2; j < All_Account[i].size(); j++) {
//                    cout << All_Account[i][j] << endl;
//                    todo_list[count].setInputText(All_Account[i][j]);
//                    count++;
//                    cout << count << endl;
//                }
//            }
//        }
//    }
//}

void Todo_Screen() {
    for (int i = 0; i < 100; i++) {
        task[i].setType(0);
    }
    Todo_Back.createButton(Renderer, "D:/MyProject/anh/back.png", 0, 0, 50, 50);
    ADD.createButton(Renderer, "D:/MyProject/anh/add.png", 260, 35, 50, 50);
    Save.createButton(Renderer, "D:/MyProject/anh/save.png", 1000, 35, 50, 50);
    for (int i = 0; i < 100; i++) {
        check[i].createButton(Renderer, "D:/MyProject/anh/check.png", 970, 50 * (i + 1), 20, 20);
    }
    //readTask(User, task, Count);
}

void Render_Todo_Screen() {
    Background.render(Renderer, 0, 0);
    Todo_Back.render(Renderer);
    ADD.render(Renderer);
    Save.render(Renderer);
    for (int i = 0; i < Count; i++) {
        task[i].render(Renderer, "*", 350, 50 * (i + 1), text_color, Content_Font);
        check[i].render(Renderer);
    }
}

void Clear_Todo_Screen() {
    Count = 0;
    Todo_Pos = 0;
    Todo_Back.free();
    ADD.free();
    Save.free();
    noti_check.free();
    for (int i = 0; i < task.size(); i++) {
        task[i].free();
        check[i].free();
    }
    SDL_RenderClear(Renderer);
}

 void handle_event(Screen& Current, bool& quit, SDL_Event& ev, int& pos, int& code) {
    while (SDL_PollEvent(&ev) != 0) {
        if (ev.type == SDL_QUIT) {
            quit = true;
            break;
        }
        else {
            switch (Current) {
            case Start:
                switch (ev.type) {  
                case SDL_MOUSEMOTION:
                    if (sign_in.isInside(ev.button.x, ev.button.y)) {
                        sign_in.setState(BUTTON_STATE_MOUSE_OVER_MOTION);
                    }
                    else {
                        sign_in.setState(BUTTON_STATE_MOUSE_OUTSIDE);
                    }
                    if (sign_up.isInside(ev.button.x, ev.button.y)) {
                        sign_up.setState(BUTTON_STATE_MOUSE_OVER_MOTION);
                    }
                    else {
                        sign_up.setState(BUTTON_STATE_MOUSE_OUTSIDE);
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    for (int i = 0; i < Start_Textbox.size(); i++) {
                        if (Start_Textbox[i].isMouseInside(ev.button.x, ev.button.y) == true) {
                            Start_Textbox[i].setState(true);
                            SignIn_Pos = i;
                        }
                        else {
                            Start_Textbox[i].setState(false);
                        }
                    }
                    if (sign_in.isInside(ev.button.x, ev.button.y)) {
                        sign_in.setState(BUTTON_STATE_MOUSE_CLICK);
                        if (User.signIn(Start_Textbox[0].getInputText(), Start_Textbox[1].getInputText()) == true) {
                            Current = Menu;
                            Clear_Start_Screen();
                            Menu_Screen();
                        }
                        else {
                            Signin_Warning.loadFromRenderedText(Renderer, "Invalid Username or Password!", warning_color, Warning_Font);
                        }
                    }
                    else if (sign_up.isInside(ev.button.x, ev.button.y)) {
                        sign_up.setState(BUTTON_STATE_MOUSE_CLICK);
                        Current = SignUp;
                        Clear_Start_Screen();
                        Signup_Screen();
                    }
                    else if (toggle_password.isInside(ev.button.x, ev.button.y) == true) {
                        cout << "Mouse is in side toggle switch" << endl;
                        if (toggle_password.getState() == BUTTON_STATE_MOUSE_OUTSIDE) {
                            toggle_password.setState(BUTTON_STATE_MOUSE_OVER_MOTION);
                            Start_Textbox[1].setType(0);
                        }
                        else if (toggle_password.getState() == BUTTON_STATE_MOUSE_OVER_MOTION) {
                            toggle_password.setState(BUTTON_STATE_MOUSE_OUTSIDE);
                            Start_Textbox[1].setType(1);
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (sign_in.isInside(ev.button.x, ev.button.y)) {
                        sign_in.setState(BUTTON_STATE_MOUSE_OUTSIDE);
                    }
                    else if (sign_up.isInside(ev.button.x, ev.button.y)) {
                        sign_up.setState(BUTTON_STATE_MOUSE_OUTSIDE);
                    }
                    break;
                case SDL_KEYDOWN:
                    if (ev.key.keysym.sym == SDLK_BACKSPACE && Start_Textbox[SignIn_Pos].getInputText().length() > 0) {
                        if (Start_Textbox[SignIn_Pos].getState() == true) {
                            Start_Textbox[SignIn_Pos].popInputText();
                        }
                    }
                    else if (ev.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) {
                        SDL_SetClipboardText(Start_Textbox[SignIn_Pos].getInputText().c_str());
                    }
                    else if (ev.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {
                        Start_Textbox[SignIn_Pos].setInputText(SDL_GetClipboardText());
                    }
                    break;
                case SDL_TEXTINPUT:
                    if (!(SDL_GetModState() & KMOD_CTRL && (ev.text.text[0] == 'c' || ev.text.text[0] == 'C' || ev.text.text[0] == 'v' || ev.text.text[0] == 'V'))) {
                        if (Start_Textbox[SignIn_Pos].getState() == true) {
                            Start_Textbox[SignIn_Pos].updateInputText(ev.text.text);
                        }
                    }
                    break;
                }
                break;
            case SignUp:
                switch (ev.type) {
                case SDL_MOUSEMOTION:
                    if (Sign_up.isInside(ev.button.x, ev.button.y)) {
                        Sign_up.setState(BUTTON_STATE_MOUSE_OVER_MOTION);
                    }
                    else {
                        Sign_up.setState(BUTTON_STATE_MOUSE_OUTSIDE);
                    }
                    if (SignUp_Back.isInside(ev.button.x, ev.button.y)) {
                        SignUp_Back.setState(BUTTON_STATE_MOUSE_OVER_MOTION);
                    }
                    else {
                        SignUp_Back.setState(BUTTON_STATE_MOUSE_OUTSIDE);
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    cout << "mouse pressed" << endl;
                    for (int i = 0; i < SignUp_Textbox.size(); i++) {
                        if (SignUp_Textbox[i].isMouseInside(ev.button.x, ev.button.y) == true) {
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
                            if (Toggle_Switch[i].getState() == BUTTON_STATE_MOUSE_OUTSIDE) {
                                Toggle_Switch[i].setState(BUTTON_STATE_MOUSE_OVER_MOTION);
                                SignUp_Textbox[i + 1].setType(0);
                            }
                            else {
                                Toggle_Switch[i].setState(BUTTON_STATE_MOUSE_OUTSIDE);
                                SignUp_Textbox[i + 1].setType(1);
                            }
                        }
                    }
                    if (Sign_up.isInside(ev.button.x, ev.button.y)) {
                        Sign_up.setState(BUTTON_STATE_MOUSE_CLICK);
                        code = User.signUp(SignUp_Textbox[0].getInputText(), SignUp_Textbox[1].getInputText(), SignUp_Textbox[2].getInputText());
                        if (code == 0) {
                            Current = Menu;
                            Clear_SignUp_Screen();
                            Menu_Screen();
                        }
                    }
                    else if (SignUp_Back.isInside(ev.button.x, ev.button.y)) {
                        SignUp_Back.setState(BUTTON_STATE_MOUSE_CLICK);
                        Current = Start;
                        Clear_SignUp_Screen();
                        Start_Screen();
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (Sign_up.isInside(ev.button.x, ev.button.y)) {
                        Sign_up.setState(BUTTON_STATE_MOUSE_OUTSIDE);
                    }
                    else if (SignUp_Back.isInside(ev.button.x, ev.button.y)) {
                        SignUp_Back.setState(BUTTON_STATE_MOUSE_OUTSIDE);
                    }
                    break;
                case SDL_KEYDOWN:
                    if (ev.key.keysym.sym == SDLK_BACKSPACE && SignUp_Textbox[pos].getInputText().length() > 0) {
                        if (SignUp_Textbox[pos].getState() == true) {
                            SignUp_Textbox[pos].popInputText();
                        }
                    }
                    else if (ev.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) {
                        SDL_SetClipboardText(SignUp_Textbox[pos].getInputText().c_str());
                    }
                    else if (ev.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {
                        SignUp_Textbox[pos].setInputText(SDL_GetClipboardText());
                    }
                    break;
                case SDL_TEXTINPUT:
                    if (!(SDL_GetModState() & KMOD_CTRL && (ev.text.text[0] == 'c' || ev.text.text[0] == 'C' || ev.text.text[0] == 'v' || ev.text.text[0] == 'V'))) {
                        if (SignUp_Textbox[pos].getState() == true) {
                            SignUp_Textbox[pos].updateInputText(ev.text.text);
                        }
                    }
                    break;
                }
                break;
            case Menu:
                switch (ev.type) {
                case SDL_MOUSEMOTION:
                    if (Exit.isInside(ev.button.x, ev.button.y)) {
                        Exit.setState(BUTTON_STATE_MOUSE_OVER_MOTION);
                    }
                    else {
                        Exit.setState(BUTTON_STATE_MOUSE_OUTSIDE);
                    }
                    if (focus.isInside(ev.button.x, ev.button.y)) {
                        focus.setState(BUTTON_STATE_MOUSE_OVER_MOTION);
                    }
                    else {
                        focus.setState(BUTTON_STATE_MOUSE_OUTSIDE);
                    }
                    if (training.isInside(ev.button.x, ev.button.y)) {
                        training.setState(BUTTON_STATE_MOUSE_OVER_MOTION);
                    }
                    else {
                        training.setState(BUTTON_STATE_MOUSE_OUTSIDE);
                    }
                    if (todo.isInside(ev.button.x, ev.button.y)) {
                        todo.setState(BUTTON_STATE_MOUSE_OVER_MOTION);
                    }
                    else {
                        todo.setState(BUTTON_STATE_MOUSE_OUTSIDE);
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (Exit.isInside(ev.button.x, ev.button.y)) {
                        Exit.setState(BUTTON_STATE_MOUSE_CLICK);
                        Current = Start;
                        Clear_Menu_Screen();
                        Start_Screen();
                    }
                    else if (focus.isInside(ev.button.x, ev.button.y)) {
                        focus.setState(BUTTON_STATE_MOUSE_CLICK);
                        Current = Focus;
                        Clear_Menu_Screen();
                        Focus_Screen();
                    }
                    else if (training.isInside(ev.button.x, ev.button.y)) {
                        training.setState(BUTTON_STATE_MOUSE_CLICK);
                        Current = Training;
                        Clear_Menu_Screen();
                        Training_Screen();
                    }
                    else if (todo.isInside(ev.button.x, ev.button.y)) {
                        todo.setState(BUTTON_STATE_MOUSE_CLICK);
                        Current = Todo;
                        Clear_Menu_Screen();
                        Todo_Screen();
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (focus.isInside(ev.button.x, ev.button.y)) {
                        focus.setState(BUTTON_STATE_MOUSE_OUTSIDE);
                    }
                    else if (training.isInside(ev.button.x, ev.button.y)) {
                        training.setState(BUTTON_STATE_MOUSE_OUTSIDE);
                    }
                    else if (todo.isInside(ev.button.x, ev.button.y)) {
                        todo.setState(BUTTON_STATE_MOUSE_OUTSIDE);
                    }
                    break;
                }
                break;
            case Focus:
                switch (ev.type) {
                case SDL_MOUSEMOTION: 
                    if (Focus_Back.isInside(ev.button.x, ev.button.y)) {
                        Focus_Back.setState(BUTTON_STATE_MOUSE_OVER_MOTION);
                    }
                    else {
                        Focus_Back.setState(BUTTON_STATE_MOUSE_OUTSIDE);
                    }
                    for (int i = 0; i < 2; i++) {
                        if (Arrows[i].isInside(ev.button.x, ev.button.y)) {
                            Arrows[i].setState(BUTTON_STATE_MOUSE_OVER_MOTION);
                        }
                        else {
                            Arrows[i].setState(BUTTON_STATE_MOUSE_OUTSIDE);
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (Focus_Back.isInside(ev.button.x, ev.button.y)) {
                        Focus_Back.setState(BUTTON_STATE_MOUSE_CLICK);
                        Current = Menu;
                        Clear_Focus_Screen();
                        Menu_Screen();
                    } 
                    else if (Arrows[0].isInside(ev.button.x, ev.button.y)) {
                        Arrows[0].setState(BUTTON_STATE_MOUSE_CLICK);
                        if (current_time_option < 3) current_time_option++;
                    } 
                    else if (Arrows[1].isInside(ev.button.x, ev.button.y)) {
                        Arrows[1].setState(BUTTON_STATE_MOUSE_CLICK);
                        if (current_time_option > 0) current_time_option--;
                    }
                    else if (Start_Stop.isInside(ev.button.x, ev.button.y)) {
                        if (Start_Stop.getState() == BUTTON_STATE_MOUSE_OUTSIDE) {
                            Start_Stop.setState(BUTTON_STATE_MOUSE_OVER_MOTION);
                            session_in_progress = true;
                            Timer_Options[current_time_option][0].Start();
                        }
                        else {
                            Start_Stop.setState(BUTTON_STATE_MOUSE_OUTSIDE);
                            session_in_progress = false;
                            Timer_Options[current_time_option][Pos].Stop();
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (Focus_Back.isInside(ev.button.x, ev.button.y)) {
                        Focus_Back.setState(BUTTON_STATE_MOUSE_OUTSIDE);
                    } 
                    else if (Arrows[0].isInside(ev.button.x, ev.button.y)) {
                        Arrows[0].setState(BUTTON_STATE_MOUSE_OUTSIDE);
                    }
                    else if (Arrows[1].isInside(ev.button.x, ev.button.y)) {
                        Arrows[1].setState(BUTTON_STATE_MOUSE_OUTSIDE);
                    }
                    break;
                }
                break;
            case Training:
                switch (ev.type) {
                case SDL_MOUSEMOTION:
                    if (Training_Back.isInside(ev.button.x, ev.button.y)) {
                        Training_Back.setState(BUTTON_STATE_MOUSE_OVER_MOTION);
                    }
                    else {
                        Training_Back.setState(BUTTON_STATE_MOUSE_OUTSIDE);
                    }
                    if (Calculate.isInside(ev.button.x, ev.button.y)) {
                        Calculate.setState(BUTTON_STATE_MOUSE_OVER_MOTION);
                    }
                    else {
                        Calculate.setState(BUTTON_STATE_MOUSE_OUTSIDE);
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    for (int i = 0; i < 2; i++) {
                        if (Body[i].isMouseInside(ev.button.x, ev.button.y)) {
                            Body[i].setState(true);
                            Training_Pos = i;
                            cout << "Mouse is inside " << i << endl;
                        }
                        else {
                            Body[i].setState(false);
                            cout << "Mouse is outside " << i << endl;
                        }
                    }
                    for (int i = 0; i < 3; i++) {
                        if (Exercises[i].isInside(ev.button.x, ev.button.y)) {
                            if (Choose_Exercises[i] == false) {
                                Choose_Exercises[i] = true;
                            }
                            else {
                                Choose_Exercises[i] = false;
                            }
                        }
                    }
                    if (Training_Back.isInside(ev.button.x, ev.button.y)) {
                        Training_Back.setState(BUTTON_STATE_MOUSE_CLICK);
                        Current = Menu;
                        Clear_Training_Screen();
                        Menu_Screen();
                    }
                    else if (Calculate.isInside(ev.button.x, ev.button.y)) {
                        Calculate_BMI();
                    }
                    break;
                case SDL_KEYDOWN:
                    if (ev.key.keysym.sym == SDLK_BACKSPACE && Body[Training_Pos].getInputText().length() > 0) {
                        if (Body[Training_Pos].getState() == true) {
                            Body[Training_Pos].popInputText();
                        }
                    }
                    else if (ev.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) {
                        SDL_SetClipboardText(Body[Training_Pos].getInputText().c_str());
                    }
                    else if (ev.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {
                        Body[Training_Pos].setInputText(SDL_GetClipboardText());
                    }
                    break;
                case SDL_TEXTINPUT:
                    if (!(SDL_GetModState() & KMOD_CTRL && (ev.text.text[0] == 'c' || ev.text.text[0] == 'C' || ev.text.text[0] == 'v' || ev.text.text[0] == 'V'))) {
                        if (Body[Training_Pos].getState() == true) {
                            Body[Training_Pos].updateInputText(ev.text.text);
                        }
                    }
                    break;
                }
                break;
            case Todo:
                switch (ev.type) {
                case SDL_MOUSEMOTION:
                    if (Todo_Back.isInside(ev.button.x, ev.button.y)) {
                        Todo_Back.setState(BUTTON_STATE_MOUSE_OVER_MOTION);
                    }
                    else {
                        Todo_Back.setState(BUTTON_STATE_MOUSE_OUTSIDE);
                    }
                    if (ADD.isInside(ev.button.x, ev.button.y)) {
                        ADD.setState(BUTTON_STATE_MOUSE_OVER_MOTION);
                    }
                    else {
                        ADD.setState(BUTTON_STATE_MOUSE_OUTSIDE);
                    }
                    if (Save.isInside(ev.button.x, ev.button.y)) {
                        Save.setState(BUTTON_STATE_MOUSE_OVER_MOTION);
                    }
                    else {
                        Save.setState(BUTTON_STATE_MOUSE_OUTSIDE);
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    cout << "mouse pressed" << endl;
                    for (int i = 0; i < Count; i++) {
                        if (task[i].isMouseInside(ev.button.x, ev.button.y) == true) {
                            task[i].setState(true);
                            Todo_Pos = i;
                            cout << Todo_Pos << endl;
                        }
                        else {
                            task[i].setState(false);
                        }
                    }
                    //Nut back
                    if (Todo_Back.isInside(ev.button.x, ev.button.y)) {
                        Todo_Back.setState(BUTTON_STATE_MOUSE_CLICK);
                        Current = Menu;
                        Clear_Todo_Screen();
                        Menu_Screen();
                    }
                    //add task in list
                    else if (ADD.isInside(ev.button.x, ev.button.y)) {
                        ADD.setState(BUTTON_STATE_MOUSE_CLICK);
                        Count++;
                    }
                    //Save the list
                    else if (Save.isInside(ev.button.x, ev.button.y)) {
                        Save.setState(BUTTON_STATE_MOUSE_CLICK);
                        if (User.Save_Todo_List(User, task, Count) == true) {
                            noti_check.loadFromRenderedText(Renderer, "SAVED", text_color, Content_Font);
                        }
                    }
                    for (int i = 0; i < check.size(); i++) {
                        if (check[i].isInside(ev.button.x, ev.button.y) == true) {
                            cout << "Mouse is in side check switch" << endl;
                            if (check[i].getState() == BUTTON_STATE_MOUSE_OUTSIDE) {
                                check[i].setState(BUTTON_STATE_MOUSE_OVER_MOTION);

                            }
                            else if (check[i].getState() == BUTTON_STATE_MOUSE_OVER_MOTION) {
                                check[i].setState(BUTTON_STATE_MOUSE_OUTSIDE);

                            }
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (Todo_Back.isInside(ev.button.x, ev.button.y)) {
                        Todo_Back.setState(BUTTON_STATE_MOUSE_OUTSIDE);
                    }
                    else if (ADD.isInside(ev.button.x, ev.button.y)) {
                        ADD.setState(BUTTON_STATE_MOUSE_OUTSIDE);
                    }
                    if (Save.isInside(ev.button.x, ev.button.y)) {
                        Save.setState(BUTTON_STATE_MOUSE_OUTSIDE);
                    }
                    break;
                case SDL_KEYDOWN:
                    noti_check.loadFromRenderedText(Renderer, "UNSAVED", text_color, Content_Font);
                    if (ev.key.keysym.sym == SDLK_BACKSPACE && task[Todo_Pos].getInputText().length() > 0) {
                        if (task[Todo_Pos].getState() == true) {
                            task[Todo_Pos].popInputText();
                        }
                    }
                    else if (ev.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) {
                        SDL_SetClipboardText(task[Todo_Pos].getInputText().c_str());
                    }
                    else if (ev.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {
                        task[Todo_Pos].setInputText(SDL_GetClipboardText());
                    }
                    break;
                case SDL_TEXTINPUT:
                    if (!(SDL_GetModState() & KMOD_CTRL && (ev.text.text[0] == 'c' || ev.text.text[0] == 'C' || ev.text.text[0] == 'v' || ev.text.text[0] == 'V'))) {
                        if (task[Todo_Pos].getState() == true) {
                            noti_check.loadFromRenderedText(Renderer, "UNSAVED", text_color, Content_Font);
                            task[Todo_Pos].updateInputText(ev.text.text);
                        }
                    }
                    break;
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
                        Signin_Warning.render(Renderer, (Start_Textbox[1].getInputBoxX() + Start_Textbox[1].getInputBoxW() - Signin_Warning.getW()), (Start_Textbox[1].getInputBoxY() + Start_Textbox[1].getInputBoxH()));
                    }
                    for (int i = 0; i < Start_Textbox.size(); i++) {
                        if (Start_Textbox[i].getInputText().length() != 0) {
                            Start_Textbox[i].renderInputText(Renderer, Content_Font, text_color);
                        }
                    }
                }
                else if (Current == SignUp) {
                    Render_Signup_Screen();
                    if (code != 0) {
                        Signup_Warning[code - 1].render(Renderer, (SignUp_Textbox[2].getInputBoxX() + SignUp_Textbox[2].getInputBoxW() - Signup_Warning[code - 1].getW()), (SignUp_Textbox[2].getInputBoxY() + SignUp_Textbox[2].getInputBoxH()));
                    }
                    for (int i = 0; i < SignUp_Textbox.size(); i++) {
                        if (SignUp_Textbox[i].getInputText().length() != 0) {
                            SignUp_Textbox[i].renderInputText(Renderer, Content_Font, text_color);
                        }
                    }
                }
                else if (Current == Menu) {
                    Render_Menu_Screen();
                }
                else if (Current == Focus) {
                    Render_Focus_Screen();
                }
                else if (Current == Training) {
                    Render_Training_Screen();
                    for (int i = 0; i < 2; i++) {
                        if (Body[i].getInputText().length() != 0) {
                            Body[i].renderInputText(Renderer, Content_Font, text_color);
                        }
                    }
                }
                else if (Current == Todo) {
                    Render_Todo_Screen();
                    noti_check.render(Renderer, 1075, 35);
                    for (int i = 0; i < task.size(); i++) {
                        if (task[i].getInputText().length() != 0) {
                            task[i].renderInputText(Renderer, Content_Font, text_color);
                        }
                    }
                }
                handle_event(Current, quit, ev, pos, code);
                SDL_RenderPresent(Renderer);
            }
        }
    }
    close();
    return 0;
}