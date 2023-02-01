#ifndef CAMERA_H
#define CAMERA_H

#include "GameLevel.h"
#include "GameObject.h"

class Camera {
    public:
        Camera() {}
        Camera(float x, float y, GameLevel* level_) {
            sizeX = x;
            sizeY = y;
            posX = x / 2;
            posY = y / 2;
            locked = true;
            level = level_;
        }
        void translate(float x, float y); //translate all renderers
        bool canTranslate(float x, float y); // the boundaries are not visible
        float getPosX() { return posX; }
        float getPosY() { return posY; }
        float midLine() { return sizeX / 2; }
        bool isLocked() { return locked; }
        void lock() { locked = true; }
        // rotate
        // post process
        // flip
        // etc
    private:
        float sizeX, sizeY;
        bool notBoundary;
        float posX, posY;
        bool locked;

        //all renderers
        GameLevel* level;
};

#endif