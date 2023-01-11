#include "PlayerClass.h"

PlayerClass::PlayerClass() {
    PLAYER_SIZE_X = PLAYER_SIZE_Y = PLAYER_VELOCITY = 0.0f;
}

PlayerClass::PlayerClass(float velocity, float x, float y, int windowWidth, int windowHeight, SpriteRenderer* renderer_) {
    load_textures();
    
    glm::vec2 playerPos = glm::vec2(windowWidth / 2.0f - x / 2.0f, windowHeight - y);
    PlayerObj = new GameObject(playerPos, glm::vec2(x,y), ResourceManager::GetTexture("Player_Stag1"));

    PLAYER_VELOCITY = velocity;
    PLAYER_SIZE_X = x;
    PLAYER_SIZE_Y = y;
    renderer = renderer_;
    width = windowWidth;
    height = windowHeight;
}

void PlayerClass::render() {
    PlayerObj->Draw(*renderer);
}

void PlayerClass::ProcessInput(const Uint8* kb) {
    if (State == STATE_ATTACKING) {
        //Direction Attack
    }
    if (State == STATE_DASHING) {
        //Direction Dash
        //Dash Attack
    }
    //Standard Movement
    else {
        if (kb[SDL_SCANCODE_W] && kb[SDL_SCANCODE_A]) {
            PlayerObj->changeSprite(ResourceManager::GetTexture("Player_Up_Left"));
            PlayerObj->Position.y -= PLAYER_VELOCITY;
            PlayerObj->Position.x -= PLAYER_VELOCITY;
        }
        else if (kb[SDL_SCANCODE_W] && kb[SDL_SCANCODE_D]) {
            PlayerObj->changeSprite(ResourceManager::GetTexture("Player_Up_Right"));
            PlayerObj->Position.y -= PLAYER_VELOCITY;
            PlayerObj->Position.x += PLAYER_VELOCITY;
        }
        else if (kb[SDL_SCANCODE_S] && kb[SDL_SCANCODE_A]) {
            PlayerObj->changeSprite(ResourceManager::GetTexture("Player_Down_Left"));
            PlayerObj->Position.y += PLAYER_VELOCITY;
            PlayerObj->Position.x -= PLAYER_VELOCITY;
        }
        else if (kb[SDL_SCANCODE_S] && kb[SDL_SCANCODE_D]) {
            PlayerObj->changeSprite(ResourceManager::GetTexture("Player_Down_Right"));
            PlayerObj->Position.y += PLAYER_VELOCITY;
            PlayerObj->Position.x += PLAYER_VELOCITY;
        }
        else if (kb[SDL_SCANCODE_W]) {
            PlayerObj->changeSprite(ResourceManager::GetTexture("Player_Up"));
            PlayerObj->Position.y -= PLAYER_VELOCITY;
        }
        else if (kb[SDL_SCANCODE_S]) {
            PlayerObj->changeSprite(ResourceManager::GetTexture("Player_Down"));
            PlayerObj->Position.y += PLAYER_VELOCITY;
        }
        else if (kb[SDL_SCANCODE_A]) {
            PlayerObj->changeSprite(ResourceManager::GetTexture("Player_Left"));
            PlayerObj->Position.x -= PLAYER_VELOCITY;
        }
        else if (kb[SDL_SCANCODE_D]) {
            PlayerObj->changeSprite(ResourceManager::GetTexture("Player_Right"));
            PlayerObj->Position.x += PLAYER_VELOCITY;
        }
    }
}

void PlayerClass::run_Animation(Player_Direction dir) {
    switch(dir) {
        case LEFT: {
            std::vector<Texture2D> run_cycle = {
                ResourceManager::GetTexture("Player_Left1"),
                ResourceManager::GetTexture("Player_Left2"),
            };
            int i = 0;
            while (i <= run_cycle.size()) {
                if (i == run_cycle.size()) i = 0;
                PlayerObj->changeSprite(run_cycle[i]);
                //time pause 1 second
                i++;
            }
        }
    }
}

void PlayerClass::load_textures() {
    ResourceManager::LoadTexture("../assets/player/PlayerTest.png", true, "Player_Stag1");

    ResourceManager::LoadTexture("../assets/player/PlayerTest.png", true, "Player_Up");
    
    ResourceManager::LoadTexture("../assets/player/PlayerTest.png", true, "Player_Down");
    
    ResourceManager::LoadTexture("../assets/player/PlayerTest.png", true, "Player_Right");
    
    ResourceManager::LoadTexture("../assets/player/PlayerTest.png", true, "Player_Left1");
    ResourceManager::LoadTexture("../assets/player/PlayerTest.png", true, "Player_Left2");
    
    ResourceManager::LoadTexture("../assets/player/PlayerTest.png", true, "Player_Up_Left");
    ResourceManager::LoadTexture("../assets/player/PlayerTest.png", true, "Player_Up_Right");
    
    ResourceManager::LoadTexture("../assets/player/PlayerTest.png", true, "Player_Down_Left");
    ResourceManager::LoadTexture("../assets/player/PlayerTest.png", true, "Player_Down_Right");
}