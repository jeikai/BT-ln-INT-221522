#pragma once
#include <SDL.h>
#include <SDL_mixer.h>
#include "MyTexture.h"

class Timer
{

private: 
	MyTexture Countdown;
	int start_point;
	int paused_point;
	int stop_point;
	bool pause;
	bool start;
	Mix_Music* alarm;

public:
	Timer();
	Timer(int stop);

	void setStopPoint(int stop);

	void Start();
	void Pause();
	void Stop();
	void Continue();

	int getTotalTime();

	bool isStarted();
	bool isPaused();

	string to_time(int n);
	void renderCountdown(SDL_Renderer* Renderer, SDL_Color color, TTF_Font* font, const int SCREEN_WIDTH);

	void free();
};

