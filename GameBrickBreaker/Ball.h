#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include <SDL.h>
#include <cmath>
//#include "MainControl.h"
#include "Object.h"

class Ball : public Object
{
    public:
        static const int BALL_HITBOX_HEIGHT = 15;
        static const int BALL_HITBOX_WIDTH = 15;
        Ball();
        virtual ~Ball();
        void render(SDL_Renderer*);
        void update();
};

#endif // BALL_H_INCLUDED
