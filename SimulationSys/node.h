#pragma once
#include <string>
using namespace std;

class Node
{
private:
	string id;
	double lon;
	double lat;
public:
	Node();
	~Node();
	Node(const string & s, double lo, double la);

	string get_id() const { return id; };
	double get_lon() const { return lon; };
	double get_lat() const { return lat; };
	void set_lon(double lo) { lon = lo; };
	void set_lat(double la) { lat = la; };
	void set_id(string i) { id = i; };
};

