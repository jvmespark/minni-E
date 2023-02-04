#include "PlayerClass.h"

PlayerClass::PlayerClass() {
    PLAYER_SIZE_X = PLAYER_SIZE_Y = PLAYER_VELOCITY_X = PLAYER_VELOCITY_Y = PLAYER_GRAVITY = 0.0f;
}

PlayerClass::PlayerClass(float velocityx, float velocityy, float x, float y, int windowWidth, int windowHeight, float levelWidth, float levelHeight, SpriteRenderer* renderer_, Camera* camera_) {
    load_textures();
    
    glm::vec2 playerPos = glm::vec2(windowWidth / 2.0f - x / 2.0f, windowHeight - y - levelHeight);
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
    camera = camera_;
    collide = false;
    collide_dir = PLAYER_NONE;
}

void PlayerClass::render() {
    PlayerObj->Draw(*renderer);
}

int round(float d)
{
    int n = static_cast<int>(d);
    // Smaller multiple
    int a = (n / 10) * 10;
     
    // Larger multiple
    int b = a + 10;
 
    // Return of closest of two
    return (n - a > b - n)? b : a;
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
            PlayerObj->Position.y += PLAYER_VELOCITY_Y;
            PlayerObj->Position.y += PLAYER_GRAVITY;
            PLAYER_GRAVITY *= 1.1;
        }
        else {
            State = STATE_NONE;
            PLAYER_GRAVITY = 0.1;
        }
    }
    //Standard Movement
    //else {
        if (kb[SDL_SCANCODE_SPACE]) {
            if (onGround) {
                State = STATE_JUMPING;
                PlayerObj->Position.y += PLAYER_VELOCITY_Y;
                onGround = false;
            }
        }
        /*
            Come back to camera locking later (or never)
            player is not spawned centered, likely to do with width offset
            going left adds to rightX.
        */
        if (kb[SDL_SCANCODE_A] && !(collide && collide_dir == PLAYER_LEFT)) {
            PlayerObj->changeSprite(ResourceManager::GetTexture("Player_Left"));
            //if (camera->canTranslate(PLAYER_VELOCITY_X, 0) && round(PlayerObj->Position.x) == (camera->midLine())) {
            //    camera->lock();
                camera->translate(PLAYER_VELOCITY_X, 0);
            //}
            //else if (!camera->isLocked()) {
            //    PlayerObj->Position.x -= PLAYER_VELOCITY_X;
            //}
        }
        if (kb[SDL_SCANCODE_D] && !(collide && collide_dir == PLAYER_RIGHT)) {
            PlayerObj->changeSprite(ResourceManager::GetTexture("Player_Right"));
            //std::cout<<"round "<<round(PlayerObj->Position.x)<<" "<<(camera->midLine())<<std::endl;
            //if (camera->canTranslate(-PLAYER_VELOCITY_X, 0) && round(PlayerObj->Position.x) == (camera->midLine())) {
            //    camera->lock();
                camera->translate(-PLAYER_VELOCITY_X, 0);
            //}
            //else if (!camera->isLocked()) {
            //    PlayerObj->Position.x += PLAYER_VELOCITY_X;
            //}
        }
    //}
        if (!onGround)
                PlayerObj->Position.y += 4;
}

void PlayerClass::load_textures() {
    //when drawing assets make sure they stand at the very end of the image, or else they float.
    ResourceManager::LoadTexture("../assets/player/Player_Stag1.png", true, "Player_Stag");

    ResourceManager::LoadTexture("../assets/player/Player_Stag1.png", true, "Player_Right");
    
    ResourceManager::LoadTexture("../assets/player/Player_Stag1.png", true, "Player_Left");
}