#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include "../common/common_headers.h"

#include "GameObject.h"
#include "../render/SpriteRenderer.h"
#include "ResourceManager.h"

#include <vector>
#include <fstream>
#include <sstream>

class GameLevel {
    public:
        // level state
        std::vector<GameObject> Bricks;
        // constructor
        GameLevel() { }
        // loads level from file
        void Load(const char *file, unsigned int levelWidth, unsigned int levelHeight);
        // render level
        void Draw(SpriteRenderer &renderer);
        // check if the level is completed (all non-solid tiles are destroyed)
        bool IsCompleted();

        void translate(float x, float y);

        float getLevelHeight() const { return unit_height; }
        float getLevelWidth() const { return unit_width; }
        float getBoundaryX() const { return boundaryWidth; }
        float getBoundaryY() const { return boundaryHeight; }
    private:
        // initialize level from tile data
        float unit_height;
        float unit_width;
        unsigned int height;
        unsigned int width;
        float boundaryHeight;
        float boundaryWidth;
        void init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight);
};

#endif