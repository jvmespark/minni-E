#include "player.h"

void Player::ProcessKeyboard(PLAYER_MOVEMENT direction, float deltaTime) {
    float velocity = Player_MovementSpeed * deltaTime;
    switch(direction) {
        case PLAYER_FORWARD: {
            Player_Position.z -= velocity;
            Player_Model = glm::translate(Player_Model, glm::vec3(0.f, 0.f, -velocity));
        }
        case PLAYER_BACKWARD: {
            Player_Position.z += velocity;
            Player_Model = glm::translate(Player_Model, glm::vec3(0.f, 0.f, velocity));
        }
        case PLAYER_LEFT: {
            Player_Position.x -= velocity;
            Player_Model = glm::translate(Player_Model, glm::vec3(0.f, 0.f, -velocity));
        }
        case PLAYER_RIGHT: {
            Player_Position.x += velocity;
            Player_Model = glm::translate(Player_Model, glm::vec3(0.f, 0.f, velocity));
        }
    }

    Player_Position.y = 0.f;
}