#include "Rank.h"

Rank::Rank()
{
}

bool Rank::cmp(rank_info a, rank_info b)
{
	return a.people > b.people;
}

void Rank::SaveRank(std::string list_name, int people, std::string time)
{
	Redis re;
	re.connect("127.0.0.1", 6379);
	std::string p = std::to_string(people);
	re.PushList(list_name, p + "  " + time);
}

void Rank::GetRank(std::string list_name) {
	Redis re;
	re.connect("127.0.0.1", 6379);
	std::vector<std::string> v = re.GetList(list_name);
	
	re_info.clear();
	for (int i = 0; i < v.size(); i++) {
		rank_info t;
		int k;
		t.people = 0;
		for (k = 0; k < v[i].size(); k++) {
			if (v[i][k] == ' ') break;
			t.people = t.people * 10 + v[i][k] - '0';
		}
		std::cout << "p " << t.people << std::endl;
		for (; k < v[i].size(); k++) {
			if (v[i][k] != ' ') break;
		}

		t.time = v[i].substr(k, v[i].size());

		re_info.push_back(t);
	}

	sort(re_info.begin(), re_info.end(), Rank::cmp);
}

bool Rank::JudgeExit(MOUSEMSG m) {
	//line(10, 15, 80, 30);
	if (m.x >= 10 && m.x <= 80 && m.y >= 15 && m.y <= 30)
		return true;
	return false;
}

void Rank::ExitRank() {
	while (true) {
		if (MouseHit() == true) {
			MOUSEMSG m = GetMouseMsg();
			if (m.mkLButton == true && JudgeExit(m)) {
				end = true;
				return;
			}
		}
	}
}

void Rank::DrawRank() {
	int x = 200, y = 200;
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(35, 0, _T("黑体"));

	TCHAR s[] = _T("名次");
	outtextxy(200, 100, s);
	TCHAR s1[] = _T("输送人数");
	outtextxy(400, 100, s1);
	TCHAR s2[] = _T("游戏时间");
	outtextxy(650, 100, s2);
	std::cout << "size " << re_info.size() << std::endl;

	TCHAR str[300];
	for (int i = 0; i < re_info.size(); i++) {
		std::cout << i << std::endl;
		settextcolor(BLACK);
		setbkmode(TRANSPARENT);
		settextstyle(35, 0, _T("黑体"));

		_stprintf(str, _T("%d"), i + 1);
		outtextxy(x, y, str);

		//TCHAR s1[10];
		_stprintf(str, _T("%d"), re_info[i].people);
		outtextxy(x + 200, y, str);
		
	//	TCHAR s3[100];
		_stprintf_s(str, MAX_PATH, _T("%S"), re_info[i].time.c_str());
		outtextxy(x + 450, y, str);

		y += 50;
	}
	rectangle(15, 20, 35, 30);
	line(15, 15, 15, 35);
	line(15, 15, 5, 25);
	line(15, 35, 5, 25);

	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	settextstyle(20, 0, _T("黑体"));

	TCHAR st[] = _T("退出");
	outtextxy(40, 15, st);

	//	line(10, 15, 80, 30);
}

Rank::~Rank()
{
}
