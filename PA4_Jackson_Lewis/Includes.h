     //*////////////////////////////////////////*//
    //*//      PA4 - Networking Project      //*//
   //*//								    //*//
  //*//     Andrew Lewis - 113 760 25      //*//
 //*//     Justin Jackon - 114 377 51     //*//
//*////////////////////////////////////////*//

// This is an overall include file which is included by every file inside this project.

#ifndef INCLUDES_H
#define INCLUDES_H

// Includes
#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <stack>
#include <cstdlib>

// Using
using namespace std; //Hope your ok with this shortcut // its fine
using std::cout;
using std::cin;
using std::endl;

// Utility Methods
class util_meths
{
public:
	string _filename;

	// Constructor
	util_meths();

	// Setter
	void util_meths::setFilename(string new_filename);

	// Methods
	void cfout(string str);

	//template<typename T>
	//void cfout(T temp);
};


#endif