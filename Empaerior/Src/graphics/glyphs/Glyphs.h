#pragma once
//thanks to GRHmedia  for his glyphs system




#include "../../SDLwrappers/Ptr_Wrappers.h"




enum class LETTERS {
	a = 10, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z, A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, PERIOD, COMMA,
	EXCLAMATION, AT, HASH, DOLLAR_SIGN, PERCENT, AND, COLON, S_SOLON, SINGLE_QUOTE, DOUBLE_QUOTE, LEFT_BRACKET, RIGHT_BRACKET, LEFT_SQUARE,
	RIGHT_SQUARE, LESS_THAN, GREATER_THAN, DIVIDE, PLUS, MINUS, EQUAL, MULTIPLY, SPACE, RETURN, NEW_LINE, TAB
};


struct glyph {
	void clean()
	{
		 SDL_DestroyTexture(&*image);
		
	}

	
	std::unique_ptr<SDL_Texture> image;
	int w, h;
};



//This function creates textures for all the characters
int createGlyphs(std::vector <glyph>& glyphs, const std::string& path, const unsigned int& size, SDL_Renderer* renderer, SDL_Color& color);



int renderLine_st(const std::string& text, int const& margin, int const& Y, std::vector <glyph>& glyphs, SDL_Renderer* renderer, int const& screenWidth, int const& screenHeight, const double& angle, const int& camera_x, const int& camera_y);


int renderLine(const std::vector<int>& text, int const& margin, int const& Y, std::vector <glyph>& glyphs, SDL_Renderer* renderer, int const& screenWidth, int const& screenHeight,const double & angle, const int& camera_x, const int& camera_y);


std::vector<int> load_glyph_values(const std::string& source);
int getValue(char Letter);





