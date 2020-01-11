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

		Graphic_element()
		{

		}

		virtual ~Graphic_element()
		{

		}
		virtual void draw(const Camera& camera) { };
		virtual void update(const Empaerior::u_s_int& dt) {
		
		};
		void set_angle(const double& newAngle)
		{
			angle = newAngle;
		}
		void set_position(const Empaerior::s_int& x, const Empaerior::s_int& y)
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
		
		
		~Sprite()
		{

		}

		// the size of the rect is only for one frame of the sprite
		// so the length of the texture should be frames * tex_rect.w
		void Init(const SDL_Rect& m_rect, const SDL_Rect& m_tex_rect, const Empaerior::string& tex_path, const unsigned int& m_frames);
		//sets a new texture instead of the old one
		//rect , animation  and position doesn't change
		void set_texture(const Empaerior::string& tex_path)
		{
			texture = Asset_Loading::load_texture(tex_path);

		}
		//changes the color of the texture to the rgb value provided
		//255,255,255 - 
		void set_color(Empaerior::byte p_r, Empaerior::byte p_g, Empaerior::byte p_b)
		{
			r = p_r;
			g = p_g;
			b = p_b;
		}
		//sets the number of frames the sprite should rotate through, 
		void set_frames(const Empaerior::byte m_frames)
		{
			frames = m_frames;
		}
		//

		void draw(const Camera& camera) override;

		void update(const Empaerior::u_s_int& dt)
		{
			time += dt; // add the time passed

			while (time >= holdTime)// check if the necesarry time passed
			{
				time -= holdTime;
				next_frame(); // advance
			}
			


		}

	
		
		

	std::shared_ptr<SDL_Texture> texture;
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
		Empaerior::u_s_int anim_x = 0, anim_y = 0;//the unaltered positions of the texture with the initial position 
		
		Empaerior::u_s_int time = 0;
		static constexpr Empaerior::u_s_int holdTime = 250; //time between animations currently 0.25 seconds

		Empaerior::byte frames = 1; //each animation must have at least one frame
		Empaerior::byte cur_frame = 0;

		//color values
		Empaerior::byte r = 0;
		Empaerior::byte g = 0;
		Empaerior::byte b = 255;





	};


	class Text_Sprite : public Graphic_element
	{
	public:
		


		void Init(const SDL_Rect& rect, const Empaerior::string& font_path, const unsigned int& size, const Empaerior::string& message, SDL_Color& color);
		
		// load the font and load the texture

		//to be used when text_function is destroyed
		void clean()
		{
			//destroy the glyphs, becuase unlike the normal sprite, the texture  is unique for all texts and alocatted bu the assetmanager
			Empaerior::u_inter i;
			for (i = 0; i < glyphs.size(); i++)
			{
				glyphs[i].clean();
			}
		}



		void draw(const Camera& camera);
		void update(const Empaerior::u_s_int& dt) {};


	public:
		std::vector<glyph> glyphs; // texts have glyphs instead of texture (the same thing but not )
		std::vector<Empaerior::byte> text_values;

	};
}