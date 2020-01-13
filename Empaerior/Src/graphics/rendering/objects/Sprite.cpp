#include "pch.h"
#include "Sprite.h"
#include "../../../Application.h"
#include "../../glyphs/Glyphs.h"
#include "../Window.h"


void Empaerior::Sprite::Init(const Empaerior::Rect& m_rect, const Empaerior::Rect& m_tex_rect, const Empaerior::string& tex_path, const unsigned int& m_frames)
{
	rect = m_rect;
	tex_rect = m_tex_rect;
	// load the texture
	texture = Asset_Loading::load_texture(tex_path);
	frames = m_frames;

}

void Empaerior::Sprite::draw(const Camera& camera)
{
	Empaerior::Rect position_rect = {rect.x - camera.rect.x,rect.y - camera.rect.y,rect.w,rect.h };
	if (texture != nullptr)
	{
		//setting the texture's color, because each sprite that uses the texture uses it differently (or not)
		SDL_SetTextureColorMod(texture.get(), r, g, b);//Safe/acceptable to call SDL_SetTextureColorMod a lot?
		//render it
		SDL_RenderCopyEx(Application::window.renderer, &(*texture), &tex_rect, &position_rect, angle, NULL, SDL_FLIP_NONE);
	}
}
Empaerior::Rect const& Empaerior::Sprite::get_dimensions()
{
	return rect;
}
void Empaerior::Text_Sprite::draw(const Camera& camera)
{
	 
	if(!glyphs.empty())renderLine(text_values, rect.x, rect.y , glyphs, Application::window.renderer, rect.w, rect.h,angle,camera.rect.x,camera.rect.y);

}



void Empaerior::Text_Sprite::Init(const Empaerior::Rect& m_rect, const Empaerior::string& font_path, const unsigned int& size, const Empaerior::string& message, Empaerior::Color& color)
{
	rect = m_rect;
	if (createGlyphs(this->glyphs, font_path, size, Application::window.renderer, color) != -1)// create glyphs
	{
		text_values = load_glyph_values(message);//translate the message to glyph values
	}
}
      