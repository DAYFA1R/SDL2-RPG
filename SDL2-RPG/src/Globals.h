#pragma once

// preprocessor stuff
#include <cstdio>
#include <String>
#include <fstream>
#include <vector>
#include <cmath>
#include <SDL.h>
#include <SDL_image.h>

using namespace std;

//vars
extern const bool DEBUG;
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern float frameTime;
extern int prevTime;
extern int currentTime;
extern float delta;
extern const Uint8* keystate;

//SDL stuff
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;

//Camera related
extern SDL_Rect cameraRect;
extern int levelWidth;
extern int levelHeight;

//funcs

//initialize SDL systems and create window
void init();

//quit and deallocate globals
void done();

//Return Texture from image file
SDL_Texture* makeTexture(string path);

//Ensures consistent frame speed across all platforms
void stabilizeFramerate();

//general box collision check
bool checkCollision(SDL_Rect a, SDL_Rect b);
