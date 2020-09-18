#ifndef BRICK_H_INCLUDED
#define BRICK_H_INCLUDED

#include <SDL.h>
#include "Ball.h"
#include "Object.h"

class Brick : public Object
{
public:
    static const int BRICK_HITBOX_HEIGHT = 20;
    static const int BRICK_HITBOX_WIDTH = 40;
    Brick();
     ~Brick();
    void render(SDL_Renderer*);

    int GetLevel() const {return level;}
    void SetLevel (const int number)
    {
        level = number;
    }
private:
    int level;
};

#endif // BRICK_H_INCLUDED
