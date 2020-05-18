#include <easyx.h>
#include <conio.h>
#include<string.h>
#include<sstream>
#include<iostream>
#include <iomanip>
#include<fstream>
#include<vector>
#include<regex>
#include<set>
#include<map>
#include<math.h>

#define PRINT
#define PRINT_ALL
#define START_LINE 1
#define END_LINE 6

using namespace std;

string itostring(int x);//数转string

string sstostring(stringstream ss);//ss转string

//站点结构
struct position
{
	int x;
	int y;
};

//站点数组
typedef vector<position> stops_vector;

//线路类
class LINE
{
public:
	LINE() {
		bool clockwise = true;
		int line_id = 0;
	}
	void add(stringstream &ss)
	{
		string temp;
		ss >> temp;
		if (clockwise == 0)
			clockwise = temp.find('C') == temp.npos ? 2 : 1;
		else if (clockwise == 1)
			clockwise = temp.find('R') == temp.npos ? 1 : 3;
		else if (clockwise == 2)
			clockwise = temp.find('C') == temp.npos ? 2 : 3;
		regex e("[0-9]*");
		smatch m;
		regex_search(temp, m, e);
		string temp1 = m.str();
		line_id = atoi(temp1.c_str());
		if (temp.find('C') == temp.npos)
			while (ss >> temp)
				elemr.push_back(atoi(temp.c_str()));
		else
			while (ss >> temp)
				elemc.push_back(atoi(temp.c_str()));
	}
public:
	vector<int> elemr;
	vector<int> elemc;
	int clockwise = 0;//0无，1C，2R，3CR
	int line_id;
};//线路类

//求两点间的距离
double distance(position A, position B);

//寻找某站点可以直通的其他站点
set<int> distinct_from_stop(LINE *, int, int);

//寻找可以直达某站点的其他站点
set<int> distinct_to_stop(LINE *, int, int);

//寻找每一条路线上的source-->des路径，并返回其中的最短路径
vector<int> find_minpath_inline(int source, int des, LINE *, int, stops_vector&);

//寻找某个点的最近点；为其自己或者最近的点
int find_nearest(int, LINE *,int,stops_vector&);
int find_nearest(position, LINE *, int, stops_vector&);

//计算路径长度
double compute_length(vector<int> &, stops_vector&);

//寻找最小转乘路线
vector<int> find_path_rec(int source, int des, LINE *, int, stops_vector&);

//寻找最短路径
vector<int> find_path_shortest(int source, int des, LINE *, int, stops_vector&, vector<map<int, double>> &);

//依据路径vector画线
int draw_line(vector<int>&, stops_vector&);

//初始画地图
void init_graph( LINE *, stops_vector&);

//构造有向图
void creat_graph(LINE *, int, stops_vector&, vector<map<int, double>> &);

//提供map中的比较函数
int cmp(const pair<int, double>& x, const pair<int, double>& y)
{
	return x.second < y.second;
}

//map排序
void sortMapByValue(map<int, double>& tMap, vector<pair<int,double> >& tVector)
{
	for (map<int, double>::iterator curr = tMap.begin(); curr != tMap.end(); curr++)
		tVector.push_back(make_pair(curr->first, curr->second));
	sort(tVector.begin(), tVector.end(), cmp);
}

