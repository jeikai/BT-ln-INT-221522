#include <SDL.h>
#include <iostream>
#include<SDL_image.h>
#include<SDL_ttf.h>
using namespace std;

const int height = 750;
const int width = 1200;
const int butwidth = 300;
const int butheight = 200,


SDL_Window * gWindow = NULL;
SDL_Renderer * gCurrent = NULL;
//TTF_Font* gFont = NULL;
/*enum demo {
	mouse_out =0,
	mouse_motion =1,
	mouse_down =2,
	mouse_up=3,
	mouse_total=4
}; */

class LTexture
{
	public:
		//Khởi tạo biến
		LTexture();
		
		//Hủy vùng nhớ
        ~LTexture();
		

		//Load ảnh
		void loadfile(string path);
		
		//Tạo ảnh từ font string
		void loadfromtext(string text, SDL_Color txtcolor);
        
		//Renders texture at given point
		void render(int x, int y);
		
		void free();
		
		int getw() {
			return gwidth;
		}
		int geth() {
			return gheight;
		}
	private:
		SDL_Texture* gTexture;

		int gwidth;
		int gheight;

};
LTexture s1;
LTexture s2;
/*
class LButton
{
	public:
		//Khởi tạo biến
		LButton();


		void position( int x, int y);

}; */
LTexture::LTexture() {
			gTexture = NULL;
			gwidth = 500;
			gheight =500;
}

LTexture::~LTexture() {
			free();

}

void LTexture::free() {
			SDL_DestroyTexture( gTexture);
			gTexture = NULL;
			gwidth = 0;
			gheight = 0;

}
void LTexture::loadfile(string path) {
			//The final texture
			free();
			SDL_Texture* newTexture = NULL;
	
			//Load image at specific path
			SDL_Surface* loadSurface = IMG_Load(path.c_str());
			
			// set color image 
			SDL_SetColorKey( loadSurface, SDL_TRUE, SDL_MapRGB( loadSurface->format, 0, 0xFF, 0xFF ) );
			
			//Tạo texture từ surface có sẵn
			newTexture = SDL_CreateTextureFromSurface( gCurrent, loadSurface );
			
			//Get image dimesion:
			gwidth = loadSurface->w;
			gheight = loadSurface->h;
			//Giải phóng surface đã load và ko dùng đến nữa
			SDL_FreeSurface(loadSurface);
			
			gTexture = newTexture;
}
void LTexture::render(int x, int y) {
			SDL_Rect m = {x, y, gwidth, gheight};
			SDL_RenderCopy(gCurrent, gTexture, NULL, &m);
}
void LTexture::loadfromtext( string textstring, SDL_Color txtcolor) {
	free();

	SDL_Surface* text  = TTF_RenderText_Solid(gFont, textstring.c_str(), txtcolor);
	gTexture = SDL_CreateTextureFromSurface( gCurrent, text);
	gwidth = text->w;
	gheight = text->h;
	SDL_FreeSurface( text);
}


void init() {
	
	if(SDL_Init(SDL_INIT_EVERYTHING) !=0) {
		cout<<"Error";
		
	} else {
		SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );
		//Tạo khung cửa sổ
		gWindow = SDL_CreateWindow("Project", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
		//Tạo renderer cho window
		gCurrent = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		
		//Init PNG loading
		int imgFlags = IMG_INIT_JPG;
		IMG_Init( imgFlags );
		TTF_Init();
	}
	
}
void loadMedia() {
	//gTexture = loadTexture("anh/anh4.jpg");
	s1.loadfile("anh/background.jpg");
	//Mở file font
	gFont = TTF_OpenFont("font/iknowaghost.ttf", 80);
	//Render text
	SDL_Color text = { 22, 115, 161};
	s2.loadfromtext("HEALTH CARE", text);
}


void fillandpaste() {
    //Initialize renderer color
	SDL_SetRenderDrawColor(gCurrent, 146, 33, 9, 1);
	SDL_RenderClear( gCurrent);
	s1.render(0 ,0);
	s2.render(width/1.75, height/3.5);
	//Update screen
	SDL_RenderPresent( gCurrent );
	
}

void close() {
	s1.free();
	s2.free();
	SDL_DestroyWindow( gWindow);
	gWindow = NULL;
	SDL_DestroyRenderer( gCurrent);
	gCurrent = NULL;
	/*SDL_DestroyTexture( gTexture);
	gTexture = NULL;*/
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}
int main(int argc, char* args[]) {
	SDL_Event e;
	init();
	//fill();
	loadMedia();
	//fill();
	
	bool check = false;
	while(!check) {
		while(SDL_PollEvent( &e ) !=0) {
			if(e.type == SDL_QUIT) {
				check = true;
			}
		}
		fillandpaste();
	}
	close();
	return 0;
}



//ham ve hinh vuong
/*void square() {
	SDL_Rect fillRect = { width / 4, height / 4, width / 2, height / 2 };
		SDL_SetRenderDrawColor( gCurrent, 0xFF, 0x00, 0x00, 0xFF );		
		SDL_RenderFillRect( gCurrent, &fillRect );
		SDL_Rect outlineRect = { width / 6, height / 6, width* 2 / 3, height * 2 / 3 };
		SDL_SetRenderDrawColor( gCurrent, 0x00, 0xFF, 0x00, 0xFF );		
		SDL_RenderDrawRect( gCurrent, &outlineRect );
		SDL_SetRenderDrawColor( gCurrent, 0x00, 0x00, 0xFF, 0xFF );		
		SDL_RenderDrawLine( gCurrent, 0, height / 2, width, height / 2 );

				//Draw vertical line of yellow dots
				SDL_SetRenderDrawColor( gCurrent, 0xFF, 0xFF, 0x00, 0xFF );
				for( int i = 0; i < height; i += 4 )
				{
					SDL_RenderDrawPoint( gCurrent, width / 2, i );
				}
				//Update screen
				SDL_RenderPresent( gCurrent);
}
void fill() {
	SDL_FillRect(gSurface, NULL, SDL_MapRGB(gSurface->format, 236, 188, 208));
} 
void update() {
	SDL_UpdateWindowSurface( gWindow);
}*/
