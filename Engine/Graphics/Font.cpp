#include "Graphics/Font.h"
#include <cassert>

nc::Font::~Font() {

	if (font != nullptr) {

		TTF_CloseFont(font);
	}
}

bool nc::Font::Load(const std::string& name, void* data)
{
	assert(data);

	font = TTF_OpenFont(name.c_str(), *static_cast<int*>(data));
		//<TTF_OpenFont, use c string of name, cast data to int* then dereference for pixel size>

		if (font == nullptr)
		{
			std::cout << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
			return false;
		}

	return true;

}

SDL_Surface* nc::Font::CreateSurface(const std::string& text, const nc::Color& color) {

	
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
		//<TTF_RenderText_Solid, use TTF font and color for the parameters>
		if (surface == nullptr)
		{
			std::cout << "TTF_RenderText_Solid Error: " << SDL_GetError() << std::endl;
		}
	return surface;
	
}
