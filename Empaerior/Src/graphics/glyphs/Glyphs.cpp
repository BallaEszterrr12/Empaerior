#include "pch.h"
#include "Glyphs.h"
#include "../../assetmanager/AssetManager.h"
#include "SDLwrappers/Rendering_Wrappers.h"
namespace Empaerior {


	Empaerior::byte createGlyphs(std::vector <glyph>& glyphs, const Empaerior::string& path, const unsigned int& size, SDL_Renderer* renderer, Empaerior::Color& color)
	{
		Empaerior::s_int w, h;
		Empaerior::ch fontChar[86] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.,!@#$%&:;'{}[]<>/+-=*";
		fontChar[84] = '"'; fontChar[85] = ' ';
		SDL_Surface* tempSurface;
		TTF_Font* font = Empaerior::Asset_Loading::load_font(path, size);
		if (font == nullptr)  return -1;
		glyph temp;
		Empaerior::ch shortString[2] = "";

		for (int cnt = 0; cnt < 86; cnt++) {
			
			shortString[0] = fontChar[cnt];
			tempSurface = TTF_RenderText_Solid(font, shortString, color);
			temp.image = SDL_CreateTextureFromSurface(renderer, tempSurface);
			SDL_QueryTexture(&(*temp.image), NULL, NULL, &w, &h);
			temp.h = h; temp.w = w;
			glyphs.push_back(std::move(temp));
			SDL_FreeSurface(tempSurface);// delete surface
		}
		return 1;
	}

	//renders from string
	void renderLine_st(const Empaerior::string& text, Empaerior::fl_point const& margin, Empaerior::fl_point const& Y, std::vector <glyph>& glyphs, SDL_Renderer* renderer, Empaerior::fl_point const& screenWidth, Empaerior::fl_point const& screenHeight, const Empaerior::fl_point& angle, const Empaerior::fl_point& camera_x, const Empaerior::fl_point& camera_y)
	{
		
		Empaerior::fl_point x = margin, y = Y, wX = 0;
		Empaerior::Float_Rect textRect;
		Empaerior::byte lValue = 0;
		Empaerior::u_inter lastSpace = 0;
		Empaerior::boole safe = true;

		for (Empaerior::u_inter cnt = 0; cnt < text.length(); cnt++)
		{   //covert from character to glyph id
			lValue = getValue(text[cnt]);

			if (lValue == 85) {
				lastSpace = cnt; wX = x + glyphs[85].w;
				//need to read ahead make sure room for next word if not then skip to next line
				for (Empaerior::u_inter t = lastSpace + 1; t < text.length(); t++) {
					lValue = getValue(text[t]);
					wX = wX + glyphs[lValue].w;
					if (wX >= screenWidth - margin) {
						safe = false;
						break;
					}
					if (lValue == 85) {
						safe = true;
						break;
					}
				}
			}
			if (true) {
				textRect.x = x - camera_x; textRect.y = y - camera_y; textRect.w = glyphs[lValue].w; textRect.h = glyphs[lValue].h;
				Empaerior::Render::RenderEx(renderer, &(*glyphs[lValue].image), NULL, &textRect,0,  angle, SDL_FLIP_NONE);
				x = x + glyphs[lValue].w;
			}
			else { cnt = lastSpace; x = margin; y = y + glyphs[lValue].h; safe = true; }
		}
	//	std::cout << '\n';
	
	}
	//slower,as  it doesn't preload the values but simpler

	//TODO: Addapt to render wrapper
	//renders from a vector of int,where each int is a value of a char from glyphs
	void renderLine(const std::vector<Empaerior::byte>& text, Empaerior::fl_point const& margin, Empaerior::fl_point const& Y, std::vector <glyph>& glyphs, SDL_Renderer* renderer, Empaerior::fl_point const& screenWidth, Empaerior::fl_point const& screenHeight, const Empaerior::fl_point& angle, const Empaerior::fl_point& camera_x, const Empaerior::fl_point& camera_y)
	{
		
		Empaerior::fl_point x = margin, y = Y, wX = 0;
		Empaerior::Float_Rect textRect;
		Empaerior::byte lValue = 0;
		Empaerior::u_inter lastSpace = 0;
		Empaerior::boole safe = true;

		for (Empaerior::u_inter cnt = 0; cnt < text.size(); cnt++)
		{   //covert from character to glyph id
			lValue = text[cnt];

			if (lValue == 85) {
				lastSpace = cnt; wX = x + glyphs[85].w;
				//need to read ahead make sure room for next word if not then skip to next line
				for (Empaerior::u_inter t = lastSpace + 1; t < text.size(); t++) {
					int m_lValue = text[t];
					wX = wX + glyphs[m_lValue].w;
					if (wX >= screenWidth - margin) {
						safe = false;
						break;
					}
					if (m_lValue == 85) {
						safe = true;
						break;
					}
				}
			}
			if (safe) {

				textRect.x = x - camera_x; textRect.y = y - camera_y; textRect.w = glyphs[lValue].w; textRect.h = glyphs[lValue].h;
			
				Empaerior::Render::RenderEx(renderer, &(*glyphs[lValue].image), NULL, &textRect, 0, angle, SDL_FLIP_NONE);
				x = x + glyphs[lValue].w;
			}
			else { cnt = lastSpace; x = margin; y = y + glyphs[lValue].h; safe = true; }
		}

		
	}
	//faster,but you need to preload the vector



	std::vector<Empaerior::byte> load_glyph_values(const Empaerior::string& source)
	{
	
		std::vector<Empaerior::byte> text;
		for (int i = 0; i < source.length(); i++) {
			text.emplace_back(getValue(source[i]));
		}

		return text;
	}




	int getValue(char Letter) {

		switch (Letter) {
		case '0':
		{
			return 0;
		}
		case '1':
		{
			return 1;
		}
		case '2':
		{
			return 2;
		}
		case '3':
		{
			return 3;
		}
		case '4':
		{
			return 4;
		}
		case '5':
		{
			return 5;
		}
		case '6':
		{
			return 6;
		}
		case '7':
		{
			return 7;
		}
		case '8':
		{
			return 8;
		}
		case '9':
		{
			return 9;
		}
		case 'a':
		{
			return 10;
		}
		case 'b':
		{
			return 11;
		}
		case 'c':
		{
			return 12;
		}
		case 'd':
		{
			return 13;
		}
		case 'e':
		{
			return 14;
		}
		case 'f':
		{
			return 15;
		}
		case 'g':
		{
			return 16;
		}
		case 'h':
		{
			return 17;
		}
		case 'i':
		{
			return 18;
		}
		case 'j':
		{
			return 19;
		}
		case 'k':
		{
			return 20;
		}
		case 'l':
		{
			return 21;
		}
		case 'm':
		{
			return 22;
		}
		case 'n':
		{
			return 23;
		}
		case 'o':
		{
			return 24;
		}
		case 'p':
		{
			return 25;
		}
		case 'q':
		{
			return 26;
		}
		case 'r':
		{
			return 27;
		}
		case 's':
		{
			return 28;
		}
		case 't':
		{
			return 29;
		}
		case 'u':
		{
			return 30;
		}
		case 'v':
		{
			return 31;
		}
		case 'w':
		{
			return 32;
		}
		case 'x':
		{
			return 33;
		}
		case 'y':
		{
			return 34;
		}
		case 'z':
		{
			return 35;
		}
		case 'A':
		{
			return 36;
		}
		case 'B':
		{
			return 37;
		}
		case 'C':
		{
			return 38;
		}
		case 'D':
		{
			return 39;
		}
		case 'E':
		{
			return 40;
		}
		case 'F':
		{
			return 41;
		}
		case 'G':
		{
			return 42;
		}
		case 'H':
		{
			return 43;
		}
		case 'I':
		{
			return 44;
		}
		case 'J':
		{
			return 45;
		}
		case 'K':
		{
			return 46;
		}
		case 'L':
		{
			return 47;
		}
		case 'M':
		{
			return 48;
		}
		case 'N':
		{
			return 49;
		}
		case 'O':
		{
			return 50;
		}
		case 'P':
		{
			return 51;
		}
		case 'Q':
		{
			return 52;
		}
		case 'R':
		{
			return 53;
		}
		case 'S':
		{
			return 54;
		}
		case 'T':
		{
			return 55;
		}
		case 'U':
		{
			return 56;
		}
		case 'V':
		{
			return 57;
		}
		case 'W':
		{
			return 58;
		}
		case 'X':
		{
			return 59;
		}
		case 'Y':
		{
			return 60;
		}
		case 'Z':
		{
			return 61;
		}
		case '.':
		{
			return 62;
		}
		case ',':
		{
			return 63;
		}
		case '!':
		{
			return 64;
		}
		case '@':
		{
			return 65;
		}
		case '#':
		{
			return 66;
		}
		case '$':
		{
			return 67;
		}
		case '%':
		{
			return 68;
		}
		case '&':
		{
			return 69;
		}
		case ':':
		{
			return 70;
		}
		case ';':
		{
			return 71;
		}
		case '\'':
		{
			return 72;
		}
		case '{':
		{
			return 73;
		}
		case '}':
		{
			return 74;
		}
		case '[':
		{
			return 75;
		}
		case ']':
		{
			return 76;
		}
		case '<':
		{
			return 77;
		}
		case '>':
		{
			return 78;
		}
		case '/':
		{
			return 79;
		}
		case '+':
		{
			return 80;
		}
		case '-':
		{
			return 81;
		}
		case '=':
		{
			return 82;
		}
		case '*':
		{
			return 83;
		}
		case '"':
		{
			return 84;
		}
		case ' ':
		{
			return 85;
		}
		case '\r':
		{
			return 85;
		}
		case '\n':
		{
			return 85;
		}
		case '\t':
		{
			return 85;
		}
		default:
		{
			return 85;
		}

		break;
		}
		return 85;
	}

}