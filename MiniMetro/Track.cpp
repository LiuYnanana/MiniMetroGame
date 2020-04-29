#include "Track.h"

Track::Track() {
	myLoger = MyLogger::GetInstance();
}

void Track::GetAllTrackColor() {
	LOG4CPLUS_DEBUG(myLoger->rootLog, "start srand track color...");
	srand(time(NULL));
	
	for (int i = 0; i < 20; i++) vis[i] = false;
	for (int i = 0; i < track_num; i++) {
		int t;
		do {
			t = (rand() % 12) *2;
			LOG4CPLUS_DEBUG(myLoger->rootLog, "color t is " << t);
		} while (vis[t] == true);
		LOG4CPLUS_DEBUG(myLoger->rootLog, "finally color t is " << t);
		vis[t] = true;
		track_color.push_back(t);
	}
	LOG4CPLUS_DEBUG(myLoger->rootLog, "all colors are ");

	for (int i = 0; i < track_num; i++) {
		LOG4CPLUS_INFO(myLoger->rootLog, track_color[i]);
	}
	LOG4CPLUS_INFO(myLoger->rootLog, "srand track color end...");

}

void Track::DrawTrackSelect() {
	GetAllTrackColor();
	int ty = y;
	for (int i = 0; i < 3; i++) {
		setfillcolor(Color::get_color(track_color[i]));
		solidcircle(x, ty, 6);
		ty += 35;
	}
	for (int i = 0; i < track_num; i++) {
		setfillcolor(RGB(220, 220, 220));
		solidcircle(x, ty, 6);
		ty += 35;
	}
}

Track::~Track(){}