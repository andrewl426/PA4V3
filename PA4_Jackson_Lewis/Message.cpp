     //*////////////////////////////////////////*//
    //*//      PA4 - Networking Project      //*//
   //*//								    //*//
  //*//     Andrew Lewis - 113 760 25      //*//
 //*//     Justin Jackon - 114 377 51     //*//
//*////////////////////////////////////////*//

// Includes
#include "Message.h"

// Constructors
message::message()
{
	//_packets = empty!
	//_starting_vertex = empty!
	//_ending_vertex = empty!
}
message::message(queue<packet> new_packets, vertex new_starting_vertex, vertex new_ending_vertex)
{
	_packets = new_packets;
	_starting_vertex = new_starting_vertex;
	_ending_vertex = new_ending_vertex;
}

// Copy Consturctor

// Destructor

// Getters
const queue<packet> message::get_packets()
{
	return _packets;
}
const vertex message::get_starting_vertex()
{
	return _starting_vertex;
}
const vertex message::get_ending_vertex()
{
	return _ending_vertex;
}

// Setters
void message::set_packets(queue<packet> new_packets)
{
	_packets = new_packets;
}
void message::set_starting_vertex(vertex new_starting_vertex)
{
	_starting_vertex = new_starting_vertex;
}
void message::set_ending_vertex(vertex new_ending_vertex)
{
	_ending_vertex = new_ending_vertex;
}

// Methods
void message::add_packet(packet new_packet)
{
	_packets.push(new_packet);
}

packet message::pop_packet()
{
	packet temp_packet = _packets.front();
	_packets.pop();

	return temp_packet;
}
