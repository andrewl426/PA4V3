     //*////////////////////////////////////////*//
    //*//      PA4 - Networking Project      //*//
   //*//								    //*//
  //*//     Andrew Lewis - 113 760 25      //*//
 //*//     Justin Jackon - 114 377 51     //*//
//*////////////////////////////////////////*//

#include "Includes.h"

// Constructors
util_meths::util_meths()
{
	_filename = "";
}

// Setter
void util_meths::setFilename(string new_filename)
{
	 _filename = "";
}

// Methods
void util_meths::cfout(string str)
{
	if (str == "endl")
	{
		cout << endl;
	}

	cout << str;
}

//template<typename T>
//void util_meths::cfout(T temp)
//{
//	cout << temp;
//}
