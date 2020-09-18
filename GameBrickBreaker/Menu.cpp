#include "Menu.h"
#include"Ball.h"

Menu::Menu()
{
    pos_arr[0].x = 305;
    pos_arr[0].y = 350;
    pos_arr[1].x = 150;
    pos_arr[1].y = 450;
    number_level = 1;
    ball_ = new Ball();
    ball_->setHitBox(317,300 - 16);
}

Menu::~Menu()
{
    SDL_DestroyTexture(p_object_);
}

void Menu::ballAction(SDL_Renderer* renderer)
{
    //ball_ = new Ball();
    //ball_->setHitBox(317,300);
    //ball_->setX_Y_Velocity(1,1);
    if(ball_->getY() == 134)
    {
        ball_->reverseX_Velocity();
        ball_->reverseY_Velocity();
    }
    if(ball_->getY() == 300-16)
    {
        ball_->reverseY_Velocity();
    }
    ball_->update();
    ball_->render(renderer);
}

void Menu::LoadTextMenu()
{
    std::string number = std::to_string (number_level);
    text_menu[0].SetText(number);
    text_menu[0].SetColor(WHILE_COLOR);
    text_menu[0].SetRect(pos_arr[0].x, pos_arr[0].y);

    text_menu[1].SetText("PLAY GAME");
    text_menu[1].SetColor(BLUE_COLOR);
    text_menu[1].SetRect(pos_arr[1].x, pos_arr[1].y);

}

void Menu::ShowMenu(SDL_Renderer* renderer, TTF_Font* font)
{
    Image::LoadImg("photo//menu.png", renderer);

    Image::RendImg(0, 0, renderer);

    for(int i = 0; i < 2; i++)
    {
        pos_image[i].x = i * 100 + 260;
        pos_image[i].y = 350;
        if(i == 0)image_menu[i].LoadImg("photo//giam.png", renderer);
        else image_menu[i].LoadImg("photo//tang.png", renderer);
        image_menu[i].RendImg(pos_image[i].x, pos_image[i].y, renderer);
        image_menu[i].SetRect(pos_image[i].x, pos_image[i].y);
    }

    for(int i = 0; i < 2; i++)
    {
        text_menu[i].CreateGameText(font, renderer);
    }
    ballAction(renderer);
}

bool Menu::CheckFocusWithRect(const int xm, const int ym, const SDL_Rect text_menu)
{
    if(xm >= text_menu.x && xm <= text_menu.x + text_menu.w &&
       ym >= text_menu.y && ym <= text_menu.y + text_menu.h)
       return true;
    return false;
}

int Menu::handleEvent(SDL_Event& event)
{
    std::string number = std::to_string (number_level);
    text_menu[0].SetText(number);
    switch(event.type)
    {
        case SDL_MOUSEMOTION:
            xm = event.motion.x;
            ym = event.motion.y;
            //for(int i = 0; i < 2; i++)
            //{
                if(CheckFocusWithRect(xm, ym, text_menu[1].GetRect()) == true)
                {
                    text_menu[1].SetColor(RED_COLOR);
                }
                else
                {
                    text_menu[1].SetColor(BLUE_COLOR);
                }
            //}
            break;

        case SDL_MOUSEBUTTONDOWN:
            xm = event.button.x;
            ym = event.button.y;
            if(CheckFocusWithRect(xm, ym, text_menu[1].GetRect()))
                return 1;
            if(CheckFocusWithRect(xm, ym, image_menu[0].GetRect()))
            {
                number_level--;
                if(number_level == 0) number_level = 6;
            }
            if(CheckFocusWithRect(xm, ym, image_menu[1].GetRect()))
            {
                number_level++;
                if(number_level == 7) number_level =1;
            }
            event.type = SDLK_UP;
            break;
        default:
            break;
    }
    //event.type = SDLK_UP;
    return 2;
}


