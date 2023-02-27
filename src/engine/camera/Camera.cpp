#include "Camera.h"

void Camera::translate(float x, float y) {
    level->translate(x, y);
    for (int i = 0; i < enemies.size(); i++) {
        enemies[i]->translate(x,y);
    }
    posX -= x;
    posY -= y;
}

bool Camera::canTranslate(float x, float y) {
    // check if level boundaries are visible
    float boundaryX = level->getBoundaryX();
    float boundaryY = level->getBoundaryY();

    float rightX = posX + width/2 + x;
    float leftX = posX - width/2 - x;
    float rightY = posY + height/2 + y;
    float leftY = posY - height/2 - y;

    if (0 <= leftX && rightX <= boundaryX && 0 <= leftY && leftY <= boundaryY) {
        return true;
    }
    
    locked = false;
    return false;
}

void Camera::scale(float width, float height) {}

#define SDL_LOCKIFMUST(s) (SDL_MUSTLOCK(s) ? SDL_LockSurface(s) : 0)
#define SDL_UNLOCKIFMUST(s) { if(SDL_MUSTLOCK(s)) SDL_UnlockSurface(s); }

int invert_surface_vertical(SDL_Surface *surface)
{
    Uint8 *t;
    register Uint8 *a, *b;
    Uint8 *last;
    register Uint16 pitch;

    if( SDL_LOCKIFMUST(surface) < 0 )
        return -2;

    /* do nothing unless at least two lines */
    if(surface->h < 2) {
        SDL_UNLOCKIFMUST(surface);
        return 0;
    }

    /* get a place to store a line */
    pitch = surface->pitch;
    t = (Uint8*)malloc(pitch);

    if(t == NULL) {
        SDL_UNLOCKIFMUST(surface);
        return -2;
    }

    /* get first line; it's about to be trampled */
    memcpy(t,surface->pixels,pitch);

    /* now, shuffle the rest so it's almost correct */
    a = (Uint8*)surface->pixels;
    last = a + pitch * (surface->h - 1);
    b = last;

    while(a < b) {
        memcpy(a,b,pitch);
        a += pitch;
        memcpy(b,a,pitch);
        b -= pitch;
    }

    /* in this shuffled state, the bottom slice is too far down */
    memmove( b, b+pitch, last-b );

    /* now we can put back that first row--in the last place */
    memcpy(last,t,pitch);

    /* everything is in the right place; close up. */
    free(t);
    SDL_UNLOCKIFMUST(surface);

    return 0;
}

void Camera::screenshot() {
    SDL_Surface * image = SDL_CreateRGBSurface(SDL_SWSURFACE, this->width, this->height, 24, 0x000000FF, 0x0000FF00, 0x00FF0000, 0);

    glReadPixels(0, 0, this->width, this->height, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);

    invert_surface_vertical(image);

    SDL_SaveBMP(image, "../screenshots/image.bmp"); // expand later so I can have multiple shots? Maybe the player can name it too?
    SDL_FreeSurface(image);
}