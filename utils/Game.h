#ifndef GAME_H
#define GAME_H

#include "../common/common_headers.h"
#include "../entity/PlayerClass.h"
#include "../render/Shader.h"
#include "../render/SpriteRenderer.h"

#include "ResourceManager.h"

#include <iostream>
#include <string>

enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_DEATH,
    GAME_WIN
};

class Game {
    public:
        Game();
        ~Game();
        bool init(const char* title, int x, int y, int width, int height, int flags);
 
        void update();
        void handleEvents();
        void render();
        void clean();
        void quit();

        bool isRunning() { return running; }
        SDL_Window* getWindow() const { return window; }

    private:
        SDL_Window* window;
        SpriteRenderer* renderer;
        PlayerClass* Player;
    
        bool running;
        int windowFlags;
        unsigned int windowWidth, windowHeight;

        GameState State;
};

#endif