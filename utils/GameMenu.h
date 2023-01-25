#ifndef GAME_MENU_H
#define GAME_MENU_H

#include "../common/common_headers.h"
#include "../render/TextRenderer.h"
#include "../render/SpriteRenderer.h"
#include "ResourceManager.h"

#include <map>
#include <vector>

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
        
        void render();
        void ProcessInput(const Uint8* kb);
        void ProcessInput(SDL_Event event);
        int updateState();
        // settings
        // mouse and keyboard input
    private:
        // text rendering
        unsigned int windowWidth, windowHeight;

        TextRenderer* Menu_Title;
        TextRenderer* Menu_Subtitle;
        SpriteRenderer* renderer;

        MenuState State;

        std::map<float, std::vector<float>> Main_Layout;
};

#endif