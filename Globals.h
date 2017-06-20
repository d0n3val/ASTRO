#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#ifdef _WIN32
	#include "SDL/include/SDL_rect.h"
#else
	#include "SDL_rect.h"
#endif

float random();
int randomRange(int low, int high);

#define LOG(format, ...) log(__FILE__, __LINE__, format, ##__VA_ARGS__)

void log(const char file[], int line, const char* format, ...);

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

#define MIN( a, b ) ( ((a) < (b)) ? (a) : (b) )
#define MAX( a, b ) ( ((a) > (b)) ? (a) : (b) )

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

// Useful typedefs ---------
typedef unsigned int uint;

// Configuration -----------
#define SCREEN_SIZE 1
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define WIN_TITLE "ASTRO"
#define WIN_FULLSCREEN 0
#define WIN_FULLSCREEN_DESKTOP 0
#define WIN_BORDERLESS 0
#define WIN_RESIZABLE 0
#define REN_VSYNC 1

#endif // __GLOBALS_H__
