#ifndef BOT_H_INCLUDED
#define BOT_H_INCLUDED

#include <SDL.h>
#include "player.h"
#include "MainControl.h"
#include "Object.h"

class Bot : public Object
{
public:
    Bot();
    ~Bot();
    static const int BOT_HITBOX_HEIGHT = 20;
    static const int BOT_HITBOX_WIDTH = 100;
    void render(SDL_Renderer*);
    void update();
    void catchMotionOfBall(int target_X, int target_Y);
    void backToCenter (int target_Y);
    int bot_chance=85;
};

#endif // BOT_H_INCLUDED
