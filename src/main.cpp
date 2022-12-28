#include <iostream>
#include <string>

#include "../common/common_headers.h"

#include "../entity/player.h"

#include "../utils/window.h"
#include "../utils/renderer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb_image.h"

int main(int argc, char** argv) {
    Window window("Engine", 1920/2, 1080/2);
    window.init();

    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            quit = window.Handle_Window_Events(e);
        }

        render(window);
    }
}