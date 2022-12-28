#include "Game.h"

Game::Game() {}

Game::~Game() {
    clean();
    quit();
}

bool Game::init(const char* title, int x, int y, int width, int height, int flags) {
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        window = SDL_CreateWindow(title, x, y, width, height, flags);

        if (window != 0) {
            SDL_GLContext Context = SDL_GL_CreateContext(window);
            if (Context != 0) {
                glewExperimental = GL_TRUE; 
                GLenum glewError = glewInit();
            }
            else {
                std::cerr<<"GL Context failed"<<std::endl;
                return false;
            }
        }
        else {
            std::cerr<<"Window failed"<<std::endl;
            return false;
        }

    }
    else {
        std::cerr<<"SDL Init failed"<<std::endl;
        return false;
    }

    running = true;
    windowFlags = flags;
    return true;
}

void Game::render() {
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    glViewport(0, 0, windowWidth, windowHeight);
    glClearColor(0.f, 0.f, 1.f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT);


    SDL_GL_SwapWindow(window);
}

void Game::update() {
    
}

void Game::handleEvents() {
    SDL_Event event;
 
    while(SDL_PollEvent(&event)) {
        bool mFullScreen = false;
        //if (event.type == SDL_WINDOWEVENT) {
        //    switch(event.window.event) {
        //        
        //    }
        //}
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN ) {
            if( mFullScreen ) {
                SDL_SetWindowFullscreen(window, windowFlags | SDL_WINDOW_FULLSCREEN_DESKTOP);
                mFullScreen = false;
            }
            else {
                SDL_SetWindowFullscreen(window, windowFlags);
                mFullScreen = true;
            }
        }
        if (event.type == SDL_QUIT) {
            quit();
        }
        //this is bad. fix it by just sending the key into it, and filtering on the other end.
        //switch keys
        //case: key == w
        //  player.processInput(PLAYER_UP, PLAYER_WALK);
        //case: key == space
        //  player.processInput(PLAYER_DASH);
        //case: mouse == left click
        //  player.processInput(PLAYER_ATTACK);
    }
}

void Game::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void Game::quit() {
    running = false;
}

