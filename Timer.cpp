#include "Timer.h"
Timer::Timer() {
	start_point = 0;
	paused_point = 0;
	stop_point = 0;
	pause = false;
	start = false;
	alarm = Mix_LoadMUS("D:/MyProject/sound/alarm.mp3");
}

Timer::Timer(int stop) {
	start_point = 0;
	paused_point = 0;
	stop_point = stop;
	pause = false;
	start = false;
	alarm = Mix_LoadMUS("D:/MyProject/sound/alarm.mp3");
}

void Timer::setStopPoint(int stop) {
	stop_point = stop;
}

void Timer::Start() {
	start = true;
	pause = false;
	start_point = SDL_GetTicks();
	paused_point = 0;
}

void Timer::Stop() {
	start = false;
	pause = false;
	start_point = 0;
	paused_point = 0;
}

void Timer::Pause() {
	if (start == true && pause == false) {
		pause = true;
		paused_point = SDL_GetTicks() - start_point;
		start_point = 0;
	}
}

void Timer::Continue() {
	if (start == true && pause == true) {
		pause = false;
		start_point = SDL_GetTicks() - paused_point;
		paused_point = 0;
	}
}

int Timer::getTotalTime() {
	int time = 0;
	if (start == true) {
		if (pause == true) {
			time = paused_point;
		}
		else {
			time = SDL_GetTicks() - start_point;
		}
	}
	return time;
}

bool Timer::isStarted() {
	if (start == true) {
		return true;
	}
	return false;
}

bool Timer::isPaused() {
	if (start == true && pause == true) {
		return true;
	}
	return false;
}

string Timer::to_time(int n) {
	string res = "";
	if (n / 60 >= 10) {
		res = res + to_string(n / 60) + ":";
	}
	else {
		res = res + '0' + to_string(n / 60) + ":";
	}
	if (n % 60 >= 10) {
		res += to_string(n % 60);
	}
	else {
		res = res + '0' + to_string(n % 60);
	}
	return res;
}

void Timer::renderCountdown(SDL_Renderer* Renderer, SDL_Color color, TTF_Font* font, const int SCREEN_WIDTH) {
	int temp = stop_point - getTotalTime() / 1000;
	string res = to_time(temp);
	Countdown.loadFromRenderedText(Renderer, res, color, font);
	Countdown.render(Renderer, (SCREEN_WIDTH - Countdown.getW())/2, 200);
	if (temp == 0) {
		Mix_PlayMusic(alarm, 0);
		Stop();
	}
}

void Timer::free() {
	Stop();
	Countdown.free();
	alarm = NULL;
}