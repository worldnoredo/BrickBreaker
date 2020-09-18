#include "AlertScreen.h"

AlertScreen::AlertScreen()
{
    pos_arr[0].x = 60 + 230;
    pos_arr[0].y = 3 + 270;

    pos_arr[1].x = 60 + 230;
    pos_arr[1].y = 3 + 270;

    pos_arr[2].x = 35 + 230;
    pos_arr[2].y = 40 + 270;

    pos_arr[3].x = 115 + 230;
    pos_arr[3].y = 40 + 270;

    pos_arr[4].x = 60 + 230;
    pos_arr[4].y = 75 + 270;
}

AlertScreen::~AlertScreen()
{

}

void AlertScreen::LoadTextMenu()
{
    text_menu[0].SetText("YOU WIN");
    text_menu[0].SetColor(YELLOW_COLOR);
    text_menu[0].SetRect(pos_arr[0].x, pos_arr[0].y);

    text_menu[1].SetText("YOU LOST");
    text_menu[1].SetColor(YELLOW_COLOR);
    text_menu[1].SetRect(pos_arr[1].x, pos_arr[1].y);

    text_menu[2].SetText("EXIT");
    text_menu[2].SetColor(WHILE_COLOR);
    text_menu[2].SetRect(pos_arr[2].x, pos_arr[2].y);

    text_menu[3].SetText("NEXT");
    text_menu[3].SetColor(WHILE_COLOR);
    text_menu[3].SetRect(pos_arr[3].x, pos_arr[3].y);

    text_menu[4].SetText("REPLAY");
    text_menu[4].SetColor(WHILE_COLOR);
    text_menu[4].SetRect(pos_arr[4].x, pos_arr[4].y);
}

void AlertScreen::ShowMenu(SDL_Renderer* renderer, TTF_Font* font,const bool is_win)
{
    Image::LoadImg("photo//Alert screen.png", renderer);
    rect_.x = 230;
    rect_.y = 270;
    Image::RendImg(rect_.x, rect_.y, renderer);
    if(is_win == true) text_menu[0].CreateGameText(font, renderer);
    else text_menu[1].CreateGameText(font, renderer);
    for(int i = 2; i < 5; i++)
    {
        text_menu[i].CreateGameText(font, renderer);
    }
}

bool AlertScreen::CheckFocusWithRect(const int xm, const int ym, const SDL_Rect text_menu)
{
    if(xm >= text_menu.x && xm <= text_menu.x + text_menu.w &&
       ym >= text_menu.y && ym <= text_menu.y + text_menu.h)
       return true;
    return false;
}

int AlertScreen::handleEvent(SDL_Event& event)
{
    switch(event.type)
    {
        case SDL_MOUSEMOTION:
            xm = event.motion.x;
            ym = event.motion.y;
            for(int i = 2; i < 5; i++)
            {
                if(CheckFocusWithRect(xm, ym, text_menu[i].GetRect()) == true)
                {
                    text_menu[i].SetColor(RED_COLOR);
                }
                else
                {
                    text_menu[i].SetColor(WHILE_COLOR);
                }
            }
            break;

        case SDL_MOUSEBUTTONDOWN:
            xm = event.button.x;
            ym = event.button.y;
            if(CheckFocusWithRect(xm, ym, text_menu[2].GetRect()))
                return 2;
            if(CheckFocusWithRect(xm, ym, text_menu[3].GetRect()))
                return 3;
            if(CheckFocusWithRect(xm, ym, text_menu[4].GetRect()))
                return 4;
            break;
        default:
            break;
    }
    return 6;
}
