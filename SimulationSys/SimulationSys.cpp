// SimulationSys.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include "user.h"
#include "uav.h"
#include "node.h"

using namespace std;
//ʹ�ó�ʼ���б��ʼ������

int main()
{
	int user_num = 0;
	cout << "���빤��������" << endl;
	cin >> user_num;

	User* p_user = new User[user_num];
	for (int i = 0; i < user_num; i++)
	{
		p_user[i].show();
	}


	/*
		User u1;
		Uav u2;
		int id = 2;
		u2.set_sno(id);
		cout << "hello" << u2.get_sno() << endl;
		*/
	return 0;
}