int main()
{
	string stops_num;//站点数目
	string lines_num;//线路数目
	stringstream in;
	ifstream infile_stops;
	stops_vector stops;
	//读入stops.txt
	infile_stops.open("stops.txt");
	if (!infile_stops) {
		cout << "open failed!";
		exit(-1);
	}
	getline(infile_stops, stops_num);
	string buffer, buffer1;
	while (getline(infile_stops, buffer))   //按行读取,遇到换行符结束
	{
		in << buffer;
		int stop[2];
		in >> stop[0] >> stop[1];
		stops.push_back({ stop[0],stop[1] });
		in.clear();
		in.str("");
	}
	infile_stops.close();

	//读入lines.txt
	ifstream infile_lines("lines.txt");
	infile_stops.open("stops.txt");
	if (!infile_stops) {
		cout << "open failed!";
		exit(-1);
	}
	getline(infile_lines, lines_num);
	LINE * lines = new LINE[atoi(lines_num.c_str())];
	int lines_order = 0;
	while (getline(infile_lines, buffer))//按行读取,遇换行符结束
	{
		//判断什么时候转入下一个lines
		regex e("[0-9]*");
		string temp;
		smatch m;
		regex_search(buffer, m, e);
		temp = m.str();
		if (atoi(temp.c_str()) != lines_order + 1)
			lines_order++;
		in << buffer;
		lines[lines_order].add(in);
		in.clear();
		in.str("");
	}
	infile_lines.close();

	//构造有向图 首先需要用每个站点和相邻站点以及他们之间的距离  这里用map键值的方法实现
	vector<map<int, double>>dist(stops.size());//有向图键值 vector
	creat_graph(lines, atoi(lines_num.c_str()), stops, dist);
	
	//初始化图形
	init_graph(lines, stops);
	//算法部分,最少换乘
	position start_p, end_p;
	bool has_start_p = false, has_end_p = false;
	MOUSEMSG m;// 定义鼠标消息
	int initial_start_stop = 1;
	int start_stop = initial_start_stop;
	int initial_end_stop = 30;
	int end_stop = initial_end_stop;
	while (true)
	{
		m = GetMouseMsg();
		if (m.mkLButton)
		{
			has_start_p = true;
			start_p.x = m.x;
			start_p.y = m.y;
			solidcircle(m.x, m.y, 6);
		}
		else if (m.mkRButton) {
			has_end_p = true;
			end_p.x = m.x;
			end_p.y = m.y;
			solidcircle(m.x, m.y, 4);
		}
		if (has_start_p&&has_end_p)
		{
			//处理点不在上面
			start_stop = find_nearest(start_p, lines, atoi(lines_num.c_str()), stops);
			end_stop = find_nearest(end_p, lines, atoi(lines_num.c_str()), stops);
			//递归求解最小换乘;
			vector<int> path = find_path_rec(start_stop, end_stop, lines, atoi(lines_num.c_str()), stops);
			setlinestyle(PS_DASH | PS_ENDCAP_FLAT, 3);
			setlinecolor(YELLOW);
			settextstyle(10, 0, _T("宋体"));
			if (path.size() != 0)
			{
				draw_line(path, stops);
				line(start_p.x, start_p.y, stops[start_stop - 1].x, stops[start_stop - 1].y);
				line(stops[end_stop - 1].x, stops[end_stop - 1].y,end_p.x,end_p.y);
			}
			vector <int> ret = find_path_shortest(start_stop, end_stop, lines, atoi(lines_num.c_str()), stops, dist);
			setlinecolor(GREEN);
			if (ret.size() != 0)
			{
				draw_line(ret, stops);
				line(start_p.x, start_p.y, stops[start_stop - 1].x, stops[start_stop - 1].y);
				line(stops[end_stop - 1].x, stops[end_stop - 1].y, end_p.x, end_p.y);
			}

			if(!ret.size()&&!path.size())
				line(start_p.x, start_p.y, end_p.x, end_p.y);
			has_start_p = false;
			has_end_p = false;
			getchar();
			closegraph();
			init_graph(lines,stops);
		}
	}

}

string itostring(int x) {
	stringstream ss_temp;
	string s_temp;
	ss_temp << x;
	ss_temp >> s_temp;
	return s_temp;
}

string sstostring(stringstream ss) {
	string temp1, temp2;
	while (ss >> temp1)
		temp2 += temp1;
	return temp2;
}

