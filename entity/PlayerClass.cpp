#include "PlayerClass.h"

PlayerClass::PlayerClass() {
    PLAYER_SIZE_X = PLAYER_SIZE_Y = PLAYER_VELOCITY_X = PLAYER_VELOCITY_Y = PLAYER_GRAVITY = 0.0f;
    onGround = false;
}

PlayerClass::PlayerClass(float velocityx, float velocityy, float x, float y, int windowWidth, int windowHeight, SpriteRenderer* renderer_) {
    load_textures();
    
    glm::vec2 playerPos = glm::vec2(windowWidth / 2.0f - x / 2.0f, windowHeight - y);
    PlayerObj = new GameObject(playerPos, glm::vec2(x,y), ResourceManager::GetTexture("Player_Stag"));

    PLAYER_VELOCITY_X = velocityx;
    PLAYER_VELOCITY_Y = -velocityy;
    PLAYER_GRAVITY = 0.1;
    PLAYER_SIZE_X = x;
    PLAYER_SIZE_Y = y;
    onGround = true;
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
    if (State == STATE_JUMPING) {
        if (!onGround) {
            PlayerObj->Position.y += PLAYER_VELOCITY_Y += PLAYER_GRAVITY;
        }
        else {
            State = STATE_NONE;
        }
    }
    //Standard Movement
    //else {
        if (kb[SDL_SCANCODE_SPACE]) {
            if (onGround) {
                State = STATE_JUMPING;
                onGround = false;
            }
        }
        if (kb[SDL_SCANCODE_A]) {
            PlayerObj->changeSprite(ResourceManager::GetTexture("Player_Left"));
            PlayerObj->Position.x -= PLAYER_VELOCITY_X;
        }
        if (kb[SDL_SCANCODE_D]) {
            PlayerObj->changeSprite(ResourceManager::GetTexture("Player_Right"));
            PlayerObj->Position.x += PLAYER_VELOCITY_X;
        }
    //}
}

void PlayerClass::run_Animation(Player_Direction dir) {}

void PlayerClass::load_textures() {
    ResourceManager::LoadTexture("../assets/player/PlayerTest.png", true, "Player_Stag");

    ResourceManager::LoadTexture("../assets/player/PlayerTest.png", true, "Player_Right");
    
    ResourceManager::LoadTexture("../assets/player/PlayerTest.png", true, "Player_Left");
}