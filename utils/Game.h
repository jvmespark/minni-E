#ifndef GAME_H
#define GAME_H

#include "../common/common_headers.h"
#include "../entity/PlayerClass.h"
#include "../render/Shader.h"
#include "../render/SpriteRenderer.h"
#include "ResourceManager.h"
#include "GameLevel.h"

#include <iostream>
#include <string>
#include <vector>
#include <tuple>

typedef std::tuple<bool, Player_Direction, glm::vec2> Collision;

enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_DEATH,
    GAME_WIN,
    GAME_SETTINGS,
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

        Collision DetectCollision(GameObject &one, GameObject &two);
        void ResolveCollision();

        bool isRunning() { return running; }
        SDL_Window* getWindow() const { return window; }

    private:
        SDL_Window* window;
        SpriteRenderer* renderer;
        PlayerClass* Player;
        //GameMenu* Menu;

        bool running;
        int windowFlags;
        unsigned int windowWidth, windowHeight;
        unsigned int gameWidth, gameHeight;

        GameState State;
        std::vector<GameLevel> Levels;
        unsigned int Level;
};

#endif