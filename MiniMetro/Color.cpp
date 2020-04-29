#include "Color.h"

COLORREF Color::get_color(int k) {
	switch (k)
	{
	case 0:
		return RGB(255, 182, 193);
	case 2:
		return RGB(220, 20, 60);
	case 4:
		return RGB(0, 0, 205);
	case 6:
		return RGB(0, 206, 209);
	case 8:
		return RGB(60, 179, 113);
	case 10:
		return RGB(255, 255, 0);
	case 12:
		return RGB(255, 127, 80);
	case 14:
		return RGB(255, 215, 0);
	case 16:
		return RGB(147, 112, 219);
	case 18:
		return RGB(47, 79, 79);
	case 20:
		return RGB(127, 255, 170);
	case 22:
		return RGB(175, 238, 238);
		break;
	default:
		break;
	}
}