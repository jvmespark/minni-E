#ifndef ENEMY_CLASS_H
#define ENEMY_CLASS_H

#include "../../common/common_headers.h"
#include "../core/GameObject.h"
#include "../core/ResourceManager.h"
#include "../render/SpriteRenderer.h"

#include <string>

// A* enemy 
class EnemyClass {
    public:
        EnemyClass();
        EnemyClass(float velocity, float spawnX, float spawnY, const char* enemyAsset, float sizeX, float sizeY, SpriteRenderer* renderer_);
        /*
            add later:
                pass enemy movement and attacks as functions declared outside the engine
                the engine should take care of the rendering and the initializing only
        */

        void render();
        void moveTo(float x, float y); // A* to this position
        void translate(float x, float y);
        // attack / damage
    private:
        float enemy_sizeX, enemy_sizeY;
        float enemy_velocity;
        
        SpriteRenderer* renderer;
        GameObject* EnemyObj;

        void load_textures();
};


#endif