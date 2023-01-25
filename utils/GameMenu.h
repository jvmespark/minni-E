#ifndef GAME_MENU_H
#define GAME_MENU_H

#include "../common/common_headers.h"
#include "../render/TextRenderer.h"
#include "../render/SpriteRenderer.h"
#include "ResourceManager.h"
#include "../UI/Button.h"

#include <map>
#include <vector>
#include <string>

enum MenuState {
    MAIN,
    PLAY,
    SETTINGS,
    EXIT,
};

class GameMenu {
    public:
        GameMenu() {}
        GameMenu(SpriteRenderer* renderer_, unsigned int width, unsigned int height);
        
        void init();

        void render();
        void ProcessInput(const Uint8* kb);
        void ProcessInput(SDL_Event event);
        int updateState();
        void changeState(MenuState newState) { State = newState; }
        // settings
        // mouse and keyboard input
    private:
        // text rendering
        unsigned int windowWidth, windowHeight;

        TextRenderer* Menu_Title;
        TextRenderer* Menu_Subtitle;
        SpriteRenderer* renderer;

        MenuState State;

        std::map<std::string, Button*> buttonMap;
};

#endif