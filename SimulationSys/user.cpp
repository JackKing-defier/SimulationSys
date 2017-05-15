#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include "user.h"

using namespace std;


User::User()
{
	sno = 0;
	id = "";
	lon = 0.0;
	lat = 0.0;
	isEnabled = "";
	isOnDuty = "";
	name = "";
	mid = "";
}

User::User(int s, const string & i, double lo, double la, const string & e, const string & o, const string & n, const string & m)
{
	sno = s;
	id = i;
	lon = lo;
	lat = la;
	isEnabled = e;
	isOnDuty = o;
	name = n;
	mid = m;
}

User::~User()
{

}

void User::show()
{
	cout << sno << "    ";
	cout << id << "    ";
	cout << fixed << setprecision(7) << lon << "    ";
	cout << setprecision(7) << lat << "    ";
	cout << isEnabled << "    "; 
	cout << isOnDuty << "    "; 
	cout << name << "    "; 
	cout << mid << endl;
}