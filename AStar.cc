#include "AStar.h"

AStar::AStar(const Location& src, const Location& dest, const State& state, const int maxDepth)
	:	src (src),
		dest (dest),
		currentState( state),
		maxDepth( maxDepth)
{
	openNodes.push_back(new Node(0, currentState.manDistance(src, dest), src, 0));
}

std::vector<Location> AStar::getPath() const
{
	return path;
}

bool AStar::search()
{

	while(openNodes.size() > 0)
	{
		if(step()) { 
			return true; 
		}
	}
	return false;
}

bool AStar::step()
{
	Node* current = openNodes.front();

	if(current->loc == dest) {
		path.clear();
		while(current->parent != 0) {
			path.push_back(current->loc);
			current = current->parent;
		}

		if(current->loc == src) {
			path.push_back(src);
		}

		std::reverse(path.begin(), path.end());

		for(std::vector<Location>::iterator it = path.begin(); it < path.end();  it++) {
			Location p = *it;
		}

		for(std::vector<Node*>::iterator it = openNodes.begin(); it < openNodes.end();  it++) {
			delete *it;
		}
		openNodes.clear();

		for(std::vector<Node*>::iterator it = closedNodes.begin(); it < closedNodes.end();  it++) {
			delete *it;
		}
		closedNodes.clear();

		return true;
	}

	std::pop_heap(openNodes.begin(), openNodes.end(), NodeCompare());
	openNodes.pop_back();
	closedNodes.push_back(current);


	if(current->f() + 1 < maxDepth) {
		for(int i=0; i < 4; i++)
		{
			Location neighbor = currentState.getLocation(current->loc, i);

			if(currentState.grid[neighbor.row][neighbor.col].isWater || currentState.grid[neighbor.row][neighbor.col].ant != -1)
			{
				continue;
			}

			std::vector<Node*>::iterator it = std::find_if(openNodes.begin(), openNodes.end(), LocationExists(neighbor));
			if(it != openNodes.end()) {
				Node* existing = *it;

				if(current->g + 1 < existing->g) {
					existing->g = current->g +1;
					existing->parent = current;
					std::make_heap(openNodes.begin(), openNodes.end(), NodeCompare());
				}
				continue;
			}

			it = std::find_if(closedNodes.begin(), closedNodes.end(), LocationExists(neighbor));
			if(it != closedNodes.end()) {
				continue;
			}

			Node* nNode = new Node(current->g + 1, currentState.manDistance(neighbor, dest), neighbor, current);
			openNodes.push_back(nNode);
			std::push_heap(openNodes.begin(), openNodes.end(), NodeCompare());

		}
	}

	return false;
		
}

