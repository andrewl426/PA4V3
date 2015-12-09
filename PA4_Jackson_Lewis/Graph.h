     //*////////////////////////////////////////*//
    //*//      PA4 - Networking Project      //*//
   //*//								    //*//
  //*//     Andrew Lewis - 113 760 25      //*//
 //*//     Justin Jackon - 114 377 51     //*//
//*////////////////////////////////////////*//

#ifndef GRAPH_H
#define GRAPH_H

// Includes
#include "Includes.h"
#include "Vertex.h"
#include "Path.h"

// Class definition
class graph
{
public:
	// Public vars
	unordered_map<int, vertex> _vertices;

	// Constructors
	graph();
	graph(unordered_map<int, vertex> new_vertices);

	// Copy Constructor

	// Destructor

	// Getters --- ADDITIONAL GETTERS ARE NEEDED FOR MANIPULATION OF INDIVIDUAL VERTICES probably - get_vertex_at(key), returning value
	unordered_map<int, vertex> get_vertices() const;

	// Setters --- ADDITIONAL SETTERS ARE NEEDED FOR MANIPULATION OF INDIVIDUAL VERTICES probably - set_vertex_at(key, value)
	void set_vertices(unordered_map<int, vertex> new_vertices);

	// Methods
	stack<vertex> computeShortestPath(vertex start, int starting_vertex, int ending_vertex);
	
private:
};

class PathWeightComparer
{
public:
	bool operator()(const vertex lhs, const vertex rhs)
	{
		return (lhs.getPathWeight() > rhs.getPathWeight());
	}
};

//hashing algorithm must exist in STD namespace
namespace std 
{
	template <>
	struct hash<vertex>
	{
		//provide a hash (convert grocery item into integer)
		size_t operator()(const vertex& item) const
		{
			size_t hash_val = 0;

			//to hash INTs using the STL
			hash<int> int_hash{};

			//define hashing algorithm.  Ours is pretty easy...
			hash_val = int_hash(item.get_id());

			//add others as necessary
			return hash_val;
		}
	};
}

#endif