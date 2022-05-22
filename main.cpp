#include "Button.cpp"
#include "Textbox.cpp"
#include "Account.cpp"
#include "Scroll.cpp"
#include <vector>

SDL_Window* Window = NULL;
SDL_Renderer* Renderer = NULL;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

const int LEVEL_HEIGHT = 1250;

TTF_Font* Title_Font = NULL;
TTF_Font* Content_Font = NULL;
TTF_Font* Warning_Font = NULL;

SDL_Color text_color = {63,59,55};
SDL_Color warning_color = { 211, 12, 7 };

LTexture Background;

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
    if (Background.loadFromFile(Renderer, "anh/background.png") == false) {
        return false;
    }
    else {
        Title_Font = TTF_OpenFont("font/Roboto-Medium.ttf", 60);
        if (Title_Font == NULL) {
            cout << "Failed to load title font! SDL_ttf Error: " << TTF_GetError() << endl;
            return false;
        }
        Content_Font = TTF_OpenFont("font/Roboto-Medium.ttf", 40);
        if (Content_Font == NULL) {
            cout << "Failed to load content font! SDL_ttf Error: " << TTF_GetError() << endl;
            return false;
        }
        Warning_Font = TTF_OpenFont("font/Roboto-Medium.ttf", 30);
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
    Menu = 2,
    Timer = 3,
    List = 4
};

//Start screen's contents
LTexture Apptitle;
vector<TextBox> Start_Textbox(2);
Button sign_in;
Button sign_up;
Button toggle_password;
LTexture Signin_Warning;