set<int> distinct_from_stop(LINE *lines, int lines_num, int stop_order) {
	set<int> stop;
	set<int>::iterator itor;
	bool record_flag;//是否开始记录
	for (int i = 0; i < lines_num; i++)
	{
		if (lines[i].clockwise == 1) {
			record_flag = false;
			for (int j = 0; j < lines[i].elemc.size(); j++)
			{
				if (!record_flag&&stop_order == lines[i].elemc[j]) {
					record_flag = true;
				}
				if (record_flag == true&&stop_order!= lines[i].elemc[j]) {
					stop.insert(lines[i].elemc[j]);
				}
			}
		}

		else if (lines[i].clockwise == 2) {
			record_flag = false;
			for (int j = 0; j < lines[i].elemr.size(); j++)
			{
				if (!record_flag&&stop_order == lines[i].elemr[j]) {
					record_flag = true;
				}
				if (record_flag == true && stop_order != lines[i].elemr[j]) {
					stop.insert(lines[i].elemr[j]);
				}
			}
		}

		else if (lines[i].clockwise == 3) {
			record_flag = false;
			for (int j = 0; j < lines[i].elemc.size(); j++)
			{
				if (!record_flag&&stop_order == lines[i].elemc[j]) {
					record_flag = true;
				}
				if (record_flag == true && stop_order != lines[i].elemc[j]) {
					stop.insert(lines[i].elemc[j]);
				}
			}
			record_flag = false;
			for (int j = 0; j < lines[i].elemr.size(); j++)
			{
				if (!record_flag&&stop_order == lines[i].elemr[j]) {
					record_flag = true;
				}
				if (record_flag == true && stop_order != lines[i].elemr[j]) {
					stop.insert(lines[i].elemr[j]);
				}
			}
		}
	}
	return stop;
}

set<int> distinct_to_stop(LINE *lines, int lines_num, int stop_order) {
	set<int> stop;
	set<int>::iterator itor;
	bool record_flag = 0;//是否开始记录
	int final_index;//最后一次匹配到的结点
	for (int i = 0; i < lines_num; i++)
	{
		if (lines[i].clockwise == 1) {
			record_flag = false;
			final_index = 0;
			for (int j = 0; j < lines[i].elemc.size(); j++)
			{
				if (stop_order == lines[i].elemc[j]) {
					record_flag = true;
					final_index = j;
				}
			}
			for (int j = 0;j <final_index; j++) {
				if (!record_flag)
					break;
				else if(lines[i].elemc[j]!=stop_order)
					stop.insert(lines[i].elemc[j]);
			}
		}

		else if (lines[i].clockwise == 2) {
			record_flag = false;
			final_index = 0;
			for (int j = 0; j < lines[i].elemr.size(); j++)
			{
				if (stop_order == lines[i].elemr[j]) {
					record_flag = true;
					final_index = j;
				}
			}
			for (int j = 0; j < final_index; j++) {
				if (!record_flag)
					break;
				else if (lines[i].elemr[j] != stop_order)
					stop.insert(lines[i].elemr[j]);
			}
		}

		else if (lines[i].clockwise == 3) {
			record_flag = false;
			final_index = 0;
			for (int j = 0; j < lines[i].elemc.size(); j++)
			{
				if (stop_order == lines[i].elemc[j]) {
					record_flag = true;
					final_index = j;
				}
			}
			for (int j = 0; j < final_index; j++) {
				if (!record_flag)
					break;
				else if (lines[i].elemc[j] != stop_order)
					stop.insert(lines[i].elemc[j]);
			}
			record_flag = false;
			final_index = 0;
			for (int j = 0; j < lines[i].elemr.size(); j++)
			{
				if (stop_order == lines[i].elemr[j]) {
					record_flag = true;
					final_index = j;
				}
			}
			for (int j = 0; j < final_index; j++) {
				if (!record_flag)
					break;
				else if (lines[i].elemr[j] != stop_order)
					stop.insert(lines[i].elemr[j]);
			}
		}
	}
	return stop;
}

double distance(position A, position B) {
	return sqrt(pow(A.x-B.x,2)+pow(A.y-B.y,2));
}

