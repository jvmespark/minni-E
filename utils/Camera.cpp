#include "Camera.h"

void Camera::translate(float x, float y) {
    level->translate(x, y);
    posX -= x;
    posY -= y;
}

bool Camera::canTranslate(float x, float y) {
    // check if level boundaries are visible
    float boundaryX = level->getBoundaryX();
    float boundaryY = level->getBoundaryY();

    float rightX = posX + sizeX/2 + x;
    float leftX = posX - sizeX/2 - x;
    float rightY = posY + sizeY/2 + y;
    float leftY = posY - sizeY/2 - y;
    std::cout<<"right boundary "<<rightX<<" "<<boundaryX<<std::endl;

    if (0 <= leftX && rightX <= boundaryX && 0 <= leftY && leftY <= boundaryY) {
        return true;
    }
    
    locked = false;
    return false;
}

void Camera::scale(float width, float height) {
    
}