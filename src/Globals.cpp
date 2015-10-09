#include "Globals.h"

/* @group vars */

//general
const bool DEBUG = false;
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 900;
const Uint8* keystate;

// Frame control
float frameTime = 0;
int prevTime = 0;
int currentTime = 0;
float delta = 0;

//SDL stuff
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

//Camera related
SDL_Rect cameraRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
int levelWidth = 0;
int levelHeight = 0;


/* @end group */

/* #################################################################### */

/* @group funcs */

//initialize SDL systems and create window
void init() {
	// Base SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL init failed. SDL Error: %s\n", SDL_GetError());
	}

	// PNG handler
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		printf("SDL_image init failed. SDL_image Error: %s\n", IMG_GetError());
	}

	// Create Window
	gWindow = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	// Create Renderer
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

//quit and deallocate globals
void done() {
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	IMG_Quit();
	SDL_Quit();
}

//Return Texture from image file
SDL_Texture* makeTexture(string path) {
	//Holder for final texture
	SDL_Texture* finalTexture = NULL;

	//Holder surface for image
	SDL_Surface* tempSurface = IMG_Load(path.c_str());

	//Set texture to image in surface
	finalTexture = SDL_CreateTextureFromSurface(gRenderer, tempSurface);

	//Deallocate surface
	SDL_FreeSurface(tempSurface);

	//Return created textur
	return finalTexture;
}

void stabilizeFramerate() {
	prevTime = currentTime;
	currentTime = SDL_GetTicks();
	delta = (currentTime - prevTime) / 1000.0f;
}

bool checkCollision(SDL_Rect a, SDL_Rect b) {
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB) {
		return false;
	}
	if (topA >= bottomB) {
		return false;
	}
	if (rightA <= leftB) {
		return false;
	}
	if (leftA >= rightB) {
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}
/* @end group */
