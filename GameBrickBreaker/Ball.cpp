#include "Ball.h"
Ball::Ball() {
    //ctor
    m_hitBox.h = BALL_HITBOX_HEIGHT;
    m_hitBox.w = BALL_HITBOX_WIDTH;
    m_hitBox.y = 640 - 22 - BALL_HITBOX_HEIGHT;
    m_hitBox.x = 640 / 2 - 5;
    x_velocity=2;
    y_velocity=2;
}
Ball::~Ball()
{
    //dtor
}

void Ball::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor( renderer, 255, 255, 255, 255 );
    SDL_RenderFillRect( renderer, &m_hitBox );
}

void Ball::update() {
    if(m_hitBox.x >= 640 - m_hitBox.w)
    {
        reverseX_Velocity();
    }
    if(m_hitBox.x <= 0)
    {
        reverseX_Velocity();
    }
//     if(m_hitBox.y <= 0) {
//        reverseY_Velocity();
//    }
    m_hitBox.x += x_velocity;
    m_hitBox.y += y_velocity;
}