//Start screen's functions
void Start_Screen () {
    Apptitle.loadFromRenderedText(Renderer, "Support Assist", text_color, Title_Font);
    Start_Textbox[1].setType(1);
    sign_in.createButton(Renderer, "anh/signin.png", (SCREEN_WIDTH - 600) / 2, SCREEN_HEIGHT / 1.5);
    sign_up.createButton(Renderer, "anh/signup.png", (SCREEN_WIDTH - 600) / 2 + 400, SCREEN_HEIGHT / 1.5);
    toggle_password.createButton(Renderer, "anh/toggle_password.png", 1040, 360);
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
//

//SignUp screen's contents
vector<TextBox> SignUp_Textbox(3);
vector<Button> Toggle_Switch(2);
Button Sign_up;
Button SignUp_Back;
vector<LTexture> Signup_Warning(3);

//SignUp screen's functions
void Signup_Screen() {
    for (int i = 1; i < 3; i++) {
        SignUp_Textbox[i].setType(1);
    }
    Toggle_Switch[0].createButton(Renderer, "anh/toggle_password.png", 1040, SCREEN_HEIGHT/3);
    Toggle_Switch[1].createButton(Renderer, "anh/toggle_password.png", 1040, (11 * SCREEN_HEIGHT) / 20);
    Sign_up.createButton(Renderer, "anh/signup.png", (SCREEN_WIDTH - 600) / 2 + 400, SCREEN_HEIGHT / 1.5);
    SignUp_Back.createButton(Renderer, "anh/back.png", 0, 0, 50, 50);
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
Button Exit, Focus, Training, Todo, Menu_back;
LTexture Line;
//Menu's functions
void Menu_Screen() {
    Exit.createButton(Renderer, "anh/back.png", 0, 0, 50, 50);
    Focus.createButton(Renderer, "anh/timerbutton.png", SCREEN_WIDTH/1.999, SCREEN_HEIGHT/3.6, 200, 200);
    Training.createButton(Renderer, "anh/diagbutton.png", SCREEN_WIDTH/2.4, SCREEN_HEIGHT/2, 200, 200);
    Todo.createButton(Renderer, "anh/listbutton.png",SCREEN_WIDTH/1.7, SCREEN_HEIGHT/2, 200, 200);
    Line.loadFromFile( Renderer, "anh/line in menu.png" );
    Menu_back.createButton(Renderer, "anh/back.png", 0, 0, 50, 50);
}

void Render_Menu_Screen() {
    Background.render(Renderer, 0, 0);
    Line.render(Renderer, 0,SCREEN_HEIGHT/1.65);
    Exit.render(Renderer);
    Focus.render(Renderer);
    Training.render(Renderer);
    Todo.render(Renderer);
    Menu_back.render(Renderer);
}

void Clear_Menu_Screen() {
    Todo.free();
    Focus.free();
    Training.free();
    Line.free();
    Menu_back.free();
    SDL_RenderClear(Renderer);
}
//Todo's Content
vector<TextBox> task(100);
Scroll dot;
//SDL_Rect camera = {0, 0, 900, SCREEN_HEIGHT};
Button List_Back, ADD, Save;
LTexture danh_sach, noti_check;
vector<Button> check(100);
int count =0;
void Todo_Screen() {
    
    for ( int i = 0; i < 100 ; i++) {
        task[i].setType(0);
    }
    List_Back.createButton(Renderer, "anh/back.png", 0, 0, 50, 50);
    ADD.createButton(Renderer, "anh/add.png", 260, 35, 50, 50);
    Save.createButton(Renderer, "anh/save.png", 1000, 35, 50, 50);
    danh_sach.loadFromFile(Renderer, "anh/danh_sach.png");
    scroll.loadFromFile(Renderer, "anh/dot.bmp");
    for ( int i = 0; i< 100; i++ ) {
        check[i].createButton(Renderer, "anh/check.png", 950, 100 * (i + 1), 10, 10);
    }
}
void Render_Todo_Screen () {
    Background.render( Renderer, 0, 0);
    
        /*camera.x = ( dot.getX() + Scroll::SCROLL_WIDTH / 2 ) - SCREEN_WIDTH / 2;
		camera.y = ( dot.getY() + Scroll::SCROLL_HEIGHT / 2 ) - SCREEN_HEIGHT / 2;

		//Keep the camera in bounds
		if( camera.x < 0 )
		{ 
			camera.x = 0;
		}
		if( camera.y < 0 )
		{
			camera.y = 0;
		}
		if( camera.x > 1280 - camera.w )
		{
			camera.x = 1280 - camera.w;
		}
		if( camera.y > LEVEL_HEIGHT - camera.h )
		{
			camera.y = LEVEL_HEIGHT - camera.h;
		}*/
    //Khung list menu   
    danh_sach.render(Renderer, 200, 0);
    //dot.render(Renderer);
    List_Back.render(Renderer);
    ADD.render(Renderer);
    Save.render(Renderer);
    for ( int i = 0; i< count ; i++) {
        task[i].render(Renderer, "*", 350, 100* ( i + 1), text_color, Content_Font);
        check[i].render(Renderer);
    }
    
}
void Clear_Add_Task() {
    
    List_Back.free();
    ADD.free();
    danh_sach.free();
    Save.free();
    noti_check.free();
    for ( int i = 0; i< task.size(); i++) {
        //task[i].free();
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
                            Menu_Screen();
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
                    if (SignUp_Back.isInside(ev.button.x, ev.button.y)) {
                        SignUp_Back.setButtonState(BUTTON_STATE_MOUSE_OVER_MOTION);
                    }
                    else {
                        SignUp_Back.setButtonState(BUTTON_STATE_MOUSE_OUTSIDE);
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
                            Menu_Screen();
                        }
                    }
                    else if (SignUp_Back.isInside(ev.button.x, ev.button.y)) {
                        SignUp_Back.setButtonState(BUTTON_STATE_MOUSE_CLICK);
                        Current = Start;
                        Clear_SignUp_Screen();
                        Start_Screen();
                    }
                }
                else if (ev.type == SDL_MOUSEBUTTONUP) {
                    if (Sign_up.isInside(ev.button.x, ev.button.y)) {
                        Sign_up.setButtonState(BUTTON_STATE_MOUSE_OUTSIDE);
                    }
                    else if (SignUp_Back.isInside(ev.button.x, ev.button.y)) {
                        SignUp_Back.setButtonState(BUTTON_STATE_MOUSE_OUTSIDE);
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
            case Menu:

                if (ev.type == SDL_MOUSEMOTION) {

                        if (Training.isInside(ev.button.x, ev.button.y)) {
                            Training.setButtonState(BUTTON_STATE_MOUSE_OVER_MOTION);
                        }
                        else {
                            Training.setButtonState(BUTTON_STATE_MOUSE_OUTSIDE);
                        }
                        
                        if (Focus.isInside(ev.button.x, ev.button.y)) {
                            Focus.setButtonState(BUTTON_STATE_MOUSE_OVER_MOTION);
                        }
                        else {
                            Focus.setButtonState(BUTTON_STATE_MOUSE_OUTSIDE);
                        }
                    
                        if (Todo.isInside(ev.button.x, ev.button.y)) {
                            Todo.setButtonState(BUTTON_STATE_MOUSE_OVER_MOTION);
                        }
                        else {
                            Todo.setButtonState(BUTTON_STATE_MOUSE_OUTSIDE);
                        }
                        if (Menu_back.isInside(ev.button.x, ev.button.y)) {
                            Menu_back.setButtonState(BUTTON_STATE_MOUSE_OVER_MOTION);
                        }
                        else {
                            Menu_back.setButtonState(BUTTON_STATE_MOUSE_OUTSIDE);
                        }
                    }
                    else if (ev.type == SDL_MOUSEBUTTONDOWN) {
                        if (Training.isInside(ev.button.x, ev.button.y)) {
                            Training.setButtonState(BUTTON_STATE_MOUSE_CLICK);
                            //Current = Timer;
                            Clear_Menu_Screen();
                            Background.render( Renderer, 0, 0);
                        }
                        //Focus
                        else if (Focus.isInside(ev.button.x, ev.button.y)) {
                            Focus.setButtonState(BUTTON_STATE_MOUSE_CLICK);
                            //Current = Timer;
                            Clear_Menu_Screen();
                            Background.render( Renderer, 0, 0);
                            
                        } 
                        //Todo
                        else if (Todo.isInside(ev.button.x, ev.button.y)) {
                            Todo.setButtonState(BUTTON_STATE_MOUSE_CLICK);
                            Current = List;
                            Clear_Menu_Screen();
                            Todo_Screen();
                        }
                        //Nút back lại
                         else if (Menu_back.isInside(ev.button.x, ev.button.y)) {
                            Menu_back.setButtonState(BUTTON_STATE_MOUSE_CLICK);
                            Current = Start;
                            Clear_Menu_Screen();
                            Start_Screen();
                        }
                    }
                    else if (ev.type == SDL_MOUSEBUTTONUP) {
                        if (Training.isInside(ev.button.x, ev.button.y)) {
                            Training.setButtonState(BUTTON_STATE_MOUSE_OUTSIDE);
                        }
                        else if (Todo.isInside(ev.button.x, ev.button.y)) {
                            Todo.setButtonState(BUTTON_STATE_MOUSE_OUTSIDE);
                        } 
                        else if (Focus.isInside(ev.button.x, ev.button.y)) {
                            Focus.setButtonState(BUTTON_STATE_MOUSE_OUTSIDE);
                        }
                        else if (Menu_back.isInside(ev.button.x, ev.button.y)) {
                            Menu_back.setButtonState(BUTTON_STATE_MOUSE_OUTSIDE);
                        }
                    }
                    break;
            case List:
                    if (ev.type == SDL_MOUSEMOTION) {
                        if (List_Back.isInside(ev.button.x, ev.button.y)) {
                            List_Back.setButtonState(BUTTON_STATE_MOUSE_OVER_MOTION);
                        }
                        else {
                            List_Back.setButtonState(BUTTON_STATE_MOUSE_OUTSIDE);
                        }
                        if (ADD.isInside(ev.button.x, ev.button.y)) {
                            ADD.setButtonState(BUTTON_STATE_MOUSE_OVER_MOTION);
                        }
                        else {
                            ADD.setButtonState(BUTTON_STATE_MOUSE_OUTSIDE);
                        }
                        if (Save.isInside(ev.button.x, ev.button.y)) {
                            Save.setButtonState(BUTTON_STATE_MOUSE_OVER_MOTION);
                        }
                        else {
                            Save.setButtonState(BUTTON_STATE_MOUSE_OUTSIDE);
                        }
                    }
                    else if ( ev.type == SDL_MOUSEBUTTONDOWN) {
                         cout << "mouse pressed" << endl;
        
                        for ( int i = 0; i < task.size(); i++) {
                            if (task[i].is_mouse_inside(ev.button.x, ev.button.y) == true) {
                                task[i].setState(true);
                                task[i].setType(0);
                                pos = i;
                                cout << pos << endl;
                            }
                            else {
                                task[i].setState(false);
                            }
                        }
                        //Nut back
                        if (List_Back.isInside(ev.button.x, ev.button.y)) {
                            List_Back.setButtonState(BUTTON_STATE_MOUSE_CLICK);
                            Current = Menu;
                            Clear_Add_Task();
                            Menu_Screen();
                        }
                        //add task in list
                        else if (ADD.isInside(ev.button.x, ev.button.y)) {
                            ADD.setButtonState(BUTTON_STATE_MOUSE_CLICK);
                            count++;
                        }
                        //Save the list
                        else if (Save.isInside(ev.button.x, ev.button.y)) {
                            Save.setButtonState(BUTTON_STATE_MOUSE_CLICK);
                            for ( int i = 0; i< count; i++) {
                                if (User.list(task[i].getInputText()) == true) {
                                    noti_check.loadFromRenderedText(Renderer, "SAVED", text_color, Content_Font);
                                } else {
                                    noti_check.loadFromRenderedText(Renderer, "UNSAVED", text_color, Content_Font);
                                }
                            }
                        }
                        for ( int i = 0; i < check.size() ; i++) {
                            if (check[i].isInside(ev.button.x, ev.button.y) == true) {
                                cout << "Mouse is in side check switch" << endl;
                            if (check[i].getCurrentState() == BUTTON_STATE_MOUSE_OUTSIDE) {
                                check[i].setButtonState(BUTTON_STATE_MOUSE_OVER_MOTION);
                                
                            }
                            else if (check[i].getCurrentState() == BUTTON_STATE_MOUSE_OVER_MOTION) {
                                check[i].setButtonState(BUTTON_STATE_MOUSE_OUTSIDE);
                                
                            }
                            }
                        }
                    }
                    else if (ev.type == SDL_MOUSEBUTTONUP) {
                        if (List_Back.isInside(ev.button.x, ev.button.y)) {
                            List_Back.setButtonState(BUTTON_STATE_MOUSE_OUTSIDE);
                        }
                        else if (ADD.isInside(ev.button.x, ev.button.y)) {
                            ADD.setButtonState(BUTTON_STATE_MOUSE_OUTSIDE);
                        } 
                        if (Save.isInside(ev.button.x, ev.button.y)) {
                            Save.setButtonState(BUTTON_STATE_MOUSE_OUTSIDE);
                            
                        }
                    } 
                    else if (ev.type == SDL_KEYDOWN) {
                        
                        if (ev.key.keysym.sym == SDLK_BACKSPACE && task[pos].getInputText().length() > 0) {
                            if (task[pos].getState() == true) {
                                task[pos].inputPop();
                            }
                        }
                        else if (ev.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL) {
                            SDL_SetClipboardText(task[pos].getInputText().c_str());
                        }
                        else if (ev.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL) {
                            task[pos].setInputText(SDL_GetClipboardText());
                        }
                        //Scroll
                        //dot.handleScroll_event(ev);
                    }
                    else if (ev.type == SDL_TEXTINPUT) {
                        if (!(SDL_GetModState() & KMOD_CTRL && (ev.text.text[0] == 'c' || ev.text.text[0] == 'C' || ev.text.text[0] == 'v' || ev.text.text[0] == 'V'))) {
                              if ( task[pos].getState() == true) {
                                task[pos].updateInputText(ev.text.text);
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
                else if (Current == Menu) {
                    Render_Menu_Screen();
                }
                else if ( Current = List) {
                    Render_Todo_Screen();
                    noti_check.render(Renderer, 1075, 35);
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
                } else if ( Current == List) {
                     
                    for (int i = 0; i < task.size(); i++) {
                        if (task[i].getInputText().length() != 0) {
                                task[i].renderInputText(Renderer, Content_Font, text_color);
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
/*
- Tạo ra 1 Text box
- Khai báo vector kiểu TextBox như dòng 218
- Render ra textbox như dòng 226
Trong hàm handle_event:
- Trong event SDL_MOUSEBUTTONDOWN:
-- in ra mouse pressed nếu textbox được nhấn vào
-- sau đó xét xem trỏ chuột có đang ở trong textbox hay không với hàm is_mouse_inside
-- sau đó với hàm setState, nếu textbox nào active thì trong main nó sẽ render text vào textbox đấy
-Trong event SDL_KEYDOWN:
-- Nếu là lệnh backspace và nếu getState = true thì xóa với hàm inputPop
- Trong event SDL_TEXTINPUT
-- Nếu thỏa mãn điều kiện như dòng 320 thì cập nhập chuỗi với hàm updateInpuText

*/