vector<int> find_minpath_inline(int source, int des, LINE * lines, int lines_num, stops_vector & v) {
	vector<int> path, path_new;
	bool get_flag = false;
	int source_flag = -1;
	int des_flag = -1;
	string text;
	for (int i = 0; i < lines_num; i++) {
		if (lines[i].clockwise == 1) {
			source_flag = -1;
			des_flag = -1;
			path_new.clear();
			for (int j = 0; j < lines[i].elemc.size(); j++)
			{
				if (des_flag == -1 && source == lines[i].elemc[j]) {
					source_flag = j;
				}
				if (source_flag > -1 && des == lines[i].elemc[j]) {
					des_flag = j;
				}
			}
			if (source_flag > -1 && des_flag > -1)
			{
				for (int j = source_flag; j <= des_flag; j++)
				{
					if (get_flag == false)
						path.push_back(lines[i].elemc[j]);
					else
						path_new.push_back(lines[i].elemc[j]);
				}
				if (get_flag == false)
				{
					get_flag = true;
					path_new = path;
				}
				else
				{
					if (compute_length(path_new, v) < compute_length(path, v))
						path = path_new;
				}
			}
		}

		else if (lines[i].clockwise == 2) {
			source_flag = -1;
			des_flag = -1;
			path_new.clear();
			for (int j = 0; j < lines[i].elemr.size(); j++)
			{
				if (des_flag == -1 && source == lines[i].elemr[j]) {
					source_flag = j;
				}
				if (source_flag > -1 && des == lines[i].elemr[j]) {
					des_flag = j;
				}
			}
			if (source_flag > -1 && des_flag > -1)
			{
				for (int j = source_flag; j <= des_flag; j++)
				{
					if (get_flag == false)
						path.push_back(lines[i].elemr[j]);
					else
						path_new.push_back(lines[i].elemr[j]);
				}
				if (get_flag == false)
				{
					get_flag = true;
					path_new = path;
				}
				else
				{
					if (compute_length(path_new, v) < compute_length(path, v))
						path = path_new;
				}
			}
		}

		else if (lines[i].clockwise == 3) {
			source_flag = -1;
			des_flag = -1;
			path_new.clear();
			for (int j = 0; j < lines[i].elemc.size(); j++)
			{
				if (des_flag == -1 && source == lines[i].elemc[j]) {
					source_flag = j;
				}
				if (source_flag > -1 && des == lines[i].elemc[j]) {
					des_flag = j;
				}
			}
			if (source_flag > -1 && des_flag > -1)
			{
				for (int j = source_flag; j <= des_flag; j++)
				{
					if (get_flag == false)
						path.push_back(lines[i].elemc[j]);
					else
						path_new.push_back(lines[i].elemc[j]);
				}
				if (get_flag == false)
				{
					get_flag = true;
					path_new = path;
				}
				else
				{
					if (compute_length(path_new, v) < compute_length(path, v))
						path = path_new;
				}
			}


			source_flag = -1;
			des_flag = -1;
			path_new.clear();
			for (int j = 0; j < lines[i].elemr.size(); j++)
			{
				if (des_flag ==-1&& source == lines[i].elemr[j]) {
					source_flag = j;
				}
				if (source_flag > -1 && des == lines[i].elemr[j]) {
					des_flag = j;
				}
			}
			if (source_flag > -1 && des_flag > -1)
			{
				for (int j = source_flag; j <= des_flag; j++)
				{
					if (get_flag == false)
						path.push_back(lines[i].elemr[j]);
					else
						path_new.push_back(lines[i].elemr[j]);
				}
				if (get_flag == false)
				{
					get_flag = true;
					path_new = path;
				}
				else
				{
					if (compute_length(path_new, v) < compute_length(path, v))
						path = path_new;
				}
			}
		}
	}
	return path;
}

int draw_line(vector<int>& p, stops_vector& v) {
	if (p.size() == 0)
		return -1;
	for (int i = 0; i < p.size() - 1; i++)
	{
		line(v[p[i] - 1].x, v[p[i] - 1].y, v[p[i + 1] - 1].x, v[p[i + 1] - 1].y);
	}
	return 0;
}

double compute_length(vector<int> &v, stops_vector& s) {
	double ret = 0;
	for (int i = 0; i < v.size() - 1; i++)
		ret += distance(s[v[i + 1] - 1], s[v[i] - 1]);
		//ret += sqrt((pow(s[v[i + 1] - 1].x - s[v[i] - 1].x, 2) + (pow(s[v[i + 1] - 1].y - s[v[i] - 1].y, 2))));
	return ret;
}

