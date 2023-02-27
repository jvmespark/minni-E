#include "EnemyClass.h"

EnemyClass::EnemyClass() {}

EnemyClass::EnemyClass(float velocity, float spawnX, float spawnY, const char* enemyAsset, float sizeX, float sizeY, SpriteRenderer* renderer_) {
    load_textures();
    glm::vec2 enemyPos = glm::vec2(spawnX, spawnY);
    EnemyObj = new GameObject(enemyPos, glm::vec2(sizeX,sizeY), ResourceManager::GetTexture("Enemy_Stag"));

    enemy_velocity = velocity;
    enemy_sizeX = sizeX;
    enemy_sizeY = sizeY;

    renderer = renderer_;
}

void EnemyClass::render() {
    EnemyObj->Draw(*renderer);
}

void EnemyClass::moveTo(float x, float y) {
    // find the slope between this position and given position
    // dx and dy movement
    float dx = x - EnemyObj->Position.x;
    float dy = y - EnemyObj->Position.y;
} // A* to this position, research better game AI

void EnemyClass::translate(float x, float y) {
    EnemyObj->Position.x += x;
    EnemyObj->Position.y += y;
}

void EnemyClass::load_textures() {
    ResourceManager::LoadTexture("../../demo_game/assets/player/Player_Stag1.png", true, "Enemy_Stag");
}