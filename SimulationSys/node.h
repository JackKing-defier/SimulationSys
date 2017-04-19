#pragma once
#include <string>
using namespace std;

class Node
{
private:
	string id;
	float lon;
	float lat;
public:
	Node();
	~Node();
	Node(const string & s, float lo, float la);
};