int find_nearest(int n, LINE * lines,int lines_num,stops_vector& v){
	int ret = n;
	double length = 0;
	double temp = 66666;
	bool find_flag = false;
	for (int i = 0; i < lines_num; i++) {
		for (int j = 0; j < lines[i].elemc.size(); j++)
		{
			if (!find_flag)
			{
				length = distance(v[n - 1], v[lines[i].elemc[j] - 1]);
				ret = lines[i].elemc[j];
				find_flag = true;
			}
			else
			{
				temp = distance(v[n - 1], v[lines[i].elemc[j] - 1]);
			}
			if (temp < length)
			{
				ret = lines[i].elemc[j];
				length = temp;
			}
		}
		for (int j = 0; j < lines[i].elemr.size(); j++)
		{
			if (!find_flag)
			{
				length = distance(v[n - 1], v[lines[i].elemr[j] - 1]);
				find_flag = true;
				ret = lines[i].elemr[j];
			}
			else {
				temp = distance(v[n - 1], v[lines[i].elemr[j] - 1]);
			}
				if (temp < length)
			{
				ret = lines[i].elemr[j];
				length = temp;
			}
		}
	}
	return ret;
}

int find_nearest(position p, LINE * lines, int lines_num, stops_vector& v) {
	int ret = 0;
	double length = 0;
	double temp = 66666;
	bool find_flag = false;
	for (int i = 0; i < lines_num; i++) {
		for (int j = 0; j < lines[i].elemc.size(); j++)
		{
			if (!find_flag)
			{
				length = distance(p, v[lines[i].elemc[j] - 1]);
				ret = lines[i].elemc[j];
				find_flag = true;
			}
			else
			{
				temp = distance(p, v[lines[i].elemc[j] - 1]);
			}
			if (temp < length)
			{
				ret = lines[i].elemc[j];
				length = temp;
			}
		}
		for (int j = 0; j < lines[i].elemr.size(); j++)
		{
			if (!find_flag)
			{
				length = distance(p, v[lines[i].elemr[j] - 1]);
				find_flag = true;
				ret = lines[i].elemr[j];
			}
			else {
				temp = distance(p, v[lines[i].elemr[j] - 1]);
			}
			if (temp < length)
			{
				ret = lines[i].elemr[j];
				length = temp;
			}
		}
	}
	return ret;
}

