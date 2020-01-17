#pragma once
//thanks to GRHmedia  for his glyphs system



#include <iostream>
#include "../../SDLwrappers/Ptr_Wrappers.h"

namespace Empaerior {



	enum class LETTERS {
		a = 10, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, PERIOD, COMMA,
		EXCLAMATION, AT, HASH, DOLLAR_SIGN, PERCENT, AND, COLON, S_SOLON, SINGLE_QUOTE, DOUBLE_QUOTE, LEFT_BRACKET, RIGHT_BRACKET, LEFT_SQUARE,
		RIGHT_SQUARE, LESS_THAN, GREATER_THAN, DIVIDE, PLUS, MINUS, EQUAL, MULTIPLY, SPACE, RETURN, NEW_LINE, TAB
	};

	//glyphs must be deallocated 
	class glyph {
	public:
		
		void clean()
		{
			SDL_DestroyTexture(&*image);
			
		}

		SDL_Texture* image;
		Empaerior::fl_point w, h;
	};



	//This function creates textures for all the characters
	Empaerior::byte createGlyphs(std::vector <Empaerior::glyph>& glyphs, const Empaerior::string& path, const unsigned int& size, SDL_Renderer* renderer, Empaerior::Color& color);



	void renderLine_st(const Empaerior::string& text, Empaerior::fl_point const& margin, Empaerior::fl_point const& Y, std::vector <glyph>& glyphs, SDL_Renderer* renderer, Empaerior::fl_point const& screenWidth, Empaerior::fl_point const& screenHeight, const Empaerior::fl_point& angle, const Empaerior::fl_point& camera_x, const Empaerior::fl_point& camera_y);


	void renderLine(const std::vector<Empaerior::byte>& text, Empaerior::fl_point const& margin, Empaerior::fl_point const& Y, std::vector <glyph>& glyphs, SDL_Renderer* renderer, Empaerior::fl_point const& screenWidth, Empaerior::fl_point const& screenHeight, const Empaerior::fl_point& angle, const Empaerior::fl_point& camera_x, const Empaerior::fl_point& camera_y);


	std::vector<Empaerior::byte> load_glyph_values(const  Empaerior::string& source);
	int getValue(Empaerior::ch Letter);





}