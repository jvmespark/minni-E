#ifndef PLAYER_H
#define PLAYER_H

#include "../common/common_headers.h"
#include "../utils/GameObject.h"
#include "../utils/ResourceManager.h"
#include "../render/SpriteRenderer.h"

enum Player_State {
    STATE_STANDING,
    STATE_DASHING,
    STATE_ATTACKING,
};

class PlayerClass {
    public:
        PlayerClass();
        PlayerClass(float velocity, float x, float y, int windowWidth, int widowHeight, SpriteRenderer* renderer_);

        void render();

        void ProcessInput(const Uint8* kb);
        //void update();

    private:
        float PLAYER_SIZE_X;
        float PLAYER_SIZE_Y;
        float PLAYER_VELOCITY;
        int width, height;

        SpriteRenderer* renderer;
        GameObject* PlayerObj;

        Player_State State; 
};

#endif