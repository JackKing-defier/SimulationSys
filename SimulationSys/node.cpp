#include "stdafx.h"
#include "node.h"

Node::Node()
{
}

Node::~Node()
{
}

Node::Node(const string & s, float lo, float la)
{
	id = s;
	lon = lo;
	lat = la;
}
