#include "Window.h"

Window screen;

Window::Window() {
    window = NULL;
    SCRN_TITLE = "";
    SCRN_WIDTH = 0;
    SCRN_HEIGHT = 0;
    WindowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
}

void Window::init() {
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

    WindowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
    window = SDL_CreateWindow( SCRN_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCRN_WIDTH, SCRN_HEIGHT, WindowFlags );
    if (!window) {
        std::cout<<"ERROR: SDL Window"<<std::endl;
        exit(1);
    }

    SDL_GLContext Context = SDL_GL_CreateContext(window);
    glewExperimental = GL_TRUE; 
	GLenum glewError = glewInit();
}

bool Window::Handle_Window_Events(SDL_Event& e) {
    bool mFullScreen = false;
    if (e.type == SDL_WINDOWEVENT) {
        switch(e.window.event) {

        }
    }
    else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN ) {
        if( mFullScreen ) {
            SDL_SetWindowFullscreen(window, WindowFlags | SDL_WINDOW_FULLSCREEN_DESKTOP);
            mFullScreen = false;
        }
        else {
            SDL_SetWindowFullscreen(window, WindowFlags);
            mFullScreen = true;
        }
    }
    else if (e.type == SDL_QUIT) {
        return true;
    }
    return false;
}
