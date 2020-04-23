#pragma once
#include <vector>
#include <easyx.h>			
#include <conio.h>
#include <iostream>
class Graphics
{
public:
	static void DrawGraphics(int, std::vector<int> );

/*

	0：无边框的填充矩形 solidrectangle
	1：有边框的填充矩形 fillrectangle
	2：无边框的填充圆 solidcircle
	3：有边框的填充圆 fillcircle
	4: 无边框的填充三角形 solidpolygon
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
};

