#ifndef PLAYER_H
#define PLAYER_H

#include "../common/common_headers.h"
#include "../utils/GameObject.h"
#include "../utils/ResourceManager.h"
#include "../render/SpriteRenderer.h"

#include <vector>

enum Player_State {
    STATE_STANDING,
    STATE_DASHING,
    STATE_ATTACKING,
    STATE_JUMPING,
    STATE_NONE,
};

enum Player_Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    NONE,
};

class PlayerClass {
    public:
        PlayerClass();
        PlayerClass(float velocityx, float velocityy, float x, float y, int windowWidth, int widowHeight, float levelH, float levelW, SpriteRenderer* renderer_);

        void render();

        void ProcessInput(const Uint8* kb);
        //void update();

        float getSizeX() const { return PLAYER_SIZE_X; }
        float getSizeY() const { return PLAYER_SIZE_Y; }
        float posX() const { return PlayerObj->Position.x; }
        float posY() const { return PlayerObj->Position.y; }
        GameObject* getGameObject() const { return PlayerObj; }

        void setOnGround(bool g) { onGround = g; }

        void run_Animation(Player_Direction dir);

    private:
        float PLAYER_SIZE_X;
        float PLAYER_SIZE_Y;
        float PLAYER_VELOCITY_X;
        float PLAYER_VELOCITY_Y;
        float PLAYER_GRAVITY;
        int width, height;
        float levelHeight, levelWidth;
        bool onGround;

        SpriteRenderer* renderer;
        GameObject* PlayerObj;

        Player_State State; 
        Player_Direction Direction;

        void load_textures();
};

#endif