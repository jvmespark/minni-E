#ifndef PLAYER_H
#define PLAYER_H

#include "../common/common_headers.h"
#include "../utils/GameObject.h"
#include "../utils/ResourceManager.h"
#include "../render/SpriteRenderer.h"
#include "../utils/Camera.h"

#include <vector>

enum Player_State {
    STATE_STANDING,
    STATE_DASHING,
    STATE_ATTACKING,
    STATE_JUMPING,
    STATE_MOVING,
    STATE_NONE,
};

// Make a new state to lock the camera. If camera is locked, then dont translate camera just the player.


class PlayerClass {
    public:
        PlayerClass();
        PlayerClass(float velocityx, float velocityy, float x, float y, int windowWidth, int widowHeight, float levelH, float levelW, SpriteRenderer* renderer_, Camera* camera_);

        void render();

        void ProcessInput(const Uint8* kb);
        //void update();

        float getSizeX() const { return PLAYER_SIZE_X; }
        float getSizeY() const { return PLAYER_SIZE_Y; }
        float posX() const { return PlayerObj->Position.x; }
        float posY() const { return PlayerObj->Position.y; }
        float getVelocityX() const { return PLAYER_VELOCITY_X; }
        float getVelocityY() const { return PLAYER_VELOCITY_Y; }
        GameObject* getGameObject() const { return PlayerObj; }
        void changeState(Player_State newState) { State = newState; }

        void setPosY(float newPosY) { PlayerObj->Position.y = newPosY; }
        void setPosX(float newPosX) { PlayerObj->Position.x = newPosX; }
        void setCollide(bool collide_, int collide_dir_) { collide = collide_; collide_dir = collide_dir_; }

        void setOnGround(bool g) { onGround = g; }
        bool isOnGround() { return onGround; }

    private:
        float PLAYER_SIZE_X;
        float PLAYER_SIZE_Y;
        float PLAYER_VELOCITY_X;
        float INIT_VEL_Y;
        float PLAYER_VELOCITY_Y;
        float PLAYER_GRAVITY;
        int width, height;
        float levelHeight, levelWidth;
        bool onGround;
        bool collide;
        int collide_dir;
        
        Camera* camera;
        SpriteRenderer* renderer;
        GameObject* PlayerObj;

        Player_State State; 

        void load_textures();
};

#endif