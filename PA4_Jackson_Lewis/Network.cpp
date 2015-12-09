     //*////////////////////////////////////////*//
    //*//      PA4 - Networking Project      //*//
   //*//								    //*//
  //*//     Andrew Lewis - 113 760 25      //*//
 //*//     Justin Jackon - 114 377 51     //*//
//*////////////////////////////////////////*//

// Includes
#include "Network.h"

// Constructors
network::network()
{
	//_graph = empty!
	_tick_count = 0;
	//_message = empty!
}
network::network(graph new_graph, int new_tick_count, message new_message)
{
	_graph = new_graph;
	_tick_count = new_tick_count;
	_message = new_message;
}

// Copy Consturctor

// Destructor

// Getters
const graph network::get_graph()
{
	return _graph;
}
const int network::get_tick_count()
{
	return _tick_count;
}
const message network::get_message()
{
	return _message;
}

// Setters
void network::set_graph(graph new_graph)
{
	_graph = new_graph;
}
void network::set_tick_count(int new_tick_count)
{
	_tick_count = new_tick_count;
}
void network::set_message(message new_message)
{
	_message = new_message;
}

// Methods
void network::tick()
{
	_tick_count++;
}

void network::driver(string filename)
{
	string message_text;
	message message_item;
	packet temp_packet;
	int j = 0; // used to keep track of message order
	int starting_vertex;
	int ending_vertex;
	int ticker = 0;
	unordered_map<vertex, int> distances;
	vertex temp_vertex;
	stack<vertex> temp_stack;
	stack<vertex> reversed_temp_stack;

	// Run file processor
	file_processor(filename);

	// Get info from user
	cout << endl << "*****USER INPUT*****" << endl << endl;
	cout << "Enter a message to send: ";
	// Eat newline
	getline(cin, message_text);
	// clear buffer
	cin.clear();
	fflush(stdin); 
	// Get users msg
	getline(cin, message_text);
	// Get starting vert
	cout << "Enter a starting vertex: ";
	cin >> starting_vertex;
	// Get ending vert
	cout << "Enter a destination vertex: ";
	cin >> ending_vertex;
	
	// If the vertices are valid set message items start and end verts
	if (_graph.get_vertices().count(starting_vertex) && _graph.get_vertices().count(ending_vertex))
	{
		// Init message_item with starting and ending vertex
		message_item.set_starting_vertex(_graph.get_vertices().at(starting_vertex));
		message_item.set_ending_vertex(_graph.get_vertices().at(ending_vertex));
	}

	// Turn message into message item full of packets
	cout << endl << "*****PACKET SUMMARY*****" << endl << endl;
	for (auto i : message_text)
	{
		// Set packets char
		temp_packet.set_value(i);
		// Set packets order
		temp_packet.set_order(j);
		// Check to verify validity of vertex
		if (_graph.get_vertices().count(starting_vertex) && _graph.get_vertices().count(ending_vertex))
		{
			// Init prev location to source...
			temp_packet.set_previous_location(_graph.get_vertices().at(starting_vertex));
			// Init next location to source... (makes sure its initialized...)
			temp_packet.set_next_hop(_graph.get_vertices().at(starting_vertex));
			temp_packet.set_current_wait(_graph.get_vertices().at(starting_vertex).getPathWeight());
			// Init dest to ending vertex...
			temp_packet.set_destination(_graph.get_vertices().at(ending_vertex));
			temp_packet.get_destination()->set_id(ending_vertex);				
		}

		// Add new packet to the message's packet queue, _packets
		message_item.add_packet(temp_packet);

		// Print full packet info
		cout << "_PACKET_" << endl << "Val: " << temp_packet.get_value() << endl << "Ord: " << temp_packet.get_order() << endl
			<< "Wai: " << temp_packet.get_current_wait() << endl << "Pre: " << temp_packet.get_previous_location()->get_id() << endl 
			<< "Nex: " << temp_packet.get_next_hop()->get_id() << endl << "Des: " << temp_packet.get_destination()->get_id() << endl << endl;

		// Increment order counter
		j++;
	}

	// Check validity of source and dest nodes and message.
	if (_graph.get_vertices().count(starting_vertex) && _graph.get_vertices().count(ending_vertex))
	{
		cout << "*****SIMULATING*****" << endl << endl;

		// Set all loadfactors to 1 BASE STATE
		for (auto i : _graph.get_vertices())
		{
			i.second.set_load_factor(1);
		}

		// While not done...
		while (!message_item.get_packets().empty() || !in_the_network.empty()) // While true that we are not finished (More packets to be sent, or more packets are in transmission...)
		{
			// If msg has more packets to send, queue the next packet for transmission at the starting location
			if (!message_item.get_packets().empty())
			{
				//temp_packet.set_current_wait(temp_packet.get_current_wait()	* temp_packet.get_next_hop()->getPathWeight()); //trying to update current wait
				temp_packet.set_current_wait(temp_packet.get_next_hop()->getPathWeight() * temp_packet.get_next_hop()->get_load_factor()); // New set wait...
								
				// Compute the shortest route
				temp_stack = _graph.computeShortestPath(_graph.get_vertices().at(starting_vertex), _graph.get_vertices().at(starting_vertex).get_id(), temp_packet.get_destination()->get_id());
				
				// Reverse stack
				while (!temp_stack.empty())
				{
					reversed_temp_stack.push(temp_stack.top());
					temp_stack.pop();
				}

				// Print all of stack...
//				for (int i = 0; i < reversed_temp_stack.size(); i++)
//				{
//					cout << endl << "TS: " << reversed_temp_stack.top().get_id();
//					reversed_temp_stack.pop();
//				}

				temp_packet.get_packets_path().set_vertices(reversed_temp_stack);
				
				// Grab the shortest path out of distances (ie. the next_hop)
				/*		
				int k = 0;
				for (auto i : distances)
				{
					if (k == 0)
					{
						temp_vertex = i.first;
					}
					temp_packet.get_packets_path().push_vertex(i.first);
					k++;
				}
				
				// Compute the shortest route
				//distances = _graph.computeShortestPath(_graph.get_vertices().at(starting_vertex));
				
				// PRINT DIJKSTRA RESULTS
						cout << "*****DISTANCES*****" << endl << endl;
						cout << "Path";
						for (auto i : distances)
						{
							cout << " -> V" << i.first.get_id() << ", W" << i.second;
						}
						cout << endl << endl << "Distance to dest: ";
						for (auto i : distances)
						{
							if (i.first.get_id() == ending_vertex)
							{
								cout << " -> V" << i.first.get_id() << ", W" << i.second;
							}
						}
						cout << endl << endl << "*****END DISTS*****" << endl;								
				*/

				temp_vertex = reversed_temp_stack.top();
				temp_packet.get_packets_path().set_vertices(reversed_temp_stack);
				while (!reversed_temp_stack.empty())
				{
					reversed_temp_stack.pop();
				}
				
				// Determine next intermediary node
				  // Check path?
				temp_packet = message_item.pop_packet();

				temp_packet.set_previous_location(_graph.get_vertices().at(temp_packet.get_next_hop()->get_id()));//initializiing temp packet
				temp_packet.set_next_hop(_graph.get_vertices().at(temp_vertex.get_id()));
				//temp_packet.get_previous_location()->set_edges();

				// Queue the packets arrival at the proper time
				  // push onto queue?
				temp_packet.set_current_wait(temp_packet.get_next_hop()->getPathWeight() * temp_packet.get_next_hop()->get_load_factor());

				// Increase the load factor of each node that communicated this tick
				// Update source load factor
				temp_packet.get_previous_location()->set_load_factor(temp_packet.get_previous_location()->get_load_factor()+1);
				// Update dest load factor
				temp_packet.get_next_hop()->set_load_factor(temp_packet.get_next_hop()->get_load_factor()+1);

				// Load factor out
				// Print load factor info... 
				/*
				cout << endl << "Load Factor: First Loop" << endl;
				cout << "PreLF: " << temp_packet.get_previous_location()->get_load_factor() << endl;
				cout << "NexLF: " << temp_packet.get_next_hop()->get_load_factor() << endl;
				*/
		
				// Push temp_packet into the network vector
				in_the_network.push_back(temp_packet);

				// prints adams style info
				cout << "Sending packet " << temp_packet.get_value() << " to vertex " << temp_packet._next_hop->get_id()
					<< " with a wait of " << temp_packet.get_current_wait() << " at time " << ticker << endl;
			}


			// For each packet in the network...			
			for (int i = 0; i < in_the_network.size(); i++)
			{
				// Decrement expected arrival time
				// Arrival --
				in_the_network[i].set_current_wait((in_the_network[i].get_current_wait() - 1)); // Not sure if this works

				// If time is <= 0, it arrived
				if (in_the_network[i].get_current_wait() <= 0) // Not sure if this works
				{

					// Decrement load factor source
					// if the loadfactor is > 1
					if (in_the_network[i].get_previous_location()->get_load_factor() > 1)
					{
						in_the_network.at(i).get_previous_location()->set_load_factor(in_the_network.at(i).get_previous_location()->get_load_factor() - 1);
						//in_the_network[i].get_previous_location()->set_load_factor(in_the_network[i].get_previous_location()->get_load_factor() - 1);
					}
					
					// Decrement load factor dest
					// if the loadfactor is > 1
					if (in_the_network[i].get_next_hop()->get_load_factor() > 1)
					{
						//in_the_network[i].get_next_hop()->set_load_factor(in_the_network[i].get_next_hop()->get_load_factor() - 1);
						in_the_network.at(i).get_next_hop()->set_load_factor(in_the_network.at(i).get_next_hop()->get_load_factor() - 1);
					}

					// Print load factor info...
					/*
					cout << endl << "Load Factor: Decrement" << endl;
					cout << "PreLF: " << in_the_network[i].get_previous_location()->get_load_factor() << endl;
					cout << "NexLF: " << in_the_network[i].get_next_hop()->get_load_factor() << endl;
					*/
					
					// If packet has not reached final dest, schedule another transmission using the first loop (Alter nodes transmitting packet)
					if (in_the_network[i].get_previous_location()->get_id() != ending_vertex)
					{
						// Schedule another transmission
						// Compute the shortest route
						temp_stack = _graph.computeShortestPath(_graph.get_vertices().at(starting_vertex), _graph.get_vertices().at(starting_vertex).get_id(), temp_packet.get_destination()->get_id());

						// Reverse stack
						while (!temp_stack.empty())
						{
							reversed_temp_stack.push(temp_stack.top());
							temp_stack.pop();
						}

						// Print all of stack...
//						for (int i = 0; i < reversed_temp_stack.size(); i++)
//						{
//							cout << endl << "TS: " << reversed_temp_stack.top().get_id();
//							reversed_temp_stack.pop();
//						}

						in_the_network[i].get_packets_path().set_vertices(reversed_temp_stack);

						// Grab the shortest path out of distances (ie. the next_hop)
						/*
						int k = 0;
						for (auto i : distances)
						{
						if (k == 0)
						{
						temp_vertex = i.first;
						}
						temp_packet.get_packets_path().push_vertex(i.first);
						k++;
						}

						// Compute the shortest route
						//distances = _graph.computeShortestPath(_graph.get_vertices().at(starting_vertex));

						// PRINT DIJKSTRA RESULTS
						cout << "*****DISTANCES*****" << endl << endl;
						cout << "Path";
						for (auto i : distances)
						{
						cout << " -> V" << i.first.get_id() << ", W" << i.second;
						}
						cout << endl << endl << "Distance to dest: ";
						for (auto i : distances)
						{
						if (i.first.get_id() == ending_vertex)
						{
						cout << " -> V" << i.first.get_id() << ", W" << i.second;
						}
						}
						cout << endl << endl << "*****END DISTS*****" << endl;
						*/

						
						reversed_temp_stack.pop();
						temp_vertex = reversed_temp_stack.top();
						
						in_the_network[i].get_packets_path().set_vertices(reversed_temp_stack);
						//while (!reversed_temp_stack.empty())
						//{
						//	reversed_temp_stack.pop();
						//}

						// Determine next intermediary node
						// Check path?
						if (!message_item.get_packets().empty())
						{
							in_the_network[i] = message_item.pop_packet();
						}

						in_the_network[i].set_previous_location(_graph.get_vertices().at(in_the_network[i].get_next_hop()->get_id()));//initializiing temp packet
						in_the_network[i].set_next_hop(_graph.get_vertices().at(temp_vertex.get_id()));
						//temp_packet.get_previous_location()->set_edges();

						// Queue the packets arrival at the proper time
						// push onto queue?
						in_the_network[i].set_current_wait(in_the_network[i].get_next_hop()->getPathWeight() * in_the_network[i].get_next_hop()->get_load_factor());

						// Increase the load factor of each node that communicated this tick
						// Update source load factor
						in_the_network[i].get_previous_location()->set_load_factor(in_the_network[i].get_previous_location()->get_load_factor() + 1);
						// Update dest load factor
						in_the_network[i].get_next_hop()->set_load_factor(in_the_network[i].get_next_hop()->get_load_factor() + 1);

						// Print load factor info...
						/*
						cout << endl << "Load Factor: Second Loop" << endl;
						cout << "PreLF: " << in_the_network[i].get_previous_location()->get_load_factor() << endl;
						cout << "NexLF: " << in_the_network[i].get_next_hop()->get_load_factor() << endl;
						*/

						// prints adams style info
						cout << "Sending packet " << in_the_network[i].get_value() << " to vertex " << in_the_network[i]._next_hop->get_id()
							<< " with a wait of " << in_the_network[i].get_current_wait() << " at time " << ticker << endl;
					}

					//cout << in_the_network[i].get_destination()->get_id() << " " << ending_vertex << endl;
					//system("PAUSE");
					// If packet has reached destination, add to list of completed packets
					if (in_the_network[i].get_destination()->get_id() == ending_vertex)
					{
						// push this packet to completed packets
						completed_packets.push_back(in_the_network[i]);
						completed_packets.back().set_arrival_time(ticker);
						//need to set route here as well once its know
						
						in_the_network.erase(in_the_network.begin()+i);
						in_the_network.shrink_to_fit();
					}
				}
			}
			ticker++;
		}
	}

	print_arrivals(); //print what happened during the simulation
}

