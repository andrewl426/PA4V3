     //*////////////////////////////////////////*//
    //*//      PA4 - Networking Project      //*//
   //*//								    //*//
  //*//     Andrew Lewis - 113 760 25      //*//
 //*//     Justin Jackon - 114 377 51     //*//
//*////////////////////////////////////////*//

#include "Includes.h"
#include "Network.h"

int main(int argc, char *argv[])
{
	string filename;

	for (int i = 1; i < argc; i++) //argv is much easier to deal with as a string
	{
		filename = argv[i];
	}
	if (filename == "")//if argv is null/empty prompt user for a filename
	{
		cout << "Enter a jobs filename: ";
		cin >> filename;
		cout << endl;
	}


	network dothething;

	dothething.driver(filename);
	
	// End of program pause
	cout << endl << endl;
	system( "pause" );
}