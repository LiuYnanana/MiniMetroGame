#include "Route.h"

Route::Route(Map* _mp, Track* _track, Station* _station) {
	mp = _mp;
	p_track = _track;
	ptr_station = _station;
	myLoger = MyLogger::GetInstance();
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 100; j++) {
			for (int k = 0; k < 100; k++) {
				Edge_route[i][j][k] = false;
			}
		}
	}
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
	
	double dist;
	dist = 10;
	if (sx < ex) {
		if (ex - sx <= 5) dist = 1;
		double x1 = 1.0 * sx - dist;
		double y1 = 1.0 * (x1 - ex) * (sy - ey) / (sx - ex) + ey;

		double x2 = 1.0 * ex + dist;
		double y2 = 1.0 * (x2 - sx) * (sy - ey) / (sx - ex) + sy;

		return { (int)x1, (int)y1, (int)x2, (int)y2, (int)sx, (int)sy, (int)ex, (int)ey };
	}

	if (sx - ex <= 5) dist = 1;
	double x1 = 1.0 * ex - dist;   //ex < sx   前端是sx  x1是和ex一起的
	double y1 = 1.0 * (x1 - sx) * (ey - sy) / (ex - sx) + sy;

	double x2 = 1.0 * sx + dist;
	double y2 = 1.0 * (x2 - ex) * (sy - ey) / (sx - ex) + ey;

	return { (int)x2, (int)y2, (int)x1, (int)y1, (int)sx, (int)sy, (int)ex, (int)ey };
}

void Route::UpdateTrackInfo() {
	p_track->track_info[p_track->used_track].second += 3;
	p_track->used_track++;
}

int Route::GetStationId(int x, int y) {
	std::pair<int, int> t_pair = std::make_pair(x, y);
	point_list::iterator it = find_if(mp->sta_appear.begin(), mp->sta_appear.end(), 
		[t_pair](const std::pair<int, int> a) {
			return t_pair == a;});
	return it - mp->sta_appear.begin();
}

void Route::GetRouteStationInfo(int sx, int sy, int ex, int ey, route_point& t_route_point, int route_id) {
	t_route_point.route_id = route_id;
	t_route_point.station_sid = GetStationId(sx, sy);
	t_route_point.station_eid = GetStationId(ex, ey);

	mu_push_sta_id.lock();
	auto it1 = find(connect_sta_id.begin(), connect_sta_id.end(), t_route_point.station_sid);
	if (it1 == connect_sta_id.end()) connect_sta_id.push_back(t_route_point.station_sid);
	auto it2 = find(connect_sta_id.begin(), connect_sta_id.end(), t_route_point.station_eid);
	if (it2 == connect_sta_id.end()) connect_sta_id.push_back(t_route_point.station_eid);
	mu_push_sta_id.unlock();


	Edge_route[t_route_point.route_id][t_route_point.station_sid][t_route_point.station_eid] = true;
	Edge_route[t_route_point.route_id][t_route_point.station_eid][t_route_point.station_sid] = true;

	Next_station[t_route_point.route_id][t_route_point.station_sid][1] = t_route_point.station_eid;
	Next_station[t_route_point.route_id][t_route_point.station_eid][0] = t_route_point.station_sid;
}

void Route::ConnectStationToStation(int sx, int sy, int ex, int ey) {
	if (p_track->used_track < p_track->owned_track) {  // 线路充足
		
		route_point t_route_point = GetRouteEndpoint(sx, sy, ex, ey);
		GetRouteStationInfo(sx, sy, ex, ey, t_route_point, p_track->used_track);
		
		std::deque<route_point> t_q;
		t_q.push_back(t_route_point);
		route_info.push_back(t_q);

		UpdateTrackInfo();
		
		sx = -1;
		sy = -1;
		LOG4CPLUS_INFO(myLoger->rootLog, "1 push route_info: (" << t_route_point.fsx << " "
			<< t_route_point.fsy << " " << t_route_point.fex << " " << t_route_point.fey << ") ("
			<< t_route_point.sx << " " << t_route_point.sy << " " << t_route_point.ex << " "
			<< t_route_point.ey << ") " << t_route_point.route_id << " " << t_route_point.station_sid <<
			" " << t_route_point.station_eid);

	}
	else {
		// 线路不足 无法创建新的线路
	}
}

void Route::ConnectStationToRoute(int sx, int sy, int ex, int ey, int route_id) {
	
	route_point t_route_point = GetRouteEndpoint(sx, sy, ex, ey);
	GetRouteStationInfo(sx, sy, ex, ey, t_route_point, route_id);

	t_route_point.fex = -1;
	t_route_point.fey = -1;
	route_info[route_id].front().fsx = -1;
	route_info[route_id].front().fsy = -1;
	route_info[route_id].push_front(t_route_point);


	LOG4CPLUS_INFO(myLoger->rootLog, "2 push route_info: (" << t_route_point.fsx << " "
		<< t_route_point.fsy << " " << t_route_point.fex << " " << t_route_point.fey << ") ("
		<< t_route_point.sx << " " << t_route_point.sy << " " << t_route_point.ex << " "
		<< t_route_point.ey << ") " << t_route_point.route_id << t_route_point.station_sid <<
		" " << t_route_point.station_eid);
}