vector<int> find_path_rec(int start_stop, int end_stop, LINE * lines, int lines_num, stops_vector & stops) {
	//0次换乘;
	vector<int> path, path1;
	path = find_minpath_inline(start_stop, end_stop, lines, lines_num, stops);
	if (path.size() > 0)
		return path;
	//有换乘
	set<int> start_distinct = distinct_from_stop(lines, lines_num, start_stop);
	set<int> end_distinct = distinct_to_stop(lines, lines_num, end_stop);
	if (start_distinct.size() == 0 || end_distinct.size() == 0)
	{
		path.clear();
		return path;
	}
	set<int> common;
	set_intersection(start_distinct.begin(), start_distinct.end(), end_distinct.begin(), end_distinct.end(), inserter(common, common.begin()));
	double  length = 0, temp = 0;
	vector<vector<int>> path_arry, path_arry1;
	if (common.size() > 0) {
		for (set<int>::iterator itor = common.begin(); itor != common.end(); itor++)
			path_arry.push_back(find_minpath_inline(start_stop, *itor, lines, lines_num, stops));
		for (set<int>::iterator itor = common.begin(); itor != common.end(); itor++)
			path_arry1.push_back(find_minpath_inline(*itor, end_stop, lines, lines_num, stops));

		vector<int> path_pre;
		path = path_arry[0];
		path1 = path_arry1[0];
		length = compute_length(path_arry[0], stops) + compute_length(path_arry1[0], stops);
		for (int i = 1; i < path_arry.size(); i++) {
			temp = compute_length(path_arry[i], stops) + compute_length(path_arry1[i], stops);
			if (temp < length) {
				length = temp;
				path = path_arry[i];
				path1 = path_arry1[i];
			}
		}
		vector<int> path_ret;
		path_ret.insert(path_ret.end(), path.begin(), path.end()-1);
		path_ret.insert(path_ret.end(), path1.begin(), path1.end());
		if (path_ret.size() != 0)
			return path_ret;
		path_ret.clear();
		return path_ret;
	}
	else {
		vector<set<int>> vector_start_distinct;
		for(set<int>::iterator itor = start_distinct.begin(); itor != start_distinct.end(); itor++)
			vector_start_distinct.push_back(distinct_from_stop(lines, lines_num , *itor));
		set<int> start_distinct_temp = vector_start_distinct[0];//求并集
		set<int> set_temp;
		for (int i = 1; i < vector_start_distinct.size(); i++)
		{
			set_union(start_distinct_temp.begin(), start_distinct_temp.end(), vector_start_distinct[i].begin(), vector_start_distinct[i].end(), inserter(set_temp, set_temp.begin()));
			start_distinct_temp = set_temp;
		}
		set<int> start_distinct_new;//求差集
		set_difference(start_distinct_temp.begin(), start_distinct_temp.end(), start_distinct.begin(), start_distinct.end(), inserter(start_distinct_new, start_distinct_new.begin()));
		set<int> common_new;//求交集
		set_intersection(start_distinct_new.begin(), start_distinct_new.end(), end_distinct.begin(), end_distinct.end(), inserter(common_new, common_new.begin()));
		double  length = 0, temp = 0;
		vector<vector<int>> path_arry_new, path_arry1_new;
		if (common_new.size() > 0) {
			for (set<int>::iterator itor = common_new.begin(); itor != common_new.end(); itor++)
				path_arry_new.push_back(find_path_rec(start_stop, *itor, lines, lines_num, stops));
			for (set<int>::iterator itor = common_new.begin(); itor != common_new.end(); itor++)
				path_arry1_new.push_back(find_path_rec(*itor, end_stop, lines, lines_num, stops));
			vector<int> path_new = path_arry_new[0];
			vector<int> path1_new = path_arry1_new[0];
			vector<int> path_pre;
			length = compute_length(path_arry_new[0], stops) + compute_length(path_arry1_new[0], stops);
			for (int i = 1; i < path_arry_new.size(); i++) {
				path_pre = find_minpath_inline(start_stop, path_arry_new[i][0], lines, lines_num, stops);
				temp = compute_length(path_arry_new[i], stops) + compute_length(path_arry1_new[i], stops) + compute_length(path_pre, stops);
				if (temp < length) {
					length = temp;
					path = path_arry_new[i];
					path1 = path_arry1_new[i];
				}
			}
			vector<int> path_ret;
			path_ret.insert(path_ret.end(), path_pre.begin(), path_pre.end()-1);
			path_ret.insert(path_ret.end(), path_new.begin(), path_new.end()-1);
			path_ret.insert(path_ret.end(), path1_new.begin(), path1_new.end());
			if (path_ret.size() != 0)
				return path_ret;
			path_ret.clear();
			return path_ret;
		}
	}
}

