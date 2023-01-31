#include "Game.h"

Game::Game() {}

Game::~Game() {
    clean();
    quit();
}

bool Game::init(const char* title, int x, int y, int width, int height, int flags) {
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

    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

    //Enable transparency 
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

    // load shaders
    ResourceManager::LoadShader("../render/shader_sources/Sprite.vert", "../render/shader_sources/Sprite.frag", nullptr, "sprite");
    ResourceManager::LoadShader("../render/shader_sources/Camera.vert", "../render/shader_sources/Camera.frag", nullptr, "Camera");
    // configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    // set render-specific controls
    renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

    ResourceManager::LoadTexture("../assets/backgrounds/background2.jpg", false, "background");
    ResourceManager::LoadTexture("../assets/backgrounds/foreground.png", false, "foreground");
    ResourceManager::LoadTexture("../assets/player/duck.png", false, "block");
    ResourceManager::LoadTexture("../assets/player/Player_Stag1.png", false, "block_solid");

    Menu = new GameMenu(renderer, width, height);

    gameWidth = width*2;
    gameHeight = height;
    GameLevel one; one.Load("../levels/one.lvl", gameWidth, gameHeight);
    this->Levels.push_back(one);
    Level = 0;

    // change this later to appear in the update function so levels can be iterated
    camera = new Camera(&this->Levels[this->Level]);

    //I hard coded level height, but its going to need to be dynamic later
    Player = new PlayerClass(2.0f, 7.0, 50.0f, 70.0f, width, height, one.getLevelHeight(), one.getLevelWidth(), renderer, camera);

    State = GAME_MENU;
    running = true;
    windowFlags = flags;
    windowWidth = width;
    windowHeight = height;
    return true;
}

void Game::render() {
    if (this->State == GAME_MENU) {
        Menu->render();
    }
    if (this->State == GAME_ACTIVE) {
        renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0.0f, 0.0f), glm::vec2(this->windowWidth, this->windowHeight), 0.0f);
        this->Levels[this->Level].Draw(*renderer);
        Player->render();
        //renderer->DrawSprite(ResourceManager::GetTexture("foreground"), glm::vec2(0.0f, 0.0f), glm::vec2(this->windowWidth, this->windowHeight), 0.0f);
    }
    if (this->State == GAME_WIN) {
        // not a menu state, just text overlay
    }
    if (this->State == GAME_DEATH) {
        // not a menu state, fade to black and text.
    }

    SDL_GL_SwapWindow(window);
}

void Game::update() {
    //music
    //boss movement
    //update level and camera
    //etc
    if (this->State==GAME_MENU) {
        State = static_cast<GameState>(Menu->updateState());
    }
    if (this->State==GAME_ACTIVE) {
        this->ResolveCollision();
    }
    if (this->State==GAME_EXIT) {
        quit();
    }
}

void Game::handleEvents() {
    SDL_Event event;
    const Uint8* kb = SDL_GetKeyboardState(NULL);
 
    while(SDL_PollEvent(&event)) {
        bool mFullScreen = false;

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
        if (this->State==GAME_MENU) {
            Menu->ProcessInput(event);
        }
    }

    if (this->State == GAME_MENU) {
        Menu->ProcessInput(kb);
    }
    if (this->State == GAME_ACTIVE) {
        Player->ProcessInput(kb);
    }
    if (this->State == GAME_WIN) {}
    if (this->State == GAME_DEATH) {}
}

void Game::clean() {
    ResourceManager::Clear();
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::quit() {
    running = false;
}

//Update later to use Quad Trees
/*
Collision Game::DetectCollision(GameObject &one, GameObject &two) {

}
*/
void Game::ResolveCollision() {
    float ground_level = this->windowHeight - Player->getSizeY() - this->Levels[this->Level].getLevelHeight();
    if (Player->posY() >= ground_level && !Player->isOnGround()) {
        Player->setPosY(ground_level);
        Player->setOnGround(true);
    }
}