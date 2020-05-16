#include "Route.h"

Route::Route(Map* _mp, Track* _track) {
	mp = _mp;
	p_track = _track;
	myLoger = MyLogger::GetInstance();
}

std::pair<int, int> Route::JudgeOnStation(int x, int y) {
	for (auto i : mp->sta_appear) {
		int _x = i.first;
		int _y = i.second;
		if ((x - _x) * (x - _x) + (y - _y) * (y - _y) <= 10 * 10) {
			return std::make_pair(_x, _y);
		}
	}
	return std::make_pair(-1, -1);
}

bool Route::JudgeOnEndpoint(int mx, int my, int x, int y) {
	if ((mx - x) * (mx - x) + (my - y) * (my - y) <= 5 * 5) {
		return true;
	} return false;
}

Route::route_point Route::GetRouteEndpoint(int sx, int sy, int ex, int ey) {
	LOG4CPLUS_INFO(myLoger->rootLog, "getRouteEndPoint" << sx << " "
		<< sy << " " << ex << " " << ey << ")");
	
	if (abs(ex - sx) <= 5) {
		double x1 = 1.0 * sx - 1;
		double y1 = 1.0 * (x1 - ex) * (sy - ey) / (sx - ex) + ey;

		double x2 = 1.0 * ex + 1;
		double y2 = 1.0 * (x2 - sx) * (sy - ey) / (sx - ex) + sy;

		return { (int)x1, (int)y1, (int)x2, (int)y2, (int)sx, (int)sy, (int)ex, (int)ey };
	}

	if (sx < ex) {
		double x1 = 1.0 * sx - 10;
		double y1 = 1.0 * (x1 - ex) * (sy - ey) / (sx - ex) + ey;

		double x2 = 1.0 * ex + 10;
		double y2 = 1.0 * (x2 - sx) * (sy - ey) / (sx - ex) + sy;

		LOG4CPLUS_INFO(myLoger->rootLog, "get route end point" << x1 << " "
			<< y1 << " " << x2 << " " << y2 << ") ("
			<< sx << " " << sy << " " << ex << " "
			<< ey << ") ");

		return { (int)x1, (int)y1, (int)x2, (int)y2, (int)sx, (int)sy, (int)ex, (int)ey };
	}

	double x1 = 1.0 * ex - 10;   //ex < sx   前端是sx  x1是和ex一起的
	double y1 = 1.0 * (x1 - sx) * (ey - sy) / (ex - sx) + sy;

	double x2 = 1.0 * sx + 10;
	double y2 = 1.0 * (x2 - ex) * (sy - ey) / (sx - ex) + ey;

	LOG4CPLUS_INFO(myLoger->rootLog, "get route end point" << x1 << " "
		<< y1 << " " << x2 << " " << y2 << ") ("
		<< sx << " " << sy << " " << ex << " "
		<< ey << ") ");

	return { (int)x2, (int)y2, (int)x1, (int)y1, (int)sx, (int)sy, (int)ex, (int)ey };
}