vector<int> find_path_shortest(int start_stop, int end_stop, LINE * lines, int lines_num, stops_vector & stops,vector<map<int, double>> &dist){
	//采用Dijkstra算法求解最小路径
	//首先需要用每个站点和相邻站点以及他们之间的距离 构造有向图 ， 这里用map键值的方法实现
	vector<pair<int, double>> sort_dis;//记录排序后的dist
	map<int,double> dis = dist[start_stop - 1];//用来记录start_up到各个结点的距离（初始只有相邻结点）
	for (int i = 0; i < stops.size(); i++)
	{
		if (dis.count(i+1) == 0)
			dis.insert(pair<int, double>(i + 1, INFINITE));
	}
	dis[start_stop] = 0;
	map<int, double>::iterator itor;
	vector<int> parents_node(stops.size());//记录前驱结点
	set<int> visited = {start_stop};
	int min_dis_point;
	double min_dis;
	for (int i = 0; i < stops.size(); i++) {//确保所有的结点都可以被扩展到
		sort_dis.clear();
		sortMapByValue(dis, sort_dis);//对dis进行排序，寻找离当前结点最近的未访问过的点
		for (int j = 0; j < sort_dis.size(); j++)
			if (visited.find(sort_dis[j].first) == visited.end())//该节点未被访问过
			{
				min_dis_point = sort_dis[j].first;
				min_dis = sort_dis[j].second;
				visited.insert(sort_dis[j].first);
				break;
			}
		//更新相邻结点的开销
		if (sort_dis.size() > 0) {
			for (itor = dist[min_dis_point - 1].begin(); itor != dist[min_dis_point - 1].end(); itor++)
			{
				double temp = min_dis + (*itor).second;
				if (dis[(*itor).first] > temp)
				{
					dis[(*itor).first] = temp;
					parents_node[(*itor).first - 1] = min_dis_point;
				}
			}
		}
	}
	vector<int> ret = { end_stop };
	int temp = parents_node[end_stop-1];
	while (temp) {
		ret.insert(ret.begin(), temp);
		temp = parents_node[temp-1];
	}
	ret.insert(ret.begin(), start_stop);
	return ret;
}

void init_graph( LINE * lines, stops_vector& stops)
{
	// 初始化绘图窗口
	initgraph(800, 400);
	//setaspectratio(1.5, 1.5);
	setbkcolor(RGB(255, 250, 240));//设置背景颜色
	setfillcolor(BLACK);//设置填充颜色
	settextcolor(RED);//设置字体颜色
	setlinecolor(BLUE);//设置直线颜色
	settextstyle(13, 0, _T("宋体"));
	cleardevice();
	for (int i = 0; i < stops.size(); i++)
	{
		string s1 = itostring(stops[i].x);
		string s2 = itostring(stops[i].y);
		string s3 = itostring(i + 1);
		string s4 = s3 + ":(" + s1 + ',' + s2 + ')';
		solidcircle(stops[i].x, stops[i].y, 2);
		outtextxy(stops[i].x + 3, stops[i].y + 3, s3.c_str());
	}
	for (int i = START_LINE - 1; i < END_LINE; i++)
	{
		switch (lines[i].clockwise)
		{
		case 0: {
			break;
		}
		case 1: {;
			for (int j = 0; j < lines[i].elemc.size() - 1; j++)
			{
				if (j == 0) {
					setfillcolor(GREEN);//设置填充颜色
					solidcircle(stops[lines[i].elemc[j] - 1].x, stops[lines[i].elemc[j] - 1].y, 5);
				}
				if (j == lines[i].elemc.size() - 2) {
					setfillcolor(RED);//设置填充颜色
					solidrectangle(stops[lines[i].elemc[j + 1] - 1].x - 1, stops[lines[i].elemc[j + 1] - 1].y + 2, stops[lines[i].elemc[j + 1] - 1].x + 1, stops[lines[i].elemc[j + 1] - 1].y - 2);

				}
				setlinestyle(PS_SOLID | PS_ENDCAP_ROUND, 1);
				setlinecolor(RED);
				line(stops[lines[i].elemc[j] - 1].x, stops[lines[i].elemc[j] - 1].y, stops[lines[i].elemc[j + 1] - 1].x, stops[lines[i].elemc[j + 1] - 1].y);
			}
			break;
		}
		case 2: {
			for (int j = 0; j < lines[i].elemr.size() - 1; i++)
			{
				if (j == 0) {
					setfillcolor(GREEN);//设置填充颜色
					solidcircle(stops[lines[i].elemr[j] - 1].x, stops[lines[i].elemr[j] - 1].y, 5);
				}
				if (j == lines[i].elemr.size() - 2) {
					setfillcolor(RED);//设置填充颜色
					solidrectangle(stops[lines[i].elemr[j + 1] - 1].x - 1, stops[lines[i].elemr[j + 1] - 1].y + 2, stops[lines[i].elemr[j + 1] - 1].x + 1, stops[lines[i].elemr[j + 1] - 1].y - 2);

				}
				setlinecolor(BLUE);
				line(stops[lines[i].elemr[j] - 1].x, stops[lines[i].elemr[j] - 1].y, stops[lines[i].elemr[j + 1] - 1].x, stops[lines[i].elemr[j + 1] - 1].y);
			}
			break;
		}
		case 3: {
			for (int j = 0; j < lines[i].elemc.size() - 1; j++)
			{
				if (j == 0) {
					setfillcolor(GREEN);//设置填充颜色
					solidcircle(stops[lines[i].elemc[j] - 1].x, stops[lines[i].elemc[j] - 1].y, 5);
				}
				if (j == lines[i].elemc.size() - 2) {
					setfillcolor(RED);//设置填充颜色
					solidrectangle(stops[lines[i].elemc[j + 1] - 1].x - 1, stops[lines[i].elemc[j + 1] - 1].y + 2, stops[lines[i].elemc[j + 1] - 1].x + 1, stops[lines[i].elemc[j + 1] - 1].y - 2);

				}
				setlinecolor(RED);
				setlinestyle(PS_SOLID | PS_ENDCAP_ROUND, 1);

				line(stops[lines[i].elemc[j] - 1].x, stops[lines[i].elemc[j] - 1].y, stops[lines[i].elemc[j + 1] - 1].x, stops[lines[i].elemc[j + 1] - 1].y);
			}


			for (int j = 0; j < lines[i].elemr.size() - 1; j++)
			{
				if (j == 0) {
					setfillcolor(GREEN);//设置填充颜色
					solidcircle(stops[lines[i].elemr[j] - 1].x, stops[lines[i].elemr[j] - 1].y, 5);
				}
				if (j == lines[i].elemr.size() - 2) {
					setfillcolor(RED);//设置填充颜色
					solidrectangle(stops[lines[i].elemr[j + 1] - 1].x - 1, stops[lines[i].elemr[j + 1] - 1].y + 2, stops[lines[i].elemr[j + 1] - 1].x + 1, stops[lines[i].elemr[j + 1] - 1].y - 2);
				}
				DWORD a[4] = { 2, 3, 2, 3 };
				setlinecolor(BLUE);
				setlinestyle(PS_USERSTYLE | PS_ENDCAP_FLAT, 2, a, 4);
				line(stops[lines[i].elemr[j] - 1].x, stops[lines[i].elemr[j] - 1].y, stops[lines[i].elemr[j + 1] - 1].x, stops[lines[i].elemr[j + 1] - 1].y);
			}
			break;
		}

		default:
			break;
		}

	}

}

