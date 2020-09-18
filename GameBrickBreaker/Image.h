#ifndef IMAGE_H_INCLUDED
#define IMAGE_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

class Image
{
public:
	Image();
	~Image();

	void SetRect(const int x, const int y)
	{
		rect_.x = x;
		rect_.y = y;
	}

	SDL_Rect GetRect() const { return rect_; }

	void SetObject(SDL_Texture* object) {p_object_ = object;}
	SDL_Texture* GetObject() { return p_object_; }

	bool LoadImg(std::string path, SDL_Renderer* renderer);
	void RendImg(int x, int y, SDL_Renderer* renderer);

protected:
	SDL_Rect rect_;
	SDL_Texture* p_object_;
};

#endif // IMAGE_H_INCLUDED
