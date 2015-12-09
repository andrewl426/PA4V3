     //*////////////////////////////////////////*//
    //*//      PA4 - Networking Project      //*//
   //*//								    //*//
  //*//     Andrew Lewis - 113 760 25      //*//
 //*//     Justin Jackon - 114 377 51     //*//
//*////////////////////////////////////////*//

#ifndef VERTEX_H
#define VERTEX_H

// Includes
#include "Includes.h"

// Class definition
class vertex
{
public:
	// Public vars
	int _id;
	unordered_map<vertex*, int> _edges;
	int _load_factor;
	int _path_weight;
	static int _id_counter;

	// Constructors
	vertex();
	vertex(int new_id, unordered_map<vertex*, int> new_edges, int new_load_factor);

	// Copy Constructor

	// Destructor

	// Getters
	int vertex::get_id() const;
	unordered_map<vertex*, int> get_edges();
	int get_load_factor();
	int getPathWeight() const;

	// Setters
	void set_id(int new_id);
	void set_edges(unordered_map<vertex*, int> new_edges);
	void set_load_factor(int new_load_factor);
	void set_path_weight(int new_weight);

	// Methods
private:
	
};

#endif