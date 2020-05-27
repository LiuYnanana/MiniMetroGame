#include "Track.h"

Track::Track() {
	myLoger = MyLogger::GetInstance();
	used_track = 0;
	owned_track = 3;
}

void Track::DrawOneTrack(int x, int y)
{
	setcolor(BLACK);
	setfillcolor(WHITE);
	fillcircle(x, y, r);   
	line(x - 32, y, x + 22, y - 23);
	line(x - 22, y + 23, x + 32, y);

	line(x - 6, y - 11, x + 3, y + 11);
	line(x - 3, y - 12, x + 6, y + 10);

	line(x - 23, y - 4, x - 14, y + 19);
	line(x - 20, y - 5, x - 11, y + 18);

	line(x + 13, y - 18, x + 22, y + 4);
	line(x + 16, y - 19, x + 26, y + 3);
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

void Track::GetAllTrackInfo() {
	GetAllTrackColor();
	int ty = y;
	for (int i = 0; i < track_num; i++) {
		track_info.push_back(std::make_pair(std::make_pair(x, ty), 6));
		ty += 35;
	}
	for (int i = 0; i < track_num; i++) {
		track_info.push_back(std::make_pair(std::make_pair(x, ty), 6));
	//	setfillcolor(RGB(220, 220, 220));
	//	solidcircle(x, ty, 6);
		ty += 35;
	}
	LOG4CPLUS_INFO(myLoger->rootLog, "push track info into vector end..");
}

void Track::DrawTrackSelect() {
	for (int i = 0; i < track_num; i++) {
		if (i < owned_track) {
			setfillcolor(Color::get_color(track_color[i]));
			LOG4CPLUS_INFO(myLoger->rootLog, i << " < " <<owned_track);
		}
		else {
			setfillcolor(RGB(220, 220, 220));
		}
		int cx = track_info[i].first.first;
		int cy = track_info[i].first.second;
		int r = track_info[i].second;
		solidcircle(cx, cy, r);
	}

}

Track::~Track(){}