#ifndef GAME_MENU_H
#define GAME_MENU_H

#include "../../common/common_headers.h"
#include "../render/TextRenderer.h"
#include "../render/SpriteRenderer.h"
#include "../core/ResourceManager.h"
#include "Button.h"

#include <map>
#include <vector>
#include <string>
#include <unordered_map>

enum MenuType {
    EXTERNAL,
    INTERNAL,
};

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
        MenuType Type;

        std::unordered_map<std::string, Button*> buttonMap;
        std::unordered_map<std::string, Button*>::iterator button_it;
};

#endif