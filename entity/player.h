#ifndef PLAYER_H
#define PLAYER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum PLAYER_MOVEMENT {
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
enum PLAYER_ACTION {
    PLAYER_ATTACK, //more nuances versions of attacks later and other moves
    PLAYER_ROLL,
    PLAYER_DASH,
};

//rewrite all this for 2d version, currently looks like 3d support

class Player {
    public:
        Player() : Player_Model(glm::mat4(1.0f)), Player_Position(glm::vec3(0.f, 0.f, 0.f)), Player_MovementSpeed(0.f) {}

        void ProcessKeyboard(PLAYER_MOVEMENT direction, float deltaTime); //changes the player state
    private:
        glm::mat4 Player_Model;
        glm::vec3 Player_Position;
        
        float Player_MovementSpeed;
};

#endif