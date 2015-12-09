     //*////////////////////////////////////////*//
    //*//      PA4 - Networking Project      //*//
   //*//								    //*//
  //*//     Andrew Lewis - 113 760 25      //*//
 //*//     Justin Jackon - 114 377 51     //*//
//*////////////////////////////////////////*//

#ifndef MESSAGE_H
#define MESSAGE_H

// Includes
#include "Includes.h"
#include "Vertex.h"
#include "Packet.h"

// Class definition
class message
{
public:
	// Public vars
	queue<packet> _packets;
	vertex _starting_vertex;
	vertex _ending_vertex;
	
	// Constructors
	message();
	message(queue<packet> new_packets, vertex new_starting_vertex, vertex new_ending_vertex);

	// Copy Constructor

	// Destructor

	// Getters
	const queue<packet> get_packets();
	const vertex get_starting_vertex();
	const vertex get_ending_vertex();

	// Setters
	void set_packets(queue<packet> new_packets);
	void set_starting_vertex(vertex new_starting_vertex);
	void set_ending_vertex(vertex new_ending_vertex);

	// Methods
	void add_packet(packet new_packet);
	packet pop_packet();

private:
};

#endif