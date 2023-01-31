#ifndef CAMERA_H
#define CAMERA_H

#include "GameLevel.h"
#include "GameObject.h"

class Camera {
    public:
        Camera() {}
        Camera(GameLevel* level_) {
            level = level_;
        }
        void translate(float x, float y); //translate all renderers
        // rotate
        // post process
        // flip
        // etc
    private:
        //all renderers
        GameLevel* level;
};

#endif