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
graph::graph(unordered_map<int, vertex> new_vertices)
{
	_vertices = new_vertices;
}

// Copy Consturctor

// Destructor

// Getters
unordered_map<int, vertex> graph::get_vertices() const
{
	return _vertices;
}

// Setters
void graph::set_vertices(unordered_map<int, vertex> new_vertices)
{
	_vertices = new_vertices;
}

// Methods
stack<vertex> graph::computeShortestPath(vertex start , int starting_vertex, int ending_vertex)
{
	/*
	A note on Dijkstra's Algorithm
	__________________________________________________________________________________________
	We are using a node's "load factor" to indicate the speed at which a given node operates.
	As a node becomes more saturated with network traffic, it likely will take the node longer
	to respond to any given message. To model this behavior, calculate an edge's weight to be
	the product of the edge's unadjusted weight and the node's load factor;

		(weight = vertex.getWeight() * vertext.getLoadFactor()).
	*/
	
	//holds known distances
	unordered_map<vertex, int> distances;
	stack<vertex> temp_stack;
	
	path for_the_stack;
	//underlying heap
	priority_queue<vertex, vector<vertex>, PathWeightComparer> dijkstra_queue{};

//cout << endl << "*****STA DIJKSTRAS*****" << endl;

	//reset start's path weight
	start.set_path_weight(0);
//cout << endl << "start.path_weight: " << start.getPathWeight();

	//make sure that the starting vertex is in the graph
	if (_vertices.find(start.get_id()) != _vertices.end())
	{
		//push on starting vertex
		dijkstra_queue.push(start);
//cout << endl << "Push on start(id): " << start.get_id();


		//while queue not empty
		while (dijkstra_queue.empty() == false)
		{
			//push on outgoing edges that haven't been discovered
			vertex top = dijkstra_queue.top();
			dijkstra_queue.pop();
			temp_stack.push(top); //PUSH where we went

			//Top of heap not known (in distances)?
			if (distances.find(top) == distances.end())
			{
				//cout << top.get_load_factor() << endl;
				//make known
				int current_path_weight = top.getPathWeight() * top.get_load_factor();
				//cout << "Current path weight: " << current_path_weight << endl;
				distances[top] = current_path_weight;
				if (top.get_id() == ending_vertex)
				{
//cout << endl << endl << "*****END DIJKSTRAS*****" << endl << endl;
					return temp_stack;
				}
				
//cout << endl << endl << "vertex top(id): " << top.get_id();
//cout << endl << "vertex top(PW): " << top.getPathWeight();
//cout << endl << "vertex top(LF): " << top.get_load_factor();

				//push on outgoing edges
				for (auto item : top.get_edges())
				{
					vertex *next = item.first;
					int weight = item.second * top.get_load_factor();
// Prints the wight equation..	//cout << endl << "Weight = " << item.second << " * " << top.get_load_factor();

					next->set_path_weight(weight + current_path_weight);

					//not known?  add to heap
					if (distances.find(*next) == distances.end())
					{
						dijkstra_queue.push(*next);
					}
				}
			}
		}
	}
//cout << endl << endl << "*****END DIJKSTRAS*****" << endl << endl;

	// Print all of stack...
//	for (int i = 0; i < temp_stack.size(); i++)
//	{
//		cout << endl << "TS: " << temp_stack.top().get_id();
//		temp_stack.pop();
//	}

	/*cout << "*****DISTANCES*****" << endl << endl;
	cout << "Path";
	for (auto i : distances)
	{
		cout << " -> V" << i.first.get_id() << ", W" << i.second;
	}
	cout << endl << "Distance to dest: ";
	for (auto i : distances)
	{
		if (i.first.get_id() == 1)
		{
			cout << " -> V" << i.first.get_id() << ", W" << i.second;
		}
	}
	cout << endl << endl << "*****END DISTS*****" << endl;*/



	return temp_stack;
}