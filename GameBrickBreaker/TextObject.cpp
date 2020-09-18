#include "TextObject.h"

TextObject::TextObject()
{
    str_val = "Mark: ";
    text_color = {255, 0, 0};
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
}

TextObject::~TextObject()
{

}

void TextObject::SetColor(const int type)
{
    if(type == RED_COLOR)
    text_color = {255, 0, 0};
    if(type == WHILE_COLOR)
    {
        text_color = {255, 255, 255};
    }
    if(type == YELLOW_COLOR)
    {
        text_color = {213, 155, 0};
    }
    if(type == BLUE_COLOR)
    {
        text_color = {0, 153, 153};
    }
}

void TextObject::CreateGameText(TTF_Font* font, SDL_Renderer* renderer)
{
    SDL_Surface* surface = TTF_RenderText_Solid(font, str_val.c_str(), text_color);
    p_object_ = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect srcRest;
    TTF_SizeText(font, str_val.c_str(), &srcRest.w, &srcRest.h);
    rect_.w = srcRest.w;
    rect_.h = srcRest.h;

    Image::RendImg(rect_.x, rect_.y, renderer);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(p_object_);
}

