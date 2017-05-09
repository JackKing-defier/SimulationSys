// SimulationSys.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include "user.h"
#include "uav.h"
#include "node.h"

using namespace std;
//ʹ�ó�ʼ���б��ʼ������

int main()
{
	/*int user_num = 0;
	cout << "���빤��������" << endl;
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
	//cout.setf(ios_base::basefield, ios_base::doublefield);
	string fileName, nodeinfo_temp;
	int count = 0;

	fileName = "map.osm";
	ifstream  inFile;
	ofstream  outFile("NodeInfo.txt");
	inFile.open(fileName.c_str());
	if (!inFile)
	{
		cerr << "���ļ�ʧ��" << endl;
		return -1;
	}

	Node node_temp;
	vector<Node> allnode;
	//int nullNodeInfo = 3;//��ͼ������ǰ���в��ǽڵ����ݡ�
//***************�����������鲢���ڶ�ȡ��ʱ����и�ֵ***********************
	//ʶ����ȡ�ض��ַ���
	while (getline(inFile, nodeinfo_temp))
	{
		//ʶ��id
		size_t f1 = nodeinfo_temp.find("<node id=\"", 0);
		size_t f2 = nodeinfo_temp.find("\"", f1 + 10);
		
		string  node_id;

		//��ȡid�����ҽ�����һ��
		while (f1 != nodeinfo_temp.npos)
		{
			node_id = nodeinfo_temp.substr(f1 + 10, f2 - f1 - 10);
			outFile << node_id << " ";
			node_temp.set_id(node_id);
			f1 = nodeinfo_temp.find("<node id=\"", f2 + 1);
			f2 = nodeinfo_temp.find("\"", f1 + 10);
		}

		//ʶ��lat
		size_t f3 = nodeinfo_temp.find("\" lat=\"", 0);
		size_t f4 = nodeinfo_temp.find("\" lon=\"", f3 + 7);

		string node_lat;
		double node_lat_f;

		while (f3 != nodeinfo_temp.npos)
		{
			node_lat = nodeinfo_temp.substr(f3 + 7, f4 - f3 - 7);
			outFile << node_lat << " ";
			node_lat_f = atof(node_lat.c_str());
			node_temp.set_lat(node_lat_f); //stringתdouble
			f3 = nodeinfo_temp.find("\" lat=\"", f4 + 1);
			f4 = nodeinfo_temp.find("\" lon=\"", f3 + 7);
		}		

		//ʶ��lon
		size_t f5 = nodeinfo_temp.find("\" lon=\"", 0);
		size_t f6 = nodeinfo_temp.find("\"/>", f5 + 7);

		string node_lon;
		double node_lon_f;

		while (f5 != nodeinfo_temp.npos)
		{
			node_lon = nodeinfo_temp.substr(f5 + 7, f6 - f5 - 7);
			outFile << node_lon << endl;
			node_lon_f = atof(node_lon.c_str());
			node_temp.set_lat(node_lon_f); //stringתdouble
			f5 = nodeinfo_temp.find("\" lon=\"", f6 + 1);
			f6 = nodeinfo_temp.find("\"/>", f5 + 7);
		}
		//���Ƶ�ǰ���еķǽڵ����ݡ�
		if (node_id != "")
		{
			allnode.push_back(node_temp);
		}
		

	}
	for (int i = 0; i < allnode.size(); i++)
	{
		cout << allnode[i].get_id() << "    ";
		cout <<fixed << setprecision(7) << allnode[i].get_lat() << "    ";
		cout << allnode[i].get_lon() << endl;//<< setprecision(6) 
	}
	return 0;
}

