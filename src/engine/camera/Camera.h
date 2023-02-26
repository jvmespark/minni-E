#ifndef CAMERA_H
#define CAMERA_H

#include "../core/GameLevel.h"
#include "../core/GameObject.h"

class Camera {
    public:
        Camera() {}
        Camera(float x, float y, GameLevel* level_) {
            width = x;
            height = y;
            posX = x / 2;
            posY = y / 2;
            locked = true;
            level = level_;
        }
        void translate(float x, float y); //translate all renderers
        bool canTranslate(float x, float y); // the boundaries are not visible
        float getPosX() { return posX; }
        float getPosY() { return posY; }
        float midLine() { return width / 2; }
        bool isLocked() { return locked; }
        void lock() { locked = true; }
        void scale(float width, float height);

        void screenshot();
        // rotate
        // post process
        // flip
        // etc
    private:
        float width, height;
        bool notBoundary;
        float posX, posY;
        bool locked;

        //all renderers
        GameLevel* level;
};

#endif