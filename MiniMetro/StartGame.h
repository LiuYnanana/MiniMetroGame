#pragma once
#include <easyx.h>
#include <conio.h>
#include <iostream>
extern bool end;
class StartGame
{
public:
	StartGame();
	void DrawStartGame();
	bool JudgeStart(int, int);
	bool JudgeEnd(int, int);
	bool GetSelectGame();
	~StartGame();
};

