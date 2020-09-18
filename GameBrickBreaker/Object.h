#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include <SDL.h>
#include <iostream>

class Object
{
    public:
        Object();
        virtual ~Object();

        int getX() {return m_hitBox.x;}
        int getY() {return m_hitBox.y;}

        int getX_Velocity() {return x_velocity;}
        int getY_Velocity() {return y_velocity;}

        void reverseX_Velocity() {x_velocity = -x_velocity;}
        void reverseY_Velocity() {y_velocity = - y_velocity;}
        void setX_Y_Velocity(int x_vel, int y_vel)
        {
            x_velocity = x_vel;
            y_velocity = y_vel;
        }

        void setHitBox(int x, int y)
        {
            m_hitBox.x = x;
            m_hitBox.y = y;
        }
        SDL_Rect getHitBox() {return m_hitBox; };
    protected:
        SDL_Rect m_hitBox;
        float x_velocity,y_velocity;
};

#endif // OBJECT_H_INCLUDED
