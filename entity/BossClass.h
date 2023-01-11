#ifndef ENEMY_CLASS_H
#define ENEMY_CLASS_H

#include "../common/common_headers.h"
#include "../utils/GameObject.h"

class BossClass {
    public:
        BossClass();
        BossClass(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D sprite);

        glm::vec2 Move(float dt, unsigned int window_width);
        void Reset(glm::vec2 position, glm::vec2 velocity);

        void Death();
    private:
        float PLAYER_SIZE_X;
        float PLAYER_SIZE_Y;
        float PLAYER_VELOCITY;
        int width, height;

        SpriteRenderer* renderer;
        GameObject* PlayerObj;

        Player_State State; 
        Player_Direction Direction;
};

#endif