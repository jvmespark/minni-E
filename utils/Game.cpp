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
    //Enable transparency 
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

    // load shaders
    ResourceManager::LoadShader("../render/shader_sources/Sprite.vert", "../render/shader_sources/Sprite.frag", nullptr, "sprite");
    // configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    // set render-specific controls
    renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

    Player = new PlayerClass(3.0f, 50.0f, 70.0f, width, height, renderer);

    ResourceManager::LoadTexture("../assets/backgrounds/background.png", false, "background");
    ResourceManager::LoadTexture("../assets/backgrounds/background1.jpg", false, "MenuBackground");
    ResourceManager::LoadTexture("../assets/backgrounds/foreground.png", false, "foreground");
    ResourceManager::LoadTexture("../assets/player/duck.png", false, "block");
    ResourceManager::LoadTexture("../assets/player/Player_Stag1.png", false, "block_solid");

    GameLevel one; one.Load("../levels/one.lvl", width, height);
    this->Levels.push_back(one);

    Level = 0;
    State = GAME_MENU;
    running = true;
    windowFlags = flags;
    windowWidth = width;
    windowHeight = height;
    return true;
}

void Game::render() {
    if (this->State == GAME_MENU) {
        //Menu->render();
        renderer->DrawSprite(ResourceManager::GetTexture("MenuBackground"), glm::vec2(0.0f, 0.0f), glm::vec2(this->windowWidth, this->windowHeight), 0.0f);
    }
    if (this->State == GAME_ACTIVE) {
        renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0.0f, 0.0f), glm::vec2(this->windowWidth, this->windowHeight), 0.0f);
        this->Levels[this->Level].Draw(*renderer);
        Player->render();
        //renderer->DrawSprite(ResourceManager::GetTexture("foreground"), glm::vec2(0.0f, 0.0f), glm::vec2(this->windowWidth, this->windowHeight), 0.0f);
    }
    if (this->State == GAME_WIN) {}
    if (this->State == GAME_DEATH) {}

    SDL_GL_SwapWindow(window);
}

void Game::update() {
    //music
    //boss movement
    //etc
    if (this->State==GAME_MENU) {

    }
    if (this->State==GAME_ACTIVE) {
        this->ResolveCollision();
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
    }

    if (this->State == GAME_MENU) {
        //handle menu inputs
        if (kb[SDL_SCANCODE_P]) {
            State = GAME_ACTIVE;
        }
        //Menu->ProcessInput(kb);
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

Player_Direction VectorDirection(glm::vec2 target)
{
    glm::vec2 compass[] = {
        glm::vec2(0.0f, 1.0f),	// up
        glm::vec2(1.0f, 0.0f),	// right
        glm::vec2(0.0f, -1.0f),	// down
        glm::vec2(-1.0f, 0.0f)	// left
    };
    float max = 0.0f;
    unsigned int best_match = -1;
    for (unsigned int i = 0; i < 4; i++)
    {
        float dot_product = glm::dot(glm::normalize(target), compass[i]);
        if (dot_product > max)
        {
            max = dot_product;
            best_match = i;
        }
    }
    return (Player_Direction)best_match;
}   

//Update later to use Quad Trees
Collision Game::DetectCollision(GameObject &one, GameObject &two) {
    // collision x-axis?
    bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
        two.Position.x + two.Size.x >= one.Position.x;
    // collision y-axis?
    bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
        two.Position.y + two.Size.y >= one.Position.y;
    // collision only if on both axes
    // get center point circle first 
    glm::vec2 one_half_extents(one.Size.x / 2.0f, one.Size.y / 2.0f);
    glm::vec2 one_center(one.Position.x + one_half_extents.x, one.Position.y + one_half_extents.y);
    // calculate AABB info (center, half-extents)
    glm::vec2 two_half_extents(two.Size.x / 2.0f, two.Size.y / 2.0f);
    glm::vec2 two_center(two.Position.x + two_half_extents.x, two.Position.y + two_half_extents.y);
    // get difference vector between both centers
    glm::vec2 difference = one_center - two_center;
    if (collisionX && collisionY)
        return std::make_tuple(true, VectorDirection(difference), difference);
    else
        return std::make_tuple(false, UP, glm::vec2(0.0f, 0.0f));
}

void Game::ResolveCollision() {
    //boundaries
    for (GameObject& boundary : this -> Levels[this->Level].Bricks) {
        Collision collision = DetectCollision(*Player->getGameObject(), boundary);
        if (std::get<0>(collision)) {
            Player_Direction dir = std::get<1>(collision);
            glm::vec2 diff_vector = std::get<2>(collision);
            std::cerr<<dir<<std::endl;
            Player->hitBoundary(dir);
        }
    }
    //boss and enemies

}