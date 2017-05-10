// simulationsys.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>
#include "user.h"
#include "uav.h"
#include "node.h"
#include "time.h"

using namespace std;
bool move(float lon1, float lat1, float lon2, float lat2, vector<Node> &allnode, vector<Node> &rodenode);



int main()
{
	/*
		user u1;
		uav u2;
		int id = 2;
		u2.set_sno(id);
		cout << "hello" << u2.get_sno() << endl;
		*/
		//cout.setf(ios_base::basefield, ios_base::doublefield);
	string filename, nodeinfo_temp;
	int count = 0;

	filename = "map.osm";
	ifstream  infile;
	ofstream  outfile("nodeinfo.txt");
	infile.open(filename.c_str());
	if (!infile)
	{
		cerr << "打开文件失败" << endl;
		return -1;
	}

	Node node_temp;
	vector<Node> allnode;
	//int nullnodeinfo = 3;//地图数据中前三行不是节点数据。
//***************创建对象数组并且在读取的时候进行赋值***********************
	//识别并提取特定字符串
	while (getline(infile, nodeinfo_temp))
	{
		//识别id
		size_t f1 = nodeinfo_temp.find("<node id=\"", 0);
		size_t f2 = nodeinfo_temp.find("\"", f1 + 10);

		string  node_id;

		//提取id，并且进行下一步
		while (f1 != nodeinfo_temp.npos)
		{
			node_id = nodeinfo_temp.substr(f1 + 10, f2 - f1 - 10);
			outfile << node_id << " ";
			node_temp.set_id(node_id);
			f1 = nodeinfo_temp.find("<node id=\"", f2 + 1);
			f2 = nodeinfo_temp.find("\"", f1 + 10);
		}

		//识别lat
		size_t f3 = nodeinfo_temp.find("\" lat=\"", 0);
		size_t f4 = nodeinfo_temp.find("\" lon=\"", f3 + 7);


		string node_lat;
		double node_lat_f;

		while (f3 != nodeinfo_temp.npos)
		{
			node_lat = nodeinfo_temp.substr(f3 + 7, f4 - f3 - 7);
			outfile << node_lat << " ";
			node_lat_f = atof(node_lat.c_str());
			node_temp.set_lat(node_lat_f); //string转double
			f3 = nodeinfo_temp.find("\" lat=\"", f4 + 1);
			f4 = nodeinfo_temp.find("\" lon=\"", f3 + 7);
		}

		//识别lon
		size_t f5 = nodeinfo_temp.find("\" lon=\"", 0);
		size_t f6 = nodeinfo_temp.find("\"/>", f5 + 7);

		string node_lon;
		double node_lon_f;

		while (f5 != nodeinfo_temp.npos)
		{
			node_lon = nodeinfo_temp.substr(f5 + 7, f6 - f5 - 7);
			outfile << node_lon << endl;
			node_lon_f = atof(node_lon.c_str());
			node_temp.set_lon(node_lon_f); //string转double
			f5 = nodeinfo_temp.find("\" lon=\"", f6 + 1);
			f6 = nodeinfo_temp.find("\"/>", f5 + 7);
		}
		//控制掉前三行的非节点数据。
		if (node_id != "")
		{
			allnode.push_back(node_temp);
		}


	}

	////格式化输出坐标点
	//for (int i = 0; i < allnode.size(); i++)
	//{
	//	cout << allnode[i].get_id() << "    ";
	//	cout << fixed << setprecision(7) << allnode[i].get_lat() << "    ";
	//	cout << allnode[i].get_lon() << endl;//<< setprecision(7) 
	//}

	//************************生成用户以及分配目的地********************
	int user_num = 0;
	cout << "输入工作者数量" << endl;
	cin >> user_num;

	User* p_user = new User[user_num];
	Node* p_dest = new Node[user_num];//每个用户的目的地。
	srand((unsigned)time(0));//跟随系统的随机数。
	int node_index;
	for (int i = 0; i < user_num; i++)
	{
		node_index = rand() % allnode.size();
		p_user[i].set_sno(i + 1);
		p_user[i].set_lat(allnode[node_index].get_lat());
		p_user[i].set_lon(allnode[node_index].get_lon());
		p_user[i].show();

		node_index = rand() % allnode.size();
		p_dest[i].set_id(allnode[node_index].get_id());
		p_dest[i].set_lat(allnode[node_index].get_lat());
		p_dest[i].set_lon(allnode[node_index].get_lon());
	}

	//**************用户坐标点根据路网坐标点，向目的地进行坐标移动。*************
		//p_user[0].get_lat





	return 0;
}
//##############需要处理的问题，在合适的地方结束方法。
//在调用函数之前传入空容器rode_node，
//温习一下参数 & 和 * 的区别
bool move(float lon1, float lat1, float lon2, float lat2, vector<Node> &allnode, vector<Node> &rodenode)
{
	//vector<Node>::iterator it = allnode.begin();
	double distance = sqrt(pow(abs(lon1 - lon2), 2.0) + pow(abs(lat1 - lat2), 2.0));
	float temp_lat = lat1;
	float temp_lon = lon1;
	Node node_temp;
	//it 是一个地址  
	//下面四个判断分别对应目标点在用户的四个象限
	if ((lon2 - lon1 >= 0) && (lat2 - lat1 > 0))
	{
		for (int i = 0; i < allnode.size(); i++)
		{
			if ((allnode[i].get_lat() > lat1) && (allnode[i].get_lat() < lat2)
				&& (allnode[i].get_lon() >= lon1) && (allnode[i].get_lon() <= lon2))
			{
				//计算矩形区域内，各点和用户的距离
				//寻找区域内，距离用户最近的标记点
				if (distance >= sqrt(pow(abs(lon1 - allnode[i].get_lon()), 2.0) + pow(abs(lat1 - allnode[i].get_lat()), 2.0)))
				{
					distance = sqrt(pow(abs(lon1 - allnode[i].get_lon()), 2.0) + pow(abs(lat1 - allnode[i].get_lat()), 2.0));
					temp_lon = allnode[i].get_lon();
					temp_lat = allnode[i].get_lat();
				}
				
			}
		}//如何判断已经找到最后一个的情况距离判断修改成为小于等于
		node_temp.set_lat(temp_lat);
		node_temp.set_lon(temp_lon);
		rodenode.push_back(node_temp);//将路径点记录到node_temp中
		move(temp_lon, temp_lat, lon2, lat2, allnode, rodenode);
	}
	else if ((lon2 - lon1 < 0) && (lat2 - lat1 >= 0))
	{

	}
	else if ((lon2 - lon1 <= 0) && (lat2 - lat1 < 0))
	{

	}
	else if ((lon2 - lon1 > 0) && (lat2 - lat1 <= 0))
	{

	}
	else if ((lon2 - lon1 == 0) && (lat2 - lat1 == 0))//到达目的地
	{

		return true;
	}
	return false;
}

