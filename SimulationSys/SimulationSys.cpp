// simulationsys.cpp : �������̨Ӧ�ó������ڵ㡣
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
bool moveUser(double lon1, double lat1, double lon2, double lat2, vector<Node> &allnode, vector<Node> &rodenode);



int main()
{
	//cout.setf(ios_base::basefield, ios_base::doublefield);
	string filename, nodeinfo_temp;
	int count = 0;

	filename = "map.osm";
	ifstream  infile;
	ofstream  outfile("nodeinfo.txt");
	infile.open(filename.c_str());
	if (!infile)
	{
		cerr << "���ļ�ʧ��" << endl;
		return -1;
	}

	Node node_temp;
	vector<Node> allnode;

//***************�����������鲢���ڶ�ȡ��ʱ����и�ֵ***********************
	//ʶ����ȡ�ض��ַ���
	while (getline(infile, nodeinfo_temp))
	{
		//ʶ��id
		size_t f1 = nodeinfo_temp.find("<node id=\"", 0);
		size_t f2 = nodeinfo_temp.find("\"", f1 + 10);

		string  node_id;

		//��ȡid�����ҽ�����һ��
		while (f1 != nodeinfo_temp.npos)
		{
			node_id = nodeinfo_temp.substr(f1 + 10, f2 - f1 - 10);
			outfile << node_id << " ";
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
			outfile << node_lat << " ";
			node_lat_f = atof(node_lat.c_str());
			node_temp.set_lat(node_lat_f); //stringתdouble
			f3 = nodeinfo_temp.find("\" lat=\"", f4 + 1);
			f4 = nodeinfo_temp.find("\" lon=\"", f3 + 7);
		}

		//ʶ��lon
		size_t f5 = nodeinfo_temp.find("\" lon=\"", 0);
		size_t f6 = nodeinfo_temp.find("\"", f5 + 7);

		string node_lon;
		double node_lon_f;

		while (f5 != nodeinfo_temp.npos)
		{
			node_lon = nodeinfo_temp.substr(f5 + 7, f6 - f5 - 7);
			outfile << node_lon << endl;
			node_lon_f = atof(node_lon.c_str());
			node_temp.set_lon(node_lon_f); //stringתdouble
			f5 = nodeinfo_temp.find("\" lon=\"", f6 + 1);
			f6 = nodeinfo_temp.find("\"", f5 + 7);
		}
		if (node_id != "")
		{
			allnode.push_back(node_temp);
		}


	}

	////��ʽ����������
	//for (int i = 0; i < allnode.size(); i++)
	//{
	//	cout << allnode[i].get_id() << "    ";
	//	cout << fixed << setprecision(7) << allnode[i].get_lat() << "    ";
	//	cout << allnode[i].get_lon() << "    ";//<< setprecision(7) 
	//	cout << i << endl;
	//}

	//************************�����û��Լ�����Ŀ�ĵ�********************
	int user_num = 0;
	cout << "���빤��������" << endl;
	cin >> user_num;

	User* p_user = new User[user_num];
	Node* p_dest = new Node[user_num];//ÿ���û���Ŀ�ĵء�
	srand((unsigned)time(0));//����ϵͳ���������
	int node_index;
	for (int i = 0; i < user_num; i++)
	{
		node_index = rand() % allnode.size();
		p_user[i].set_sno(i + 1);
		p_user[i].set_lat(allnode[node_index].get_lat());
		p_user[i].set_lon(allnode[node_index].get_lon());
		//p_user[i].show();

		node_index = rand() % allnode.size();
		p_dest[i].set_id(allnode[node_index].get_id());
		p_dest[i].set_lat(allnode[node_index].get_lat());
		p_dest[i].set_lon(allnode[node_index].get_lon());
	}

	//**************�û���������·������㣬��Ŀ�ĵؽ��������ƶ���*************
	//ֻ��ĳһ��ӵ������Ĺ����ߵ�����·����Ҫ��¼������
	vector<Node> waynode;
	moveUser(p_user[0].get_lon(), p_user[0].get_lat(), p_dest[0].get_lon(), p_dest[0].get_lat(), allnode, waynode);
	for (unsigned int j = 0; j < waynode.size(); j++)
	{
		cout << waynode[j].get_id() << "    ";
		cout << fixed << setprecision(7) << waynode[j].get_lat() << "    ";
		cout << waynode[j].get_lon() << endl;//<< setprecision(7) 
	}
	
	return 0;
}

