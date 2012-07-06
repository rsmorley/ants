#ifndef ASTAR_H_
#define ASTAR_H_

#include "Bug.h"
#include "Location.h"
#include "Node.h"
#include "State.h"

#include <algorithm>
#include <vector>

/*
    A* search class
*/

//const char DIRECTIONS[4] = {'N', 'E', 'S', 'W'};

class AStar
{
	public: 
		AStar(const Location& src, const Location& dest, const State& state, const int maxDepth);

		std::vector<Location> getPath() const;
		bool search();

	private:
		struct LocationExists {
			LocationExists(const Location& location) : location(location) {}
			bool operator()(Node* node) const { return node->loc == location; }
			Location location;
		};

		struct NodeCompare {
			bool operator()( const Node* n0, const Node* n1) {
				return n0->f() > n1->f();
			}
		};


		std::vector<Node*> openNodes;
		std::vector<Node*> closedNodes;
		
		std::vector<Location> path;

		int maxDepth;

		Location src;
		Location dest;

		const State& currentState;

		bool step();

		Bug bug;
};

#endif //ASTAR_H_
