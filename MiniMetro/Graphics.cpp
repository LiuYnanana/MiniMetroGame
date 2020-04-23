#include "Graphics.h"

/*
	
	0：无边框的填充矩形 solidrectangle
	1：有边框的填充矩形 fillrectangle
	2：无边框的填充圆 solidcircle
	3：有边框的填充圆 fillcircle
	4：无边框的填充三角形 solidpolygon
	5：有边框的填充三角形 fillpolygon
	6：无边框的填充五角星 solidpentagram
	7：有边框的填充五角星 fillpentagram
	8：无边框的填充十字形 solidcrisscross
	9：有边框的填充十字形 fillcrisscross
	10：无边框的填充五边形 solidpolygon
	11：有边框的填充五边形 fillpolygon
	12：无边框的填充圆角矩形 solidroundrect
	13：有边框的填充圆角矩形 fillroundrect
	14：无边框的填充椭圆 solidellipse
	15：有边框的填充椭圆 fillellipse

*/
void Graphics::DrawGraphics(int k, std::vector<int> arg) {
	switch (k)
	{
		int x, y, r, left, top, right, bottom, st_angle, end_angle;
		int ellipse_width, ellipse_height;
		POINT p[10];

	case 0:
		left = arg[0];
		top = arg[1];
		right = arg[2];
		bottom = arg[3];
		solidrectangle(left, top, right, bottom);
		break;
	case 1:
		left = arg[0];
		top = arg[1];
		right = arg[2];
		bottom = arg[3];
		fillrectangle(left, top, right, bottom);
		break;
	case 2:
		x = arg[0];
		y = arg[1];
		r = arg[2];
		solidcircle(x, y, r);
		break;
	case 3:
		x = arg[0];
		y = arg[1];
		r = arg[2];
		fillcircle(x, y, r);
		break;
	case 4:
		p[0] = { arg[0], arg[1] };
		p[1] = { arg[2], arg[3] };
		p[2] = { arg[4], arg[5] };
		solidpolygon(p, 3);
		break;
	case 5:
		p[0] = { arg[0], arg[1] };
		p[1] = { arg[2], arg[3] };
		p[2] = { arg[4], arg[5] };
		fillpolygon(p, 3);
		break;
	case 6:
		p[0] = { arg[0], arg[1] };
		p[1] = { arg[2], arg[3] };
		p[2] = { arg[4], arg[5] };
		solidpolygon(p, 3);
		p[0] = { arg[6], arg[7] };
		p[1] = { arg[8], arg[9] };
		p[2] = { arg[10], arg[11] };
		solidpolygon(p, 3);
		break;
	case 7:
		p[0] = { arg[0], arg[1] };
		p[1] = { arg[2], arg[3] };
		p[2] = { arg[4], arg[5] };
		fillpolygon(p, 3);
		p[0] = { arg[6], arg[7] };
		p[1] = { arg[8], arg[9] };
		p[2] = { arg[10], arg[11] };
		fillpolygon(p, 3);
		setlinecolor(WHITE);
		y = (arg[1] + arg[9]) / 2;
		line(arg[0] - (arg[10] - arg[6]) / 6, y - (arg[9] - arg[1]) / 6 - 2,
			arg[0] + (arg[10] - arg[6]) / 6 - 1, y - (arg[9] - arg[1]) / 6 - 2);
		line(arg[0] - (arg[10] - arg[6]) / 3 + 1, y + (arg[9] - arg[1]) / 6,
			arg[0] - (arg[10] - arg[6]) / 6, y + (arg[9] - arg[1]) / 3 - 1);
		line(arg[0] + (arg[10] - arg[6]) / 3, y + (arg[9] - arg[1]) / 6 - 2,
			arg[0] + (arg[10] - arg[6]) / 6 - 1, y + (arg[9] - arg[1]) / 3 - 1);

		std::cout << arg[0] << " " << y << std::endl;
		std::cout << arg[0] - (arg[10] - arg[6]) / 6 << " " << y + (arg[9] - arg[1]) / 6
			<< " " << arg[0] - (arg[10] - arg[6]) / 6 << " " << y + (arg[9] - arg[1]) / 6 << std::endl;

		std::cout << arg[0] - (arg[10] - arg[6]) / 3 << " " << y + (arg[9] - arg[1]) / 6
			<< " " << arg[0] - (arg[10] - arg[6]) / 6 << " " << y + (arg[9] - arg[1]) / 3 << std::endl;

		std::cout << arg[0] + (arg[10] - arg[6]) / 3 << " " << y + (arg[9] - arg[1]) / 6
			<< " " << arg[0] + (arg[10] - arg[6]) / 6 << " " << y + (arg[9] - arg[1]) / 3 << std::endl;
		break;
	case 8:
		left = arg[0];
		top = arg[1];
		right = arg[2];
		bottom = arg[3];
		solidrectangle(left, top, right, bottom);
		solidrectangle(arg[4], arg[5], arg[6], arg[7]);
		break;
	case 9:
		left = arg[0];
		top = arg[1];
		right = arg[2];
		bottom = arg[3];
		fillrectangle(left, top, right, bottom);
		fillrectangle(arg[4], arg[5], arg[6], arg[7]);
		setlinecolor(WHITE);
		line(arg[4], top, arg[4], bottom);
		line(arg[6], top, arg[6], bottom);
		break;
	case 10:
		p[0] = { arg[0], arg[1] };
		p[1] = { arg[2], arg[3] };
		p[2] = { arg[4], arg[5] };
		p[3] = { arg[6], arg[7] };
		p[4] = { arg[8], arg[9] };
		solidpolygon(p, 5);
		break;
	case 11:
		p[0] = { arg[0], arg[1] };
		p[1] = { arg[2], arg[3] };
		p[2] = { arg[4], arg[5] };
		p[3] = { arg[6], arg[7] };
		p[4] = { arg[8], arg[9] };
		fillpolygon(p, 5);
		break;
	case 12:
		left = arg[0];
		top = arg[1];
		right = arg[2];
		bottom = arg[3];
		ellipse_width = arg[4];
		ellipse_height = arg[5];
		solidroundrect(left, top, right, bottom, ellipse_width, ellipse_height);
		break;
	case 13:
		left = arg[0];
		top = arg[1];
		right = arg[2];
		bottom = arg[3];
		ellipse_width = arg[4];
		ellipse_height = arg[5];
		fillroundrect(left, top, right, bottom, ellipse_width, ellipse_height);
		break;
	case 14:
		left = arg[0];
		top = arg[1];
		right = arg[2];
		bottom = arg[3];
		solidellipse(left, top, right, bottom);
		break;
	case 15:
		left = arg[0];
		top = arg[1];
		right = arg[2];
		bottom = arg[3];
		fillellipse(left, top, right, bottom);
		break;
	default:
		break;
	}
}

/*
int x1 = 20, x2 = 50;
int y1 = 20, y2 = 50;
for (int k = 0; k <= 360; k++) {
	if (k % 10 == 0) {
		x1 = 20;
		x2 = 50;
		y1 += 40;
		y2 += 40;
	}
	fillpie(x1, y1, x2, y2, 0, k);
	x1 += 40;
	x2 += 40;
}
*/
