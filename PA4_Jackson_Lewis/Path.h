     //*////////////////////////////////////////*//
    //*//      PA4 - Networking Project      //*//
   //*//								    //*//
  //*//     Andrew Lewis - 113 760 25      //*//
 //*//     Justin Jackon - 114 377 51     //*//
//*////////////////////////////////////////*//

#ifndef PATH_H
#define PATH_H

// Includes
#include "Includes.h"
#include "Vertex.h"

// Class definition
class path
{
public:
	// Public vars
	stack<vertex> _vertices;
	int _distance_traveled = 0;

	// Constructors
	path();
	path(stack<vertex> new_vertices, int new_distance_traveled);

	// Copy Constructor

	// Destructor

	// Getters
	stack<vertex> get_vertices() const;
	int get_distance_traveled() const;

	// Setters
	void set_vertices(stack<vertex> new_vertices);
	void set_distance_traveled(int new_distance_traveled);

	// Methods
	void path::push_vertex(vertex next_vertex);
	vertex path::pop_vertex();

private:
};

#endif