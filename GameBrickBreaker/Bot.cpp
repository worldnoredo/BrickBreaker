#include"Bot.h"

Bot::Bot()
{
    m_hitBox.h = BOT_HITBOX_HEIGHT;
    m_hitBox.w = BOT_HITBOX_WIDTH;
    m_hitBox.y = 50;
    m_hitBox.x = MainControl::WIDTH/2 - (m_hitBox.w / 2) ;
}

Bot::~Bot()
{

}

void Bot::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor( renderer, 0,188,212,1 );
    SDL_RenderFillRect( renderer, &m_hitBox );
}

void Bot::update() {
    m_hitBox.x += x_velocity;
    x_velocity = 0;
}

void Bot::catchMotionOfBall(int target_X ,int target_Y) {
    if(target_Y <=  MainControl::HEIGHT/2) {
        if(target_X <= this->m_hitBox.x + this->m_hitBox.w/3) {
            if(this->m_hitBox.x >= 0) {
                this->x_velocity = -2;
            }
        }
        else if(target_X >= this->m_hitBox.x +this->m_hitBox.w*(2/3)) {
            if(this->m_hitBox.x + m_hitBox.w <= MainControl::WIDTH) {
                this-> x_velocity = 2;
            }
        }
        else {
            this->x_velocity = 0;
        }
    }
}

void Bot::backToCenter(int target_Y) {
    if(target_Y > MainControl::HEIGHT / 2) {
        if(m_hitBox.x < MainControl::WIDTH / 2 - m_hitBox.w / 2) {
            x_velocity = 1;
        }
        if(m_hitBox.x > MainControl::WIDTH / 2 - m_hitBox.w / 2) {
            x_velocity = -1;
        }
    }
}
