#ifndef ALERTSCREEN_H_INCLUDED
#define ALERTSCREEN_H_INCLUDED

#include "Image.h"
#include "TextObject.h"
#include "Menu.h"

#include <iostream>

class  AlertScreen : public TextObject
{
public:
    AlertScreen();
    ~AlertScreen();

    void LoadTextMenu();

    void ShowMenu(SDL_Renderer* renderer, TTF_Font* font, const bool is_win);
    bool CheckFocusWithRect(const int xm, const int ym, const SDL_Rect menu_text);
    int handleEvent(SDL_Event &event);
private:
    SDL_Rect pos_arr[5];
    TextObject text_menu[5];
    int xm, ym;
};

#endif // ALERTSCREEN_H_INCLUDED
