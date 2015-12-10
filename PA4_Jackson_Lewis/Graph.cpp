     //*////////////////////////////////////////*//
    //*//      PA4 - Networking Project      //*//
   //*//								    //*//
  //*//     Andrew Lewis - 113 760 25      //*//
 //*//     Justin Jackon - 114 377 51     //*//
//*////////////////////////////////////////*//

// Includes
#include "Graph.h"

// Overloaders
int operator==(const vertex &lhs, const vertex &rhs)
{
	return lhs.get_id() == rhs.get_id();
}
bool operator<(const vertex &lhs, const vertex &rhs)
{
	return lhs.get_id() < rhs.get_id();
}
bool operator>(const vertex &lhs, const vertex &rhs)
{
	return lhs.get_id() > rhs.get_id();
}

// Constructors
graph::graph()
{
	//_vertices = empty!
}
graph::graph(unordered_map<int, vertex*> new_vertices)
{
	_vertices = new_vertices;
}

// Copy Consturctor

// Destructor

// Getters
unordered_map<int, vertex*> graph::get_vertices() const
{
	return _vertices;
}

// Setters
void graph::set_vertices(unordered_map<int, vertex*> new_vertices)
{
	_vertices = new_vertices;
}

// Methods
unordered_map<vertex*, path> graph::computeShortestPath(vertex* start , int starting_vertex, int ending_vertex)
{

	//holds known distances
	unordered_map<vertex*, path> paths;
	//underlying heap
	priority_queue<path, vector<path>, PathWeightComparer> dijkstra_queue{};
	path temp;

	//reset start's path weight
	start->set_path_weight(0);
	temp.push_vertex(start);


	//make sure that the starting vertex is in the graph
	if (_vertices.find(start->get_id()) != _vertices.end())
	{
		//push on starting vertex
		dijkstra_queue.push(temp);


		//while queue not empty
		while (dijkstra_queue.empty() == false)
		{
			//push on outgoing edges that haven't been discovered
			path top = dijkstra_queue.top();
			dijkstra_queue.pop();

			//Top of heap not known (in distances)?
			if (paths.find(top.get_vertices().top()) == paths.end())
			{	
				paths[top.get_vertices().top()] = top;

				//push on outgoing edges
				for (auto item : top.get_vertices().top()->get_edges())
				{
					vertex *next = item.first;


					//not known?  add to heap
					if (paths.find(next) == paths.end())
					{
						path next_path = top;
						int current_path_weight = item.second * next->get_load_factor();
						
						next_path.push_vertex(next);
						next_path.set_distance_traveled(top.get_distance_traveled() + current_path_weight);
						dijkstra_queue.push(next_path);
					}
				}
			}
		}
	}


	return paths;
}