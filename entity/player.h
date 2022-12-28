#ifndef PLAYER_H
#define PLAYER_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum PLAYER_MOVEMENT {
    PLAYER_FORWARD,
    PLAYER_BACKWARD,
    PLAYER_LEFT,
    PLAYER_RIGHT,
};

class Player {
    public:
        Player() : Player_Model(glm::mat4(1.0f)), Player_Position(glm::vec3(0.f, 0.f, 0.f)), Player_MovementSpeed(0.f) {}

        void ProcessKeyboard(PLAYER_MOVEMENT direction, float deltaTime);
    private:
        glm::mat4 Player_Model;
        glm::vec3 Player_Position;
        
        float Player_MovementSpeed;
};

#endif