void Route::GetRouteInfo() {
	MOUSEMSG m;
	int sx = - 1, sy = -1;
	int flag = -1;
	int t_route_id;
	while (true) {
	//	mu_route.lock();
		m = GetMouseMsg();
		
		std::pair<int, int> t = JudgeOnStation(m.x, m.y); 
		if (t.first != -1) {       //鼠标命中站点
			if (m.uMsg == WM_LBUTTONDOWN) {
				LOG4CPLUS_INFO(myLoger->rootLog, "Mouse info" << m.x << " "
					<< m.y);
				sx = t.first;
				sy = t.second;
				flag = 1;
				LOG4CPLUS_DEBUG(myLoger->rootLog, "mouse left ok, flag = " << flag 
					<< "sx, sy " << sx << sy);
			}

			if (m.uMsg == WM_LBUTTONUP && sx != -1) {
				if (flag == 1) {
					if (p_track->used_track < p_track->owned_track) {
						LOG4CPLUS_DEBUG(myLoger->rootLog, "flag ");

						route_point t_route_point = GetRouteEndpoint(sx, sy, t.first, t.second);
						t_route_point.route_id = p_track->used_track;
						std::deque<route_point> t_q;
						t_q.push_back(t_route_point);
						route_info.push_back(t_q);
						p_track->track_info[p_track->used_track].second += 3;
						p_track->used_track++;
						

						sx = -1;
						sy = -1;
						LOG4CPLUS_INFO(myLoger->rootLog, "1 push route_info: (" << t_route_point.fsx << " "
							<< t_route_point.fsy << " " << t_route_point.fex << " " << t_route_point.fey << ") ("
							<< t_route_point.sx << " " << t_route_point.sy << " " << t_route_point.ex << " "
							<< t_route_point.ey << ") " << t_route_point.route_id);
					}
					else {
						// 线路不足 无法创建新的线路
					}
				}
				else if (flag == 2 || flag == 3) {    //连接一个endpoint  一个站点 
					
					if (flag == 2) { 
						route_point t_route_point = GetRouteEndpoint(t.first, t.second, sx, sy);
						t_route_point.route_id = t_route_id;

						t_route_point.fex = -1;
						t_route_point.fey = -1;
						route_info[t_route_id].front().fsx = -1;
						route_info[t_route_id].front().fsy = -1;
						route_info[t_route_id].push_front(t_route_point);
						LOG4CPLUS_INFO(myLoger->rootLog, "2 push route_info: (" << t_route_point.fsx << " "
							<< t_route_point.fsy << " " << t_route_point.fex << " " << t_route_point.fey << ") ("
							<< t_route_point.sx << " " << t_route_point.sy << " " << t_route_point.ex << " "
							<< t_route_point.ey << ") " << t_route_point.route_id);
					}
					else {
						route_point t_route_point = GetRouteEndpoint(sx, sy, t.first, t.second);
						t_route_point.route_id = t_route_id;
						t_route_point.fsx = -1;
						t_route_point.fsy = -1;

						route_info[t_route_id].back().fex = -1;
						route_info[t_route_id].back().fey = -1;
						route_info[t_route_id].push_back(t_route_point);
						LOG4CPLUS_INFO(myLoger->rootLog, "3 push route_info: (" << t_route_point.fsx << " "
							<< t_route_point.fsy << " " << t_route_point.fex << " " << t_route_point.fey << ") ("
							<< t_route_point.sx << " " << t_route_point.sy << " " << t_route_point.ex << " "
							<< t_route_point.ey << ") " << t_route_point.route_id);
					}
				}
				flag = -1;
				sx = -1;
				sy = -1;
				}
			}
		
		for (auto q_route : route_info) {
			route_point t_f = q_route.front();
			route_point t_b = q_route.back();

			if (t_f.fsx != -1 && JudgeOnEndpoint(m.x, m.y, t_f.fsx, t_f.fsy)) {
				if (m.uMsg == WM_LBUTTONDOWN) {

					sx = t_f.sx;
					sy = t_f.sy;
					flag = 2;
					t_route_id = t_f.route_id;
				}
			}

			if (t_b.fex != -1 && JudgeOnEndpoint(m.x, m.y, t_b.fex, t_b.fey)) {
				if (m.uMsg == WM_LBUTTONDOWN) {
					/*q_route.back().fex = -1;
					q_route.back().fey = -1;*/
					sx = t_b.ex;
					sy = t_b.ey;
					flag = 3;
					t_route_id = t_b.route_id;

					LOG4CPLUS_INFO(myLoger->rootLog, "3! " << sx << " " << sy << "; " <<
					m.x << " " << m.y << "; " << t_b.fex << " " << t_b.fey);
				}
			}
		}
		//mu_route.unlock();
		Sleep(50);
	}
} 

void Route::DrawRoute() {
	LOG4CPLUS_INFO(myLoger->rootLog, "route_info size: " << route_info.size());
	//mu_route.lock();
	for (auto t_route : route_info) {
		LOG4CPLUS_INFO(myLoger->rootLog, "--------------");
		for (std::deque<route_point> ::iterator it = t_route.begin();
			it != t_route.end(); it++) {
			setlinecolor(Color::get_color(p_track->track_color[it->route_id]));
			line(it->sx, it->sy, it->ex, it->ey);
			

			LOG4CPLUS_INFO(myLoger->rootLog, "Draw push route_info: (" << it->fsx << " "
				<< it->fsy << " " << it->fex << " " << it->fey << ") ("
				<< it->sx << " " << it->sy << " " << it->ex << " "
				<< it->ey << ") " << it->route_id);

			if (it->fsx != -1 && it->fsy != -1) {
				line(it->fsx, it->fsy, it->sx, it->sy);
				//LOG4CPLUS_INFO(myLoger->rootLog, "set color!");
				setfillcolor(Color::get_color(p_track->track_color[it->route_id]));
				//LOG4CPLUS_INFO(myLoger->rootLog, "set color!!");
				solidcircle(it->fsx, it->fsy, 2);
				//LOG4CPLUS_INFO(myLoger->rootLog, "set color!!!");
			}
			if (it->fex != -1 && it->fey != -1) {
				line(it->ex, it->ey, it->fex, it->fey);
				setfillcolor(Color::get_color(p_track->track_color[it->route_id]));
				solidcircle(it->fex, it->fey, 2);
			}
		}
	}
	//LOG4CPLUS_INFO(myLoger->rootLog, "!!!!route_info size: " << route_info.size());
	//mu_route.unlock();
}