void Route::ConnectRouteToStation(int sx, int sy, int ex, int ey, int route_id) {
	route_point t_route_point = GetRouteEndpoint(sx, sy, ex, ey);
	GetRouteStationInfo(sx, sy, ex, ey, t_route_point, route_id);

	t_route_point.fsx = -1;
	t_route_point.fsy = -1;
	route_info[route_id].back().fex = -1;
	route_info[route_id].back().fey = -1;
	route_info[route_id].push_back(t_route_point);

	LOG4CPLUS_INFO(myLoger->rootLog, "3 push route_info: (" << t_route_point.fsx << " "
		<< t_route_point.fsy << " " << t_route_point.fex << " " << t_route_point.fey << ") ("
		<< t_route_point.sx << " " << t_route_point.sy << " " << t_route_point.ex << " "
		<< t_route_point.ey << ") " << t_route_point.route_id << " " << t_route_point.station_sid <<
		" " << t_route_point.station_eid);
	
}

void Route::StationDFS(int start, int station_id, int route,  bool is_first, bool front) {
	if (is_first) {
		int u = Next_station[route][station_id][front];
		int sta_shape = mp->v_station_shape[u];
		if (dfs_vis[u]) return;
		LOG4CPLUS_INFO(myLoger->rootLog, "next station id shape" << u << " "
			<< sta_shape);
		dfs_vis[u] = true;
		station_arrive[start][route][front][sta_shape]++;
		StationDFS(start, u, route, false, front);
		dfs_vis[u] = false;
	}
	else {
		for (int k = 0; k < p_track->used_track; k++) {
			for (int i = 0; i < connect_sta_id.size(); i++) {
				int u = connect_sta_id[i];
				if (Edge_route[k][station_id][u] && !dfs_vis[u]) {
					dfs_vis[u] = true;
					int sta_shape = mp->v_station_shape[u];
					station_arrive[start][route][front][sta_shape]++;
					StationDFS(start, u, k, false, front);
					dfs_vis[u] = false;
				}
			}
		}
		
	}
}

void Route::GetConnectionInfo() {
	mu_push_sta_id.lock();

	for (int k = 0; k < p_track->used_track; k++) {
		for (int i = 0; i < connect_sta_id.size(); i++) {
			LOG4CPLUS_INFO(myLoger->rootLog, "dfs i " << i);
			memset(dfs_vis, false, sizeof(dfs_vis));
			dfs_vis[connect_sta_id[i]] = true;
			StationDFS(connect_sta_id[i], connect_sta_id[i], k, true, true);
			memset(dfs_vis, false, sizeof(dfs_vis));
			dfs_vis[connect_sta_id[i]] = true;
			StationDFS(connect_sta_id[i], connect_sta_id[i], k, true, false);
		}
	}
	
	for (int i = 0; i < connect_sta_id.size(); i++) {
		for (int j = 0; j < p_track->used_track; j++) {
			for (auto m : station_arrive[connect_sta_id[i]][j][1]) {
				LOG4CPLUS_INFO(myLoger->rootLog, "1 dfs station_id " << connect_sta_id[i] << " "
					<< m.first << " " << m.second);
			}
			for (auto m : station_arrive[connect_sta_id[i]][j][0]) {
				LOG4CPLUS_INFO(myLoger->rootLog, "0 dfs station_id " << connect_sta_id[i] << " "
					<< m.first << " " << m.second);
			}
		}
	}

	mu_push_sta_id.unlock();
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
				sx = t.first;
				sy = t.second;
				flag = sta_to_sta;
			}

			if (m.uMsg == WM_LBUTTONUP && sx != -1 && sx != t.first) {
				if (flag == sta_to_sta) {
					ConnectStationToStation(sx, sy, t.first, t.second);
				}
			    if (flag == sta_to_route) {
					ConnectStationToRoute(t.first, t.second, sx, sy, t_route_id);
				}
				if (flag == route_to_sta) {
					ConnectRouteToStation(sx, sy, t.first, t.second, t_route_id);
				}
				GetConnectionInfo();
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
					flag = sta_to_route;
					t_route_id = t_f.route_id;
				}
			}

			if (t_b.fex != -1 && JudgeOnEndpoint(m.x, m.y, t_b.fex, t_b.fey)) {
				if (m.uMsg == WM_LBUTTONDOWN) {
					sx = t_b.ex;
					sy = t_b.ey;
					flag = route_to_sta;
					t_route_id = t_b.route_id;
				}
			}
		}
		//mu_route.unlock();
		Sleep(50);
	}
} 

void Route::DrawRoute() {
	//mu_route.lock();
	for (auto t_route : route_info) {
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
				setfillcolor(Color::get_color(p_track->track_color[it->route_id]));

				solidcircle(it->fsx, it->fsy, 2);
			}
			if (it->fex != -1 && it->fey != -1) {
				line(it->ex, it->ey, it->fex, it->fey);
				setfillcolor(Color::get_color(p_track->track_color[it->route_id]));
				solidcircle(it->fex, it->fey, 2);
			}
		}
	}
	//mu_route.unlock();
}