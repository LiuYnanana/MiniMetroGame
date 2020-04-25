#include "SubwayHead.h"


SubwayHead::SubwayHead() {
	myLoger = MyLogger::GetInstance();
}

void SubwayHead::DrawSubwayHead() {
	LOG4CPLUS_DEBUG(myLoger->rootLog, "start draw subwayHead");
	setcolor(BLACK);
	setfillcolor(WHITE);
	fillcircle(x, y, r);
	
	//setcolor(BLACK);
	fillroundrect(22, 376, 58, 419, 10, 10);
	fillcircle(40, 380, 2);
	fillrectangle(27, 384, 53, 402);
	fillellipse(42, 392, 51, 402);
	setlinecolor(BLACK);
	line(30, 391, 33, 388);
	line(29, 398, 40, 387);
	fillroundrect(35, 409, 45, 419, 3, 3);
	//setfillcolor(YELLOW);
	fillcircle(31, 413, 2);
	fillcircle(26, 408, 2);
	fillcircle(49, 413, 2);
	fillcircle(54, 408, 2);

	line(28, 419, 22, 426);
	line(52, 419, 57, 426);
	LOG4CPLUS_DEBUG(myLoger->rootLog, "subwayHead is successfully drawn");

}

SubwayHead::~SubwayHead() {}