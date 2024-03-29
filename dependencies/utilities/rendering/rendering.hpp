﻿#pragma once
#include "../../utilities/csgo.hpp"

enum font_flags {
	fontflag_none,
	fontflag_italic = 0x001,
	fontflag_underline = 0x002,
	fontflag_strikeout = 0x004,
	fontflag_symbol = 0x008,
	fontflag_antialias = 0x010,
	fontflag_gaussianblur = 0x020,
	fontflag_rotary = 0x040,
	fontflag_dropshadow = 0x080,
	fontflag_additive = 0x100,
	fontflag_outline = 0x200,
	fontflag_custom = 0x400,
	fontflag_bitmap = 0x800,
};

namespace rendering {
	void initialize();

	void cornered_rect(int x, int y, int w, int h, color colour);
	void line(int x1, int y1, int x2, int y2, color colour);
	void text(int x, int y, unsigned long font, std::string string, bool text_centered, color colour);
	void rect(int x, int y, int w, int h, color color);
	void filled_rect(int x, int y, int w, int h, color colour);
	void textured_polygon(int n, vertex_t* vertice, color col);
	void circle(int x, int y, int r, int s, color col);
	vec2_t get_text_size(unsigned long font, std::string text);

	namespace fonts {
		inline unsigned long watermark;
		inline unsigned long name;
		inline unsigned long visitor9;
		inline unsigned long esp;
	}
};