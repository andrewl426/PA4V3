     //*////////////////////////////////////////*//
    //*//      PA4 - Networking Project      //*//
   //*//								    //*//
  //*//     Andrew Lewis - 113 760 25      //*//
 //*//     Justin Jackon - 114 377 51     //*//
//*////////////////////////////////////////*//

#ifndef NETWORK_H
#define NETWORK_H

// Includes
#include "Includes.h"
#include "Graph.h"
#include "Message.h"

// Class definition
class network
{
public:
	// Public vars
	graph _graph;
	int _tick_count;
	message _message;
	vector<packet> in_the_network;
	vector<packet> completed_packets;
	path path;

	// Constructors
	network();
	network(graph new_graph, int new_tick_count, message new_message);

	// Copy Constructor

	// Destructor

	// Getters
	const graph get_graph();
	const int get_tick_count();
	const message get_message();
	
	// Setters
	void set_graph(graph new_graph);
	void set_tick_count(int new_tick_count);
	void set_message(message new_message);

	// Methods
	void tick();
	void driver(string filename);
	void file_processor(string filename);
	vector<string> string_parser(string tobeparsed);
	void print_arrivals();

private:
};




#endif