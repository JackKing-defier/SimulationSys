#include "stdafx.h"
#include "node.h"

Node::Node()
{
}

Node::~Node()
{
}

Node::Node(const string & s, double lo, double la)
{
	id = s;
	lon = lo;
	lat = la;
}
