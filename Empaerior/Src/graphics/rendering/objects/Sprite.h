#pragma once
#include "../../../assetmanager/AssetManager.h"
#include "../Camera.h"
namespace Empaerior {
	///base  class for sprite elements, practically vritual
	class Graphic_element
	{
	public:
		Graphic_element(const SDL_Rect& rect)
			:rect(rect)
			// the size of the rect is only for one frame of the sprite
			// so the length of the texture should be frames * tex_rect.w
		{

		}



		virtual ~Graphic_element()
		{

		}



		virtual void draw(const Camera& camera) {};


		virtual void update(const Uint32& dt) {};

		void set_angle(const double& newAngle)
		{
			angle = newAngle;
		}



		void set_position(const int& x, const int& y)
		{
			rect.x = x;
			rect.y = y;
			return;
		}


	protected:


	public:


	protected:

		SDL_Rect rect; // the sprite




		double angle = 0; // rotation fo the element


	};

	class Sprite : public Graphic_element
	{
	public:
		// the size of the rect is only for one frame of the sprite
	    // so the length of the texture should be frames * tex_rect.w
		Sprite(const SDL_Rect& rect, const SDL_Rect& tex_rect, const std::string& tex_path, const unsigned int& frames)
			:Graphic_element(rect), tex_rect(tex_rect), anim_x(tex_rect.x), anim_y(tex_rect.y),frames(frames)

		{

			//load the texture
			
			texture = Asset_Loading::load_texture(tex_path);

		}
		~Sprite()
		{

		}

	
		void set_texture(const std::string& tex_path)
		{
			texture = Asset_Loading::load_texture(tex_path);
		}


		void draw(const Camera& camera);

		void update(const uint64_t& dt)
		{
			 
			time += dt; // add the time passed
			
			while (time >= holdTime)// check if the necesarry time passed
			{
				time -= holdTime;
				next_frame(); // advance
			}


		}



	private:
		void next_frame()// goes to the next frame in the animation 
		{
			
			// get next frame in animation
			if (cur_frame >= frames - 1)
			{
				cur_frame = 0;
			}
			else
			{
				++cur_frame;
			}
			//set the frame
			tex_rect.x = anim_x + cur_frame * tex_rect.w;
			tex_rect.y = anim_y + cur_frame * tex_rect.h;
			
		}



		SDL_Rect tex_rect;// the portion of the texture the sprite represents
		unsigned int anim_x = 0, anim_y = 0;//the unaltered positions of the texture with the initial position 
		std::shared_ptr<SDL_Texture> texture;
		uint64_t time = 0;
		static constexpr Uint32 holdTime = 250; //time between animations currently 0.25 seconds

		unsigned int frames = 1; //each animation must have at least one frame
		unsigned int cur_frame = 0;

	};


	class Text_Sprite : public Graphic_element
	{
	public:
		Text_Sprite(const SDL_Rect& rect, const std::string& font_path, const unsigned int& size, const std::string& message, SDL_Color& color);


		
		// load the font and load the texture

		~Text_Sprite()
		{
			//destroyer the glyphs, becuase unlike 6the normal sprite, the texture  is unique for all texts and alocatted bu the assetmanager
			unsigned int i;
			for (i = 0; i < glyphs.size(); i++)
			{
				glyphs[i].clean();
			}


		}
		void draw(const Camera& camera);
	


	public:
		std::vector<glyph> glyphs; // texts have glyphs instead of texture (the same thing but not )
		std::vector<int> text_values;

	};
}