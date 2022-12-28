#ifndef WINDOW_H
#define WINDOW_H

#include "../common/common_headers.h"

#include <iostream>

class Window {
    public:
        Window();
        Window(const char* SCRN_TITLE_, float SCRN_WIDTH_, float SCRN_HEIGHT_) : SCRN_TITLE(SCRN_TITLE_), SCRN_WIDTH(SCRN_WIDTH_), SCRN_HEIGHT(SCRN_HEIGHT_) {}
        
        void init();
        bool Handle_Window_Events(SDL_Event& e);

        float width() { return SCRN_WIDTH; }
        float height() { return SCRN_HEIGHT; }
        const char* title() { return SCRN_TITLE; }
        SDL_Window* program() { return window; }
    private:
        SDL_Window* window;

        float SCRN_WIDTH;
        float SCRN_HEIGHT;

        const char* SCRN_TITLE;

        Uint32 WindowFlags;
};

#endif