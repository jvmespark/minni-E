#include <iostream>
#include <string>

#include "../../common/common_headers.h"
#include "../../engine/core/Game.h"

const int FPS=60;
const float DELAY_TIME=1000.0f / FPS;
Uint32 frameStart, frameTime;

int main(int argc, char** argv) {
    Game game;
    game.init("Engine_Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920/2, 1080/2, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    while (game.isRunning()) {
        frameStart = SDL_GetTicks();

        game.update();
        game.handleEvents();
        game.render();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameTime < DELAY_TIME) {
            SDL_Delay((int)(DELAY_TIME-frameTime));
        }
        else {
            SDL_Delay((int)DELAY_TIME);
        }
    }

    game.clean();
    return 0;
}