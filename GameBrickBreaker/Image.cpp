#include "Image.h"

Image::Image()
{
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = 0;
	rect_.h = 0;
	p_object_ = nullptr;
}

Image::~Image()
{
	if (p_object_ != nullptr)
	{
		SDL_DestroyTexture(p_object_);
	}
	p_object_ = nullptr;
}

//SDL_Texture*
bool Image::LoadImg(std::string path, SDL_Renderer* renderer)
{
    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if( loadedSurface == NULL )
    {
        std::cout << "\nIMG_Load error: " << IMG_GetError();
    }
    else
    {
        SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0, 0 ) );
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
        if( newTexture == NULL )
        {
            std::cout << "\nSDL_CreateTextureFromSurface error: " << SDL_GetError();
        }
        else
        {
            rect_.w = loadedSurface->w;
            rect_.h = loadedSurface->h;
        }
        SDL_FreeSurface( loadedSurface );
    }
    p_object_ = newTexture;
    //SDL_DestroyTexture(newTexture);
	return p_object_ != nullptr;
}

void Image::RendImg( int x, int y, SDL_Renderer* renderer )
{
    SDL_Rect renderQuad = { x, y, rect_.w, rect_.h };
    SDL_RenderCopy( renderer, p_object_, NULL, &renderQuad );
    SDL_DestroyTexture(p_object_);
}
