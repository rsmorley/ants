#ifndef NODE_H_
#define NODE_H_

#include "Location.h"

/*
    struct for representing a node in an A* search
*/
struct Node
{
    int g, h;
	Location loc;
	Node* parent;

    Node()
		:	g(0),
			h(0),
			parent(0)
    {
    };

    Node(int g, int h, const Location& loc, Node* parent)
		:	g(g),
			h(h),
			loc (loc),
			parent (parent)
    {
    };

	bool operator<(const Node& n) const 
	{
		return f() < n.f();
	}

	int f() const {
		return g+h;
	};
	int gValue() const {
		return g;
	};
	int hValue() const {
		return h;
	};

};

#endif //NODE_H_
