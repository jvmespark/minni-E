#include "../../engine/core/Game.h"

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
    ResourceManager::LoadShader("../../engine/render/shader_sources/Sprite.vert", "../../engine/render/shader_sources/Sprite.frag", nullptr, "sprite");
    ResourceManager::LoadShader("../../engine/render/shader_sources/Camera.vert", "../../engine/render/shader_sources/Camera.frag", nullptr, "Camera");
    // configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    // set render-specific controls
    renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

    ResourceManager::LoadTexture("../../demo_game/assets/backgrounds/back.jpg", false, "background");
    ResourceManager::LoadTexture("../../demo_game/assets/backgrounds/foreground.png", false, "foreground");
    ResourceManager::LoadTexture("../../demo_game/assets/blocks/grass.png", false, "stone");
    ResourceManager::LoadTexture("../../demo_game/assets/blocks/grass.png", false, "grass");

    Menu = new GameMenu(renderer, width, height);
    GameLevel one; one.Load("../../demo_game/levels/one.lvl", width, height);
    this->Levels.push_back(one);
    Level = 0;

    // have a level meta data class so these can be abstracted
    EnemyClass* enemy1 = new EnemyClass(3, width/3.0f, height/3.0f, "placeholder", 25.0f, 30.0f, renderer);
    EnemyClass* enemy2 = new EnemyClass(3, width/1.5f, height/1.5f, "placeholder", 25.0f, 35.0f, renderer);
    EnemyClass* enemy3 = new EnemyClass(3, width/1.5f, height/3.0f, "placeholder", 25.0f, 35.0f, renderer);
    enemies = { enemy1, enemy2, enemy3 };

    // change this later to appear in the update function so levels can be iterated
    // have a templated vector for everything to be shifted
    camera = new Camera(width, height, &this->Levels[this->Level]);

    //I hard coded level height, but its going to need to be dynamic later
    Player = new PlayerClass(7.0f, 7.0, 50.0f, 60.0f, width, height, one.getLevelHeight(), one.getLevelWidth(), renderer, camera);

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
        //for (int i = 0; i < this->enemies.size(); i++) {
        //    this->enemies[i]->render();
        //}
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
        //for (int i = 0; i < enemies.size(); i++) {
        //    this->enemies[i]->moveTo(Player->posX(), Player->posY());
        //}
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

    if (kb[SDL_SCANCODE_0]) {
        camera->screenshot();
    }
}

void Game::clean() {
    ResourceManager::Clear();
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::quit() {
    running = false;
}


Direction VectorDirection(glm::vec2 target)
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
    return (Direction)best_match;
}    

/*
    Currently AABB - AABB collision
    Upgrade later to Quad Tree Pre-Partitioning
*/

Collision Game::DetectCollision(GameObject &one, GameObject &two)
{
   // collision x-axis?
    bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
        two.Position.x + two.Size.x >= one.Position.x;
    // collision y-axis?
    bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
        two.Position.y + two.Size.y >= one.Position.y;
    // collision only if on both axex
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
    // only able to stand on a block if position is inside the block landing. cant climb sideways.
    bool side_collided = false;
    bool vert_collided = false;
    Player_Direction collide_dir = PLAYER_NONE;
    for (GameObject &box : this->Levels[this->Level].Bricks)
    {
        Collision collision = DetectCollision(*Player->getGameObject(), box);
        if (std::get<0>(collision))
        {
            Direction dir = std::get<1>(collision);
            if (dir == DOWN) { 
                float ground_level = this->windowHeight - Player->getSizeY() - (this->windowHeight - box.Position.y);
                if (Player->posY() >= ground_level && !Player->isOnGround()) {
                    Player->setPosY(ground_level);
                    Player->setOnGround(true);
                }
                vert_collided = true;
            }
            else {
                // basic collisions. should stop the player from moving in the direction they were going originally.
                if (dir == UP) {
                    // stop jumping. change the state of the player
                    Player->changeState(STATE_NONE);
                }
                if (dir == LEFT) { // left of the box
                    side_collided = true;
                    collide_dir = PLAYER_RIGHT;
                }
                if (dir == RIGHT) { // right of the box
                    side_collided = true;
                    collide_dir = PLAYER_LEFT;
                }
            }
        }
    }
    Player->setCollide(side_collided, collide_dir);
    if (!vert_collided)
        Player->setOnGround(false);
}