#include "PlayerClass.h"

PlayerClass::PlayerClass() {
    PLAYER_SIZE_X = PLAYER_SIZE_Y = PLAYER_VELOCITY = 0.0f;
}

PlayerClass::PlayerClass(float velocity, float x, float y, int windowWidth, int windowHeight, SpriteRenderer* renderer_) {
    ResourceManager::LoadTexture("../assets/player/Player_Stag1.png", true, "Player_Stag1");
    ResourceManager::LoadTexture("../assets/player/Duck.png", true, "Player_Up");
    ResourceManager::LoadTexture("../assets/player/awesomeface.png", true, "Player_Down");
    ResourceManager::LoadTexture("../assets/player/Player_Stag1.png", true, "Player_Right");
    ResourceManager::LoadTexture("../assets/player/Player_Stag1.png", true, "Player_Left");
    ResourceManager::LoadTexture("../assets/player/Player_Stag1.png", true, "Player_Up_Left");
    ResourceManager::LoadTexture("../assets/player/Player_Stag1.png", true, "Player_Up_Right");
    ResourceManager::LoadTexture("../assets/player/Player_Stag1.png", true, "Player_Down_Left");
    ResourceManager::LoadTexture("../assets/player/Player_Stag1.png", true, "Player_Down_Right");
    
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