     //*////////////////////////////////////////*//
    //*//      PA4 - Networking Project      //*//
   //*//								    //*//
  //*//     Andrew Lewis - 113 760 25      //*//
 //*//     Justin Jackon - 114 377 51     //*//
//*////////////////////////////////////////*//

// ANDREW; I think we should use main only to open and close files, and to create the network--- I think all real logic should be handled inside of networks tick()
//			also, is an output file required? I cant find anything about it in the PA 4 pdf...
//Justin: I don't think an outlook file is required. Since we are already doing cout.. adding fout might be work it.
//Justin: Im gonna make a cout/fout function that has a filename var built in.

#include "Includes.h"
#include "Network.h"

int main(int argc, char *argv[])
{
	string filename;
	
	/*
	// BEGIN util_meths EXAMPLE
	// ----	We should most likely place this function inside of the network driver 
	// ----	function that actually runs the simulation, and just pass the filename in there
	// ---- I can template this later if we want

	// declare var
	util_meths printer;
	int test_int = 100101;

	// set filename
	printer.setFilename("FILE_NAME_HERE.txt");
	
	// prints usage
	printer.cfout("You put a string here;\nUsing 'backslash n' allows you to do new lines.\nThe next line is templated...\n");
	printer.cfout(test_int);
	// END  util_meths EXAMPLE
	*/

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