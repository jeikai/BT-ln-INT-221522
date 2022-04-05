#include <SDL.h>
#include <iostream>
#include<SDL_image.h>
#include<SDL_ttf.h>
using namespace std;

const int height = 750;
const int width = 1200;

const int butwidth = 300;
const int butheight = 200;
const int total_button = 2;

enum demo {
	mouse_out =0,
	mouse_motion =1,
	mouse_down =2,
	mouse_up=3,
	mouse_total=4
};
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
		void render(int x, int y, SDL_Rect * clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
		
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

class LButton
{
	public:
		//Khởi tạo biến
		LButton();

		void position( int x, int y);

		void event(SDL_Event* e);

		void render();

	private:

	SDL_Point gPosition;
	
	demo gSprite;

};

//The window
SDL_Window * gWindow = NULL;
//Window renderer
SDL_Renderer * gCurrent = NULL;
//Font
TTF_Font* gFont = NULL;
//Background
LTexture s1;
//Font
LTexture s2;

//Mouse button
LTexture s3;
SDL_Rect gClip[mouse_total];
//Button
LButton gButton[ total_button ];

LTexture::LTexture() {
	//Khởi tạo
			gTexture = NULL;
			gwidth = 500;
			gheight =500;
}

LTexture::~LTexture() {
		//Hàm hủy
			free();

}

void LTexture::free() {
			SDL_DestroyTexture( gTexture);
			gTexture = NULL;
			gwidth = 0;
			gheight = 0;

}
void LTexture::loadfile(string path) {
			//Xóa đi texture trc đó
			free();
			
			//The final texture
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
void LTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip) {
			//Set rendering space and render to screen
			SDL_Rect m = {x, y, gwidth, gheight};

			//Set clip rendering dimension
			m.w = clip->w;
			m.h = clip->h;
			SDL_RenderCopyEx( gCurrent, gTexture, clip, &m, angle, center, flip );
}
void LTexture::loadfromtext( string textstring, SDL_Color txtcolor) {
	free();
	SDL_Surface* text  = TTF_RenderText_Solid(gFont, textstring.c_str(), txtcolor);
	gTexture = SDL_CreateTextureFromSurface( gCurrent, text);
	gwidth = text->w;
	gheight = text->h;
	SDL_FreeSurface( text);
}

LButton::LButton() {
	gPosition.x =0;
	gPosition.y =0;
	gSprite = mouse_out;
}
void LButton::position( int x, int y) {
	gPosition.x = x;
	gPosition.y =y;
}
void LButton::event( SDL_Event* e) {
	//Nếu event mouse xảy ra
	if( e->type == SDL_MOUSEMOTION ||e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
		//Mouse position 
		int x, y;
		SDL_GetMouseState( &x, &y);
		
		bool check = true;

		if( x < gPosition.x) {
			check = false;
		} else if( x> gPosition.x + butwidth) {
			check = false;
		} else if ( y< gPosition.y ) {
			check = false;
		} else if(y> gPosition.y + butheight) {
			check = false;
		}

		if( check == false) {
			gSprite = mouse_out;

		} else {
			switch( e->type) {
				case SDL_MOUSEMOTION:
				gSprite = mouse_motion;
				break;

				case SDL_MOUSEBUTTONDOWN:
				gSprite = mouse_down;
				break;
				
				case SDL_MOUSEBUTTONUP:
				gSprite = mouse_up;
				break;
			}
		}
	}
}
void LButton::render() {
	s3.render( gPosition.x, gPosition.y, &gClip[gSprite]);
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

	s3.loadfile("anh/anh2.jpg");
	for(int i=0;i < total_button; i++) {
	gClip[i].x = 0;
	gClip[i].y = 300;
	gClip[i].w = butwidth;
	gClip[i].h = butheight;
	}
	gButton[0].position( 0, 0);
	gButton[1].position( width - butwidth, 0);
	
}


void fillandpaste() {
    //Initialize renderer color
	SDL_SetRenderDrawColor(gCurrent, 146, 33, 9, 1);
	SDL_RenderClear( gCurrent);
	s1.render(0 ,0);
	s2.render(width/1.75, height/3.5);
	//Update screen

	//Render buttons
	for (int i=0; i< total_button; i++) {
				gButton[i].render( );
	}
	SDL_RenderPresent( gCurrent );
	
}

void close() {
	s1.free();
	s2.free();
	s3.free();
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
	loadMedia();
	
	bool check = false;
	while(!check) {
		while(SDL_PollEvent( &e ) !=0) {
			if(e.type == SDL_QUIT) {
				check = true;
			}
			for (int i=0; i< total_button; i++) {
				gButton[i].event( &e );
			}
			
		}
		fillandpaste();
	}
	close();
	return 0;
}



