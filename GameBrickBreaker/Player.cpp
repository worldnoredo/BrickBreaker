#include "Player.h"

Player::Player() {
    m_hitBox.h = PLAYER_HITBOX_HEIGHT;
    m_hitBox.w = PLAYER_HITBOX_WIDTH;
    m_hitBox.y = MainControl::HEIGHT - PLAYER_HITBOX_HEIGHT;
    m_hitBox.x = MainControl::WIDTH/2 - (m_hitBox.w / 2) ;
    x_velocity=0;
}
Player::~Player() {
    //dtor
}
void Player::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor( renderer, 0,188,212,1 );
    SDL_RenderFillRect( renderer, &m_hitBox );
}
 void Player::handleEvent(SDL_Event& event)
 {
    switch(event.type)
    {
        case SDL_KEYDOWN:
            if(event.key.keysym.sym ==SDLK_LEFT) {
                if(m_hitBox.x >= 0) {
                    x_velocity = -3;
                }
            }
            else if(event.key.keysym.sym ==SDLK_RIGHT) {
                if(m_hitBox.x <= MainControl::WIDTH - m_hitBox.w) {
                x_velocity = 3;
                }
            }
            break;
        default:
            break;
    }

}

void Player::update() {
    m_hitBox.x += x_velocity;
    x_velocity = 0;
}
