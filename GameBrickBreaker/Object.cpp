#include "Object.h"

Object::Object()
{
    m_hitBox.h = 0;
    m_hitBox.w = 0;
    m_hitBox.y = 0;
    m_hitBox.x = 0;
    x_velocity = 0;
    y_velocity = 0;
}

Object::~Object()
{

}
