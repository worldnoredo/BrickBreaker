#ifndef TEXTOBJECT_H_INCLUDED
#define TEXTOBJECT_H_INCLUDED

#include <SDL_ttf.h>
#include  "Image.h"

class TextObject : public Image
{
public:
    TextObject();
    ~TextObject();
    enum TextColor
    {
        RED_COLOR = 0,
        WHILE_COLOR = 1,
        YELLOW_COLOR = 2,
        BLUE_COLOR = 3
    };

    void SetText(std::string text)
    {
        str_val = text;
    }

    void SetColor(const int type);

    void CreateGameText(TTF_Font* font, SDL_Renderer* renderer);

private:
    std::string str_val;
    SDL_Color text_color;

};

#endif // TEXTOBJECT_H_INCLUDED
