#ifndef PLAYER_H
#define PLAYER_H

#include "../common/common_headers.h"
#include "../utils/GameObject.h"
#include "../utils/ResourceManager.h"
#include "../render/SpriteRenderer.h"

enum Player_Direction {
    PLAYER_UP,
    PLAYER_DOWN,
    PLAYER_LEFT,
    PLAYER_RIGHT,
    PLAYER_UP_LEFT,
    PLAYER_UP_RIGHT,
    PLAYER_DOWN_LEFT,
    PLAYER_DOWN_RIGHT,
};

//associated with the current movement in implementation, does not need to read. Action same direction as the character 
//is already facing
enum Player_Action {
    PLAYER_WALK,
    PLAYER_ATTACK, //more nuances versions of attacks later and other moves
    PLAYER_DASH,
};

/* Design the state system 
enum State {
    STATE_STANDING,
    STATE_DASHING,
    STATE_ATTACKING,
};
*/

class PlayerClass {
    public:
        PlayerClass();
        PlayerClass(float velocity, float x, float y, int windowWidth, int widowHeight, SpriteRenderer* renderer_);

        void render();

        void ProcessInput(Player_Direction, Player_Action); //changes the player state
        void ProcessInput(Player_Action); //this one does not need direction specified, it uses the current one.
        //void update();

    private:
        float PLAYER_SIZE_X;
        float PLAYER_SIZE_Y;
        float PLAYER_VELOCITY;

        SpriteRenderer* renderer;
        GameObject* PlayerObj;
};

#endif