//�ڵ��ú���֮ǰ���������waynode����ϰһ�²��� & �� * ������
bool moveUser(double lon1, double lat1, double lon2, double lat2, vector<Node> &allnode, vector<Node> &waynode)
{
	double distance = sqrt(pow(abs(lon1 - lon2), 2.0) + pow(abs(lat1 - lat2), 2.0));
	double temp_lat = lat1;
	double temp_lon = lon1;
	Node node_temp;
	if ((lon2 - lon1 == 0) && (lat2 - lat1 == 0))//����Ŀ�ĵ�
	{
		cout << "equal" << endl;
		return true;
	}else if ((lon2 - lon1 >= 0) && (lat2 - lat1 >= 0))
	{
		for (unsigned int i = 0; i < allnode.size(); i++)
		{
			if ((allnode[i].get_lat() >= lat1) && (allnode[i].get_lat() <= lat2)
				&& (allnode[i].get_lon() >= lon1) && (allnode[i].get_lon() <= lon2)
				&& !((allnode[i].get_lat() == lat1)&& (allnode[i].get_lon() >= lon1)))
			{
				//Ѱ�������ڣ������û�����ı�ǵ���Ϊ��һ�������㡣
				if (distance > sqrt(pow(abs(lon1 - allnode[i].get_lon()), 2.0) + pow(abs(lat1 - allnode[i].get_lat()), 2.0)))
				{
					distance = sqrt(pow(abs(lon1 - allnode[i].get_lon()), 2.0) + pow(abs(lat1 - allnode[i].get_lat()), 2.0));
					temp_lon = allnode[i].get_lon();
					temp_lat = allnode[i].get_lat();
				}
			}
		}//����ж��Ѿ��ҵ����һ�������
		if (distance == sqrt(pow(abs(lon1 - lon2), 2.0) + pow(abs(lat1 - lat2), 2.0)))
		{
			return true;
		}
			
		node_temp.set_lat(temp_lat);
		node_temp.set_lon(temp_lon);
		waynode.push_back(node_temp);//��·�����¼��waynode��
		moveUser(temp_lon, temp_lat, lon2, lat2, allnode, waynode);
	}
	else if ((lon2 - lon1 <= 0) && (lat2 - lat1 >= 0))
	{
		for (unsigned int i = 0; i < allnode.size(); i++)
		{
			if ((allnode[i].get_lat() >= lat1) && (allnode[i].get_lat() <= lat2)
				&& (allnode[i].get_lon() <= lon1) && (allnode[i].get_lon() >= lon2)
				&& !((allnode[i].get_lat() == lat1) && (allnode[i].get_lon() >= lon1)))
			{
				//Ѱ�ҵڶ������ڣ������û�����ı�ǵ�
				if (distance > sqrt(pow(abs(lon1 - allnode[i].get_lon()), 2.0) + pow(abs(lat1 - allnode[i].get_lat()), 2.0)))
				{
					distance = sqrt(pow(abs(lon1 - allnode[i].get_lon()), 2.0) + pow(abs(lat1 - allnode[i].get_lat()), 2.0));
					temp_lon = allnode[i].get_lon();
					temp_lat = allnode[i].get_lat();
				}
			}
		}
		if (distance == sqrt(pow(abs(lon1 - lon2), 2.0) + pow(abs(lat1 - lat2), 2.0)))
			return true;
		node_temp.set_lat(temp_lat);
		node_temp.set_lon(temp_lon);
		waynode.push_back(node_temp);
		moveUser(temp_lon, temp_lat, lon2, lat2, allnode, waynode);
	}
	else if ((lon2 - lon1 <= 0) && (lat2 - lat1 <= 0))
	{
		for (unsigned int i = 0; i < allnode.size(); i++)
		{
			if ((allnode[i].get_lat() <= lat1) && (allnode[i].get_lat() >= lat2)
				&& (allnode[i].get_lon() <= lon1) && (allnode[i].get_lon() >= lon2)
				&& !((allnode[i].get_lat() == lat1) && (allnode[i].get_lon() >= lon1)))
			{
				//Ѱ�ҵ��������ڣ������û�����ı�ǵ�
				if (distance > sqrt(pow(abs(lon1 - allnode[i].get_lon()), 2.0) + pow(abs(lat1 - allnode[i].get_lat()), 2.0)))
				{
					distance = sqrt(pow(abs(lon1 - allnode[i].get_lon()), 2.0) + pow(abs(lat1 - allnode[i].get_lat()), 2.0));
					temp_lon = allnode[i].get_lon();
					temp_lat = allnode[i].get_lat();
				}
			}
		}
		if (distance == sqrt(pow(abs(lon1 - lon2), 2.0) + pow(abs(lat1 - lat2), 2.0)))
			return true;
		node_temp.set_lat(temp_lat);
		node_temp.set_lon(temp_lon);
		waynode.push_back(node_temp);
		moveUser(temp_lon, temp_lat, lon2, lat2, allnode, waynode);
	}
	else if ((lon2 - lon1 >= 0) && (lat2 - lat1 <= 0))
	{
		for (unsigned int i = 0; i < allnode.size(); i++)
		{
			if ((allnode[i].get_lat() <= lat1) && (allnode[i].get_lat() >= lat2)
				&& (allnode[i].get_lon() >= lon1) && (allnode[i].get_lon() <= lon2)
				&& !((allnode[i].get_lat() == lat1) && (allnode[i].get_lon() >= lon1)))
			{
				//Ѱ�ҵ��������ڣ������û�����ı�ǵ�
				if (distance > sqrt(pow(abs(lon1 - allnode[i].get_lon()), 2.0) + pow(abs(lat1 - allnode[i].get_lat()), 2.0)))
				{
					distance = sqrt(pow(abs(lon1 - allnode[i].get_lon()), 2.0) + pow(abs(lat1 - allnode[i].get_lat()), 2.0));
					temp_lon = allnode[i].get_lon();
					temp_lat = allnode[i].get_lat();
				}
			}
		}
		if (distance == sqrt(pow(abs(lon1 - lon2), 2.0) + pow(abs(lat1 - lat2), 2.0)))
			return true;
		node_temp.set_lat(temp_lat);
		node_temp.set_lon(temp_lon);
		waynode.push_back(node_temp);
		moveUser(temp_lon, temp_lat, lon2, lat2, allnode, waynode);
	}
	
	return false;
}

