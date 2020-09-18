#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "Image.h"
#include "TextObject.h"
#include <iostream>
//#include "Ball.h"
#include <string>
#include "Ball.h"

class Menu : public TextObject
{
public:
    Menu();
    ~Menu();

    void LoadTextMenu();
    void SetLevel(int number)
    {
        number_level;
    }
    int GetLevel() const {return number_level;}

    void ShowMenu(SDL_Renderer* renderer, TTF_Font* font);
    bool CheckFocusWithRect(const int xm, const int ym, const SDL_Rect menu_text);
    int handleEvent(SDL_Event &event);

    void ballAction(SDL_Renderer* renderer);
private:
    Ball* ball_;

    SDL_Rect pos_arr[2];
    Image image_menu[2];

    TextObject text_menu[2];
    int xm, ym;
    int number_level;
    SDL_Rect pos_image[2];
};

#endif // MENU_H_INCLUDED
