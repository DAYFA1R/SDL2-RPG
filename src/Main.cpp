#include "Globals.h"
#include "Player.h"
#include "Tileset.h"
#include "Map.h"

int main(int argc, char* args[]) {
	init();

	//Stage objects
	Tileset tileset("src/assets/img/tileset.png", 6, 3);
	Map map1("map1");

	// Get level dimensions
	levelWidth = tileset.getTileWidth() * map1.getMapWidth();
	levelHeight = tileset.getTileHeight() * map1.getMapHeight();

	Player player1(gRenderer, "src/assets/img/player1_sheet.png", 5, 5, 3, 4);
	//Wall wall(192, 96, 96, 576);

	// General event handler stuff
	bool quit = false;
	bool paused = false;
	SDL_Event e;

	// Game Loop
	while (!quit) {

		//framerate control
		stabilizeFramerate();

		// Poll Events
		while (SDL_PollEvent(&e) != 0) {
			switch (e.type) {
			// check for quit
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				switch(e.key.keysym.sym) {
				// check for pause
				case SDLK_ESCAPE:
					if (!paused) {
						paused = true;
					} else {
						paused = false;
					}
					break;
				}
				break;
			// checking for window focus
			case SDL_WINDOWEVENT:
				switch(e.window.event) {
				case SDL_WINDOWEVENT_FOCUS_LOST:
					paused = true;
					break;
				}
				break;
			}
		}

		if (!paused) {

			keystate = SDL_GetKeyboardState(NULL);
			player1.update(delta, keystate, map1);


			cameraRect.x = player1.getOriginX() - SCREEN_WIDTH/2;
			cameraRect.y = player1.getOriginY() - SCREEN_HEIGHT/2;

			if (cameraRect.x < 0) {
				cameraRect.x = 0;
			}

			if (cameraRect.y < 0) {
				cameraRect.y = 0;
			}

			if (cameraRect.x + cameraRect.w >= levelWidth) {
				cameraRect.x = levelWidth - SCREEN_WIDTH;
			}

			if (cameraRect.y + cameraRect.h >= levelHeight) {
				cameraRect.y = levelHeight - SCREEN_HEIGHT;
			}

			// Clear stage
			SDL_RenderClear(gRenderer);

			// Make stuff happen!
			map1.drawTiles(tileset);
			map1.drawWalls();
			player1.draw(gRenderer, cameraRect);
			// Update stage
			SDL_RenderPresent(gRenderer);
		}
	}

	done();
	return 0;
}