void creat_graph(LINE * lines, int lines_num, stops_vector & stops, vector<map<int, double>> &dist) {
	for (int i = 0; i < lines_num; i++)//构造有向图
	{
		if (lines[i].clockwise == 1) {
			for (int j = 0; j < lines[i].elemc.size() - 1; j++)
				dist[lines[i].elemc[j] - 1].insert(map<int, double>::value_type(lines[i].elemc[j + 1], distance(stops[lines[i].elemc[j] - 1], stops[lines[i].elemc[j + 1] - 1])));
		}
		else if (lines[i].clockwise == 2) {
			for (int j = 0; j < lines[i].elemr.size() - 1; j++)
				dist[lines[i].elemr[j] - 1].insert(map<int, double>::value_type(lines[i].elemr[j + 1], distance(stops[lines[i].elemr[j] - 1], stops[lines[i].elemr[j + 1] - 1])));
		}
		else if (lines[i].clockwise == 3) {
			for (int j = 0; j < lines[i].elemc.size() - 1; j++)
				dist[lines[i].elemc[j] - 1].insert(map<int, double>::value_type(lines[i].elemc[j + 1], distance(stops[lines[i].elemc[j] - 1], stops[lines[i].elemc[j + 1] - 1])));
			for (int j = 0; j < lines[i].elemr.size() - 1; j++)
				dist[lines[i].elemr[j] - 1].insert(map<int, double>::value_type(lines[i].elemr[j + 1], distance(stops[lines[i].elemr[j] - 1], stops[lines[i].elemr[j + 1] - 1])));
		}
	}
}
