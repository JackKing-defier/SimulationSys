#include <iostream>
#include "user.h"

User::User()
{
	sno = (int)0;
	id = "";
	lon = 0.0;
	lat = 0.0;
	isEnabled = "";
	isOnDuty = "";
	name = "";
	mid = "";
}

User::User(int s, const string & i, float lo, float la, const string & e, const string & o, const string & n, const string & m)
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
	cout << sno << id << lon << lat << isEnabled << isOnDuty << name << mid << endl;
}