     //*////////////////////////////////////////*//
    //*//      PA4 - Networking Project      //*//
   //*//								    //*//
  //*//     Andrew Lewis - 113 760 25      //*//
 //*//     Justin Jackon - 114 377 51     //*//
//*////////////////////////////////////////*//

// Includes
#include "Path.h"

// Constructors
path::path()
{
	//_vertices = empty!
	_distance_traveled = 0;
}
path::path(stack<vertex> new_vertices, int new_distance_traveled)
{
	_vertices = new_vertices;
	_distance_traveled = new_distance_traveled;
}

// Copy Consturctor

// Destructor

// Getters
stack<vertex> path::get_vertices() const
{
	return _vertices;
}
int path::get_distance_traveled() const
{
	return _distance_traveled;
}

// Setters
void path::set_vertices(stack<vertex> new_vertices)
{
	_vertices = new_vertices;
}
void path::set_distance_traveled(int new_distance_traveled)
{
	_distance_traveled = new_distance_traveled;
}

// Methods
void path::push_vertex(vertex next_vertex)
{
	_vertices.push(next_vertex);
}
vertex path::pop_vertex()
{
	vertex ret_val;
	ret_val = _vertices.top();
	_vertices.pop();

	return ret_val;
}