// SimulationSys.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include<fstream>
#include<string>
#include "user.h"
#include "uav.h"
#include "node.h"

using namespace std;
//使用初始化列表初始化对象

int main()
{
	/*int user_num = 0;
	cout << "输入工作者数量" << endl;
	cin >> user_num;

	User* p_user = new User[user_num];
	for (int i = 0; i < user_num; i++)
	{
		p_user[i].show();
	}*/


	/*
		User u1;
		Uav u2;
		int id = 2;
		u2.set_sno(id);
		cout << "hello" << u2.get_sno() << endl;
		*/

	string fileName, node_temp;
	//string word;  
	int count = 0;

	fileName = "map.osm";
	ifstream  inFile;
	ofstream  outFile("Fout.txt");
	inFile.open(fileName.c_str());
	if (!inFile)
	{
		cerr << "打开文件失败" << endl;
		return -1;
	}

	while (getline(inFile, node_temp))
	{
		//识别id
		size_t f1 = node_temp.find("<node id=\"", 0);
		size_t f2 = node_temp.find("\"", f1 + 10);
		
		string  node_id;

		//提取id，并且进行下一步
		while (f1 != node_temp.npos)
		{
			node_id = node_temp.substr(f1 + 10, f2 - f1 - 10);
			outFile << node_id << endl;
			f1 = node_temp.find("<node id=\"", f2 + 1);
			f2 = node_temp.find("\"", f1 + 10);
		}

		//识别lat
		size_t f3 = node_temp.find("\" lat=\"", 0);
		size_t f4 = node_temp.find("\" lon=\"", f3 + 7);

		string node_lat;

		while (f3 != node_temp.npos)
		{
			node_lat = node_temp.substr(f3 + 7, f4 - f3 - 7);
			outFile << node_lat << endl;
			f3 = node_temp.find("\" lat=\"", f4 + 1);
			f4 = node_temp.find("\" lon=\"", f3 + 7);
		}		

		//识别lon
		size_t f5 = node_temp.find("\" lon=\"", 0);
		size_t f6 = node_temp.find("\"/>", f5 + 7);

		string node_lon;

		while (f5 != node_temp.npos)
		{
			node_lon = node_temp.substr(f5 + 7, f6 - f5 - 7);
			outFile << node_lon << endl;
			f5 = node_temp.find("\" lon=\"", f6 + 1);
			f6 = node_temp.find("\"/>", f5 + 7);
		}
	}
	return 0;
}

