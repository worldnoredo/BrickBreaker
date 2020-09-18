#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <SDL.h>
#include "MainControl.h"
#include "Object.h"
class Player : public Object
{
public:
    Player();
    virtual ~Player();
    void handleEvent(SDL_Event&);
    void render(SDL_Renderer*);
    void update();
    static const int PLAYER_HITBOX_HEIGHT = 20;
    static const int PLAYER_HITBOX_WIDTH = 100;
};

#endif // PLAYER_H_INCLUDED
