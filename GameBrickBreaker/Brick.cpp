#include "Brick.h"

Brick::Brick()
{
    level = 0;
    m_hitBox.h = BRICK_HITBOX_HEIGHT;
    m_hitBox.w = BRICK_HITBOX_WIDTH;
}

Brick::~Brick()
{

}

void Brick::render(SDL_Renderer* renderer) {
    if(level == 0)
    {
        m_hitBox.x = -100;
        m_hitBox.y = -100;
        SDL_SetRenderDrawColor( renderer, 0xFF,0xFF,0xFF,1 );
    }
    if(level == 1) SDL_SetRenderDrawColor( renderer, 236, 144, 238,1.0);
    if(level == 2) SDL_SetRenderDrawColor( renderer, 236, 64, 122,1.0);
    if(level == 3) SDL_SetRenderDrawColor( renderer, 136, 14, 79,1.0);
    if(level == 4)
    {
        m_hitBox.w = 640;
        m_hitBox.h = 10;
        SDL_SetRenderDrawColor( renderer, 236,144,238, 1);
    }
    //SDL_SetRenderDrawColor( renderer,255,193,7 ,1);
    SDL_RenderFillRect( renderer, &m_hitBox );
}

//bool Brick::isDisappear(Ball ball) {
//
//}

