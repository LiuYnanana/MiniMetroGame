#pragma once
#include <string>
#include <algorithm>
#include <graphics.h>
#include <conio.h>
#include <easyx.h>
#include "Redis.h"
extern bool end;
class Rank
{
public:
	struct rank_info {
		int people;
		std::string time;
	};
	Rank();
	static bool cmp(rank_info, rank_info);
	void SaveRank(std::string, int, std::string);
	void GetRank(std::string);
	bool JudgeExit(MOUSEMSG);
	void ExitRank();
	void DrawRank();
	~Rank();
	
private:
	std::vector<Rank::rank_info> re_info;
};

