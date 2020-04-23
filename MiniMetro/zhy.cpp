//#include "stdafx.h"
//#include <iostream>
//#include <windows.h>
//#include <time.h>
//#include <process.h>
//#include <graphics.h>
//
//using namespace std;
//
//typedef long long ll;
//const int starnum = 100;
//const int liuxinnum = 100;
//ll Time;
//HANDLE hmutex;
//void gettime()
//{
//	SYSTEMTIME st;
//	GetLocalTime(&st);
//	Time = st.wHour * 3600 + st.wMinute * 60 + st.wSecond;
//}
//
//ll Rand()
//{
//	ll mod = 1000000007;
//	Time = (Time * (ll)801319 + (ll)232323) % mod;
//	return Time;
//}
//
//class Mouth
//{
//public:
//	Mouth(int x, int y)
//	{
//		this->x = x;
//		this->y = y;
//	}
//	static unsigned __stdcall move(void* p)
//	{
//		MOUSEMSG m;
//		Mouth* pi = (Mouth*)p;
//		while (true)
//		{
//			WaitForSingleObject(hmutex, INFINITE);
//			if (MouseHit() == true)
//			{
//				m = GetMouseMsg();
//				if (m.mkLButton == true)
//				{
//					pi->x = m.x;
//					pi->y = m.y;
//				}
//				else pi->x = -1;
//			}
//
//			ReleaseMutex(hmutex);
//			Sleep(1);
//		}
//	}
//	int getx()
//	{
//		return x;
//	}
//	int gety()
//	{
//		return y;
//	}
//private:
//	int x;
//	int y;
//};
//Mouth* mouth;
//class Star
//{
//public:
//	friend class Liuxin;
//	Star(int x, int y, bool vis)
//	{
//		r = Rand() % 4 + 1;
//		this->x = x;
//		this->y = y;
//		this->vis = vis;
//		this->dx = Rand() % 5 + 1;
//		this->dy = Rand() % 5 + 1;
//		ll k = Rand();
//		if (k % 4 == 0)
//		{
//			this->dx = -this->dx;
//			this->dy = -this->dy;
//		}
//		else if (k % 4 == 1) this->dx = -this->dx;
//		else if (k % 4 == 2) this->dy = -this->dy;
//	}
//	static unsigned __stdcall changdxdy(void* p)
//	{
//		Star* pi = (Star*)p;
//		if (pi->vis == false) return 0;
//		while (true)
//		{
//			WaitForSingleObject(hmutex, INFINITE);
//			if (pi == NULL || pi->vis == false) return 0;
//			else
//			{
//				pi->dx = Rand() % 5 - 2;
//				pi->dy = Rand() % 5 - 2;
//				if (pi->dx == 0 && pi->dy == 0) pi->dx = 1;
//			}
//			ReleaseMutex(hmutex);
//			Sleep(1000);
//		}
//		return 0;
//	}
//	static unsigned __stdcall movei(void* p)
//	{
//		Star* pi = (Star*)p;
//		while (true)
//		{
//			WaitForSingleObject(hmutex, INFINITE);
//			if (pi->vis == false) return 0;
//			pi->x += pi->dx;
//			pi->y += pi->dy;
//			bool flag = false;
//			if (pi->x >= 800) flag = true;
//			else if (pi->x <= 0) flag = true;
//			else if (pi->y >= 600) flag = true;
//			else if (pi->y <= 0) flag = true;
//			ReleaseMutex(hmutex);
//			if (flag == true)
//			{
//				pi->vis = false;
//				return 0;
//			}
//
//			Sleep(30);
//		}
//		return 0;
//	}
//	int getx()
//	{
//		return x;
//	}
//	int gety()
//	{
//		return y;
//	}
//	bool getvis()
//	{
//		return vis;
//	}
//	int getr()
//	{
//		return r;
//	}
//private:
//	int x;
//	int y;
//	bool vis;
//	int dx;
//	int dy;
//	int id;
//	int r;
//};
//Star* star[starnum];
//class Liuxin
//{
//public:
//	Liuxin(int dx, int dy)
//	{
//		this->speed = max(Rand() % 150 + 150, Rand() % 150 + 120);
//		this->x = 0;
//		this->y = Rand() % 500 + 1.0;
//		this->vis = true;
//		this->dx = dx / (speed * 1.0);
//		this->dy = (dy - this->y) / (speed * 1.0);
//	}
//	static unsigned __stdcall move(void* p)
//	{
//		Liuxin* pi = (Liuxin*)p;
//		while (true)
//		{
//			pi->x += pi->dx;
//			pi->y += pi->dy;
//			if (pi->x >= 800 || pi->y >= 600)
//			{
//				pi->vis = false;
//				return 0;
//			}
//			for (int i = 0; i < starnum; i++)
//			{
//				if (star[i] != NULL && star[i]->getvis() == true)
//				{
//					int x = star[i]->getx();
//					int y = star[i]->gety();
//					double dis = (pi->x - x) * (pi->x - x) + (pi->y - y) * (pi->y - y);
//					if (dis < 9)
//					{
//						pi->vis = false;
//						star[i]->vis = false;
//						return 0;
//					}
//				}
//			}
//			Sleep(5);
//		}
//	}
//	bool getvis()
//	{
//		return vis;
//	}
//	double getx()
//	{
//		return x;
//	}
//	double gety()
//	{
//		return y;
//	}
//	double getdx()
//	{
//		return dx;
//	}
//	double getdy()
//	{
//		return dy;
//	}
//private:
//	double x;
//	double y;
//	double dx;
//	double dy;
//	bool vis;
//	int speed;
//};
//Liuxin* liuxin[liuxinnum];
//
//
//
//static unsigned __stdcall buildliuxin(void* p)
//{
//	Mouth* pi = (Mouth*)p;
//	HANDLE h[liuxinnum];
//
//	for (int i = 0; i < liuxinnum; i++) liuxin[i] = NULL;
//	while (true)
//	{
//		if (pi->getx() != -1)
//		{
//			WaitForSingleObject(hmutex, INFINITE);
//			for (int i = 0; i < liuxinnum; i++)
//			{
//				if (liuxin[i] == NULL)
//				{
//					liuxin[i] = new Liuxin(pi->getx(), pi->gety());
//					h[i] = (HANDLE)_beginthreadex(NULL, NULL, Liuxin::move, liuxin[i], NULL, NULL);
//					CloseHandle(h[i]);
//					break;
//				}
//				else
//				{
//					if (liuxin[i]->getvis() == false)
//					{
//						delete liuxin[i];
//						liuxin[i] = new Liuxin(pi->getx(), pi->gety());
//						h[i] = (HANDLE)_beginthreadex(NULL, NULL, Liuxin::move, liuxin[i], NULL, NULL);
//						CloseHandle(h[i]);
//						break;
//					}
//					else;
//				}
//			}
//			ReleaseMutex(hmutex);
//			Sleep(50);
//		}
//		Sleep(1);
//	}
//}
//static unsigned  __stdcall buildstar(void* lp)
//{
//	HANDLE threadi[starnum];
//	while (true)
//	{
//		for (int i = 0; i < starnum; i++)
//		{
//			WaitForSingleObject(hmutex, INFINITE);
//			if (star[i] == NULL)
//			{
//				star[i] = new Star(Rand() % 800, Rand() % 600, true);
//				threadi[i] = (HANDLE)_beginthreadex(NULL, NULL, Star::movei, star[i], NULL, NULL);
//				CloseHandle(threadi[i]);
//				threadi[i] = (HANDLE)_beginthreadex(NULL, NULL, Star::changdxdy, star[i], NULL, NULL);
//				CloseHandle(threadi[i]);
//			}
//			else
//			{
//				if (star[i]->getvis() == true);
//				else
//				{
//					delete star[i];
//					star[i] = NULL;
//					star[i] = new Star(Rand() % 800, Rand() % 600, true);
//					threadi[i] = (HANDLE)_beginthreadex(NULL, NULL, Star::movei, star[i], NULL, NULL);
//					CloseHandle(threadi[i]);
//					threadi[i] = (HANDLE)_beginthreadex(NULL, NULL, Star::changdxdy, star[i], NULL, NULL);
//					CloseHandle(threadi[i]);
//				}
//			}
//			ReleaseMutex(hmutex);
//			Sleep(100);
//		}
//	}
//	return 0;
//}
//
//void init(IMAGE* p)
//{
//	initgraph(1000, 600);
//	loadimage(p, _T("picture\\star.jpg"), 800, 600);
//	gettime();
//	for (int i = 0; i < 100; i++) star[i] = NULL;
//	hmutex = CreateMutex(NULL, FALSE, _T("c++"));
//	mouth = new Mouth(0, 0);
//	HANDLE H = (HANDLE)_beginthreadex(NULL, NULL, Mouth::move, mouth, NULL, NULL);
//	CloseHandle(H);
//	
//	HANDLE h = (HANDLE)_beginthreadex(NULL, NULL, buildstar, NULL, NULL, NULL);
//	CloseHandle(h);
//	HANDLE HH = (HANDLE)_beginthreadex(NULL, NULL, buildliuxin, mouth, NULL, NULL);
//	CloseHandle(HH);
//}
//int main()
//{
//
//
//	IMAGE img;
//	init(&img);
//	BeginBatchDraw();
//	while (true)
//	{
//		WaitForSingleObject(hmutex, INFINITE);
//		putimage(0, 0, &img);
//		for (int i = 0; i < starnum; i++)
//		{
//			if (star[i] == NULL || star[i]->getvis() == false);
//			else
//			{
//				if (i % 6 == 0) setfillcolor(RGB(126, 184, 230));
//				else if (i % 6 == 1) setfillcolor(RGB(255, 255, 255));
//				else if (i % 6 == 2) setfillcolor(RGB(0, 191, 255));
//				else if (i % 6 == 3) setfillcolor(RGB(236, 93, 0));
//				else if (i % 6 == 4) setfillcolor(RGB(255, 222, 24));
//				else if (i % 6 == 5) setfillcolor(RGB(238, 0, 6));
//				int k = Rand() % 4 + 1;
//				solidcircle(star[i]->getx(), star[i]->gety(), 3);
//			}
//		}
//		for (int i = 0; i < liuxinnum; i++)
//		{
//			if (liuxin[i] != NULL && liuxin[i]->getvis() == true)
//			{
//				double x = liuxin[i]->getx();
//				double y = liuxin[i]->gety();
//				double dx = liuxin[i]->getdx();
//				double dy = liuxin[i]->getdy();
//				setlinecolor(RGB(0, 170, 250));
//				line((int)x, (int)y, (int)(x - dx * 4), (int)(y - dy * 4));
//			}
//		}
//
//		FlushBatchDraw();
//		ReleaseMutex(hmutex);
//		Sleep(10);
//		cleardevice();
//
//	}
//	EndBatchDraw();
//	for (int i = 0; i < 100; i++)
//	{
//		if (star[i] != NULL)
//		{
//			delete star[i];
//			star[i] = NULL;
//		}
//	}
//	return 0;
//}