void network::print_arrivals()
{
	cout << endl << endl << "Packet     Arrival Time     Route" << endl;
	for (auto i : completed_packets)
	{
		cout << i.get_value() << "          " << i.get_arrival_time() << "          Path coming soon" << endl;
		/*for (auto j : i._packets_path._vertices) this will be route soon
		{

		}*/
	}
}

void network::file_processor(string filename)
{
	ifstream input_file{ filename };
	string line = "";
	vector<string> parsed;
	unordered_map<vertex*, int> temp_paths;
	int i = 0;
	int last_key = 0;
	int current_key = 0;

	while (input_file.good() == true)
	{
		getline(input_file, line);
		parsed = string_parser(line);
		parsed.shrink_to_fit();

		current_key = stoi(parsed[0]);
		if (last_key != current_key)
		{
			last_key = stoi(parsed[0]);
			temp_paths.clear();
		}

		if (parsed.size() == 1) //This should be a new node then. 
		{			
			_graph._vertices[stoi(parsed[0])].set_id(stoi(parsed[0]));
		}
		else // this is a path
		{
			temp_paths[&_graph._vertices[stoi(parsed[1])]] = stoi(parsed[2]);
			_graph._vertices[stoi(parsed[0])].set_edges(temp_paths);
			_graph._vertices[stoi(parsed[0])].set_path_weight(stoi(parsed[2]));
		}
	}

	// Prints Vertex:Id:EdgeWeight
	cout << "*****GRAPH SUMMARY*****" << endl;
	for (auto i : _graph.get_vertices())
	{
		// Vertex (Header)
		cout << endl << "Vertex: " << i.first << endl << "Paths:" << endl;
		for (auto j : i.second.get_edges())
		{
			// Source
			cout << "   Src: " << i.first << " ";
			// Dest ID
			cout << "   Des: " << j.first->get_id() << " ";
			// Edge Weight
			cout << "   Wei: " << j.second << " ";
			cout << endl;
		}
	}
}

vector<string> network::string_parser(string tobeparsed)
{
	vector<string> pieces{};
	string delimiter = " ";

	//keep track of starting location for substring
	int start = 0;
	int i = 0;

	//find the first instance of our delimiter
	int location = tobeparsed.find(delimiter);

	//go until we have no more delimiters
	while (location != string::npos)
	{
		//grab next piece
		string piece = tobeparsed.substr(start, location - start);
		if (piece[0] == '"')
		{
			start = location + 1;
			location = tobeparsed.find(delimiter, start);
			piece.append(tobeparsed.substr(start, location - start));
		}

		pieces.push_back(piece);//add to vector

		start = location + 1;
		location = tobeparsed.find(delimiter, start);
		i++;
	}

	//right here, we have a bit of text that still needs
	//to be taken care of
	string piece = tobeparsed.substr(start);

	//it's possible that our final piece is empty
	//(optional, could always add the piece regardless of state)
	if (piece.length() > 0)
	{
		pieces.push_back(piece);
	}

	//finally, all done
	return pieces;
}
