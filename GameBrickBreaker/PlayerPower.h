#ifndef PLAYERPOWER_H_INCLUDED
#define PLAYERPOWER_H_INCLUDED

#include "Image.h"
#include <vector>

class PlayerPower : public Image
{
public:
    PlayerPower();
    ~PlayerPower();

    void render(SDL_Renderer* renderer);
    void Decreace();
    int GetNumber() const {return number;}
    void SetNumber(const int x) {number = x;}


private:
    int number;
};

#endif // PLAYERPOWER_H_INCLUDED
