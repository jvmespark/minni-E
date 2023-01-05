#include "PlayerClass.h"

PlayerClass::PlayerClass() {
    PLAYER_SIZE_X = PLAYER_SIZE_Y = PLAYER_VELOCITY = 0.0f;
}

PlayerClass::PlayerClass(float velocity, float x, float y, int windowWidth, int windowHeight, SpriteRenderer* renderer_) {
    ResourceManager::LoadTexture("../assets/player/duck.png", true, "Player");
    glm::vec2 playerPos = glm::vec2(windowWidth / 2.0f - x / 2.0f, windowHeight - y);
    PlayerObj = new GameObject(playerPos, glm::vec2(x,y), ResourceManager::GetTexture("Player"));
    
    PLAYER_VELOCITY = velocity;
    PLAYER_SIZE_X = x;
    PLAYER_SIZE_Y = y;
    renderer = renderer_;
}

void PlayerClass::render() {
    PlayerObj->Draw(*renderer);
}

void PlayerClass::ProcessInput(Player_Direction, Player_Action) {
    //switch(PLAYER_ACTION) {
    //    case: PLAYER WALK {}
    //}
}
void PlayerClass::ProcessInput(Player_Action) {

}