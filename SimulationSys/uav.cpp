#include <iostream>
#include "uav.h"
#include "stdafx.h"

Uav::Uav()
{
	sno = 0;
	id = "";
	model = "";
	brand = "";
	max_height = "";
	max_minute = "";
	max_distance = "";
	memory = "";
	resolution = "";
	min_focus = "";
	max_focus = "";
}

Uav::Uav(int s, const string & i, const string & lo, const string & la,
	const string & e, const string & o, const string & n,
	const string & m, const string & r, const string & mf,
	const string & maxf)
{
	sno = s;
	id = i;
	model = lo;
	brand = la;
	max_height = e;
	max_minute = o;
	max_distance = n;
	memory = m;
	resolution = r;
	min_focus = mf;
	max_focus = maxf;
}


Uav::~Uav()
{

}

void Uav::show()
{
	cout << sno << id << model << brand << max_height << max_minute << max_distance << memory << resolution << min_focus << max_focus << endl;
}