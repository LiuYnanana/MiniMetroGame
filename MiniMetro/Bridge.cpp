#include "Bridge.h"

Bridge::Bridge() {
	myLoger = MyLogger::GetInstance();
}

void Bridge::DrawBridge() {
	LOG4CPLUS_DEBUG(myLoger->rootLog, "start draw bridge");
	setcolor(BLACK);
	setfillcolor(WHITE);
	fillcircle(x, y, r); 
	line(18, 466, 62, 466);
	line(18, 466, 18, 493);
	line(62, 466, 62, 493);
	line(18, 464, 62, 464);
	fillpie(26, 471, 54, 511, 0, 66);
	setlinecolor(WHITE);
	line(26, 492, 54, 492);
	line(26, 491, 54, 491);
	setcolor(BLACK);
	fillcircle(22, 483, 2);
	fillcircle(26, 474, 3);
	fillcircle(58, 483, 2);
	fillcircle(54, 474, 3);
	setlinecolor(BLACK);
	line(18, 466, 18, 461);
	line(62, 466, 62, 461);
	line(29, 466, 29, 461);
	line(51, 466, 51, 461);
	line(40, 466, 40, 461);
	LOG4CPLUS_DEBUG(myLoger->rootLog, "bridge is successfully drawn");
}

Bridge::~Bridge() {}