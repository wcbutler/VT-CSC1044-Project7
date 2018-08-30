// CS 1044 Project 7 Fall 2001
//
// Student: Will Butler
// 
// Programmer:    Will Butler
// OS:            Windows ME
// System:        Pentium IV, 256 MB Memory
// Compiler:      Visual C++ 6.0 
// Last modified: November 6, 2001
//
// Purpose: To read in an parallel arrays from an input filestream. 
//			Then logs to an output file based on the search commands 
//          given from a new input file.
//
//
// If there is no input file, it write error messages to screen and the output file.
//
// The program then writes a summary of 
// its findings to an output file.
//

#include <fstream>   // for basic file i/o
#include <iostream>  // for cout
#include <iomanip>   // for formatting manipulators
#include <string>    // for string variable   
#include <climits>   // for INT_MAX
#include <cassert>   // for assert for debugging
using namespace std; // to put all of the above things in scope
const int SIZE = 100; // this is the constant total # of cells in each array, making indexes 0 through 99


// these functions have info where their code is
void outputID (ofstream& out);
void InitializeIntArray (int Array[]);
void InitializeStringArray (string Array[]);
void ReadInArrays (string License[], string Make[], string Model[], int Year[], ifstream& inFile, int NumCar);
void LicenseSearch (const string License[], const string Make[], const string Model[], const int Year[], ofstream& outFile, int NumCar, string SearchData);
void MakeSearch (const string License[], const string Make[], const string Model[], const int Year[], ofstream& outFile, int NumCar, string SearchData);


int main() {

	ifstream inFile;                  // declares an 1st input
	ifstream inFile2;                 // declares an 2nd input
	ofstream outFile;                 // declares an output
	outFile << fixed << showpoint;    // for formatting

	
	inFile.open("VehicleData.txt");    // tells where to get data for array
	inFile2.open("Searches.txt");        // tells where to get data for commands
	outFile.open("Log.txt");		   // tells where to put data
    	
	// If the input files does not exist, this will detect that.
	// We handle that by printing an error message and stopping the program.
	if ( (inFile.fail()) && (inFile2.fail())  ) {
		cout << "Search could not be carried out because data file not found: "   // Write an error message...
		     << "either VehicleData.txt or Search.txt"				  // including the file name.
             << endl                      // Bang "return"
		     << "Exiting now..." <<endl;  // Finish the message.
		outFile << "Report could not be formulated. Data file not found. Please try again with desired text file in the home directory." << endl; // writes error to file		
		return 1;
		}

	outputID (outFile);						// outputs some info, see below

    int NumCar = 0;							// sets Usage to be blank
	inFile.ignore(INT_MAX, ':');			// skips over extranious data
	inFile >> NumCar;						// gets usage
	assert(NumCar <= SIZE && NumCar >=0);   // makes sure useage isn't negative or larger than the array, else ends program
	inFile.ignore(INT_MAX, '\n');			// skips to newline
	inFile.ignore(INT_MAX, '\n');			// skips to newline
	// declare the arrays:
	string License[SIZE];
	string    Make[SIZE];
	string   Model[SIZE];
	int       Year[SIZE];

    InitializeStringArray (License);			// blanks the array to "xxx NO DATA xxx"
	InitializeStringArray (Make);		       	// blanks the array to "xxx NO DATA xxx"
	InitializeStringArray (Model);		     	// blanks the array to "xxx NO DATA xxx"
	InitializeIntArray(Year);					// blanks the array to 0s
 
 	ReadInArrays (License, Make, Model, Year, inFile, NumCar);;		// reads the arrays in from file

	// to see array in terminal for testing purposes (this is before commands)       
	int Idx=0; for (Idx=0; Idx < 25 ; Idx++) {  // adjust 25 when youw ant to see more
		cout << License[Idx] << " " << Make[Idx] << " " << Model[Idx] << " " << Year[Idx] << endl;}


	string Command       = "";      // declares variable for the command
	string SearchData    = "";      // declares variable for the data to be searched for

	int Leave= 0; // leaves loop after it is necissary
	
	//priming read
	getline(inFile2, Command,    '\t');
	getline(inFile2, SearchData, '\n');
	
	// this is the main loop to go through the script (second input file
	// and run the searches based on which command is entered
	while ((inFile) && (Leave==0)){ 
		if (Command == "license"){
			LicenseSearch (License, Make, Model, Year, outFile, NumCar, SearchData);
			getline(inFile2, Command,    '\t');
			getline(inFile2, SearchData, '\n');
		}
		else if (Command == "make"){
			MakeSearch (License, Make, Model, Year, outFile, NumCar, SearchData);
			getline(inFile2, Command,    '\t');
			getline(inFile2, SearchData, '\n');
		}
		else {
			Leave = 1; // leaves loop if input error
		}
	}

	inFile.close();							// closes input file
	inFile2.close();						// closes input file
	outFile.close();						// closes output file
	return 0;								// clears buffer
}
// END MAIN

/////////////////////////////////////////// outputID(ofstream& out)
// This function writes the student ID information and puts used cell info.
//
//	Parameters:
//		outFile         the filestream from the output textfile
//
//	Returns: info into ofstream and changed place in ofstream
//
//	Pre:  ofstream must be open     
//  Post: writes info to stream
//
//	Called by: main()
//	Calls:     none
////////////////////////////////////////////////////////////////////////
void outputID (ofstream& out) {
	out << "Programmer: Will Butler" << endl;  
	out << "CS 1044 Project 7 Fall 2001" << endl;
	out << endl;
	out << "------------------------------------------------------------" << endl; // these are the used cell spaces
}


/////////////////////////////////////////// InitializeStringArray (string Array[])
// This function puts xxx NO DATA xxx's for every array cell.
//
//	Parameters:
//		Array         the array that is being written to
//	
//		Idx			  the index, is incremented to write to the Array
//
//	Returns: String Array as all xxx NO DATA xxx cells
//
//	Pre:  array must be declared     
//  Post: writes xxx NO DATA xxx's to every cell of the array
//
//	Called by: main()
//	Calls:     none
////////////////////////////////////////////////////////////////////////
void InitializeStringArray (string Array[]) {
	int Idx;
	for (Idx=0; Idx < SIZE; Idx++) {
		Array[Idx] = "xxx NO DATA xxx";  // xxx NO DATA xxx was chosen bc it is easily identified as not the right answer
	}
		
}

/////////////////////////////////////////// InitializeIntArray (int Array[])
// This function puts 0's for every array cell.
//
//	Parameters:
//		Array         the array that is being written to
//	
//		Idx			  the index, is incremented to write to the Array
//
//	Returns: Int Array as all 0 cells
//
//	Pre:  array must be declared     
//  Post: writes 0's to every cell of the array
//
//	Called by: main()
//	Calls:     none
////////////////////////////////////////////////////////////////////////
void InitializeIntArray (int Array[]) {
	int Idx;
	for (Idx=0; Idx < SIZE; Idx++) {
		Array[Idx] = 0;					// 0 was chosen bc the year can't be 0
	}
		
}

/////////////////////////////////////////// ReadInArrays(string License[], string Make[], string Model[], int Year[], ifstream& inFile, int NumCar)
// This reads the data from the first input file and puts it into 
// four parallel arrays: License[], Make[], Model[], and Year[].
//
//	Parameters:
//		License[],
//		Make[],
//		Model[],
//		Year[]	      the arrays that are being written to, all strings except Year[] is an int
//		NumCar		  number of used cells
//
//		Idx			  the index, is incremented to write to the arrays
//		TempLicense, TempMake, TempModel, TempYear
//					  temporary storage spaces to read in data to
//
//	Returns: Four parrallel arrays: License[], Make[], Model[], and Year[]
//		     with data up till NumCar			
//
//	Pre: arrays must be declared, ifstream must be open, NumCar must have correct value    
//  Post: writes to all four arrays
//
//	Called by: main()
//	Calls:     none
////////////////////////////////////////////////////////////////////////
void ReadInArrays (string License[], string Make[], string Model[], int Year[], ifstream& inFile, int NumCar) {
	int Idx  = 0;
	string TempLicense = "";
	string TempMake    = "";
	string TempModel   = "";
    int    TempYear    = 0;    

	//priming read
	getline(inFile, TempLicense, '\t');
	getline(inFile, TempMake   , '\t');
	getline(inFile, TempModel  , '\t');
	inFile >> TempYear;
	inFile.ignore(INT_MAX,'\n');
	
	// this is the main read in loop
	while ((inFile) && (Idx < NumCar)){
		License[Idx] = TempLicense;
		Make[Idx]    = TempMake;
		Model[Idx]   = TempModel;
		Year[Idx]    = TempYear;
		getline(inFile, TempLicense, '\t');
		getline(inFile, TempMake   , '\t');
		getline(inFile, TempModel  , '\t');
		inFile >> TempYear;
		inFile.ignore(INT_MAX,'\n');
		Idx++;                         // increments the counter
	}
 }

////// LicenseSearch (const string License[], const string Make[], const string Model[], const int Year[], ofstream& outFile, int NumCar, string SearchData)
//  main() calls this if Command=="license" so this processes the license data. 
//  This searches for the license, and if it is found it returns the first data on the car,
//  if not it returns an error message.
//
//	Parameters:
//		License[]	  the constant array being searched for specific data
//		Make[],
//		Model[],
//		Year[]	      constant arrays that are used to output if license is found
//		outFile		  the output file to be written to
//		NumCar		  number of used cells
//		SearchData    data that is compared to License[] in the loop
//
//		Idx			  the index, is incremented to search the array
//		Found		  if it changes to 1, the loop is exited.. acts like a testing statement; so if 
//					  one license is found, that will be the only one outputed
//
//	Returns: data into the output file			
//
//	Pre:  arrays must be declared, ofstream must be open, NumCar and SearchData must have correct values    
//  Post: returns info about car with searched license number if found, else
//		  returns an error
//
//	Called by: main()
//	Calls:     none
////////////////////////////////////////////////////////////////////////
void LicenseSearch (const string License[], const string Make[], const string Model[], const int Year[], ofstream& outFile, int NumCar, string SearchData){
	int Idx=0;
	int Found=0;     // this ends the loop if it is found
	
	outFile << "Searching for license: " << SearchData << endl;
			
	for (Idx=0; (Idx < SIZE && Found==0); Idx++){
		if ( (License[Idx]) == (SearchData)){
			outFile << License[Idx] <<"	" <<  Make[Idx] << "	"<< Model[Idx] << "	" <<Year[Idx] << endl; 
			outFile << "------------------------------------------------------------" << endl;
			Found=1;
		}
	}
	
	if (Found == 0){
			outFile << SearchData << " not found" << endl;
			outFile << "------------------------------------------------------------" << endl;
		}

		Idx++;

}

////////// MakeSearch (const string License[], const string Make[], const string Model[], const int Year[], ofstream& outFile, int NumCar, string SearchData)
//  main() calls this if Command=="make" so this processes the make data. 
//  This searches for the make, and if it is found it returns all license plates on this car.
//  if not it returns an error message.
//
//	Parameters:
//      Make[]		  the constant array being searched for specific data
//		License[],	  
//		Model[],
//		Year[]	      constant arrays that are used to output if license is found
//		outFile		  the output file to be written to
//		NumCar		  number of used cells
//		SearchData    data that is compared to Make[] in the loop
//
//		Idx			  the index, is incremented to search the array
//		Found		  after loop is tested, if this is still 0, then the error message is outputed
//
//	Returns: data into the output file			
//
//	Pre:  arrays must be declared, ofstream must be open, NumCar and SearchData must have correct values    
//  Post: returns info about car with searched make name if found, else
//		  returns an error
//
//	Called by: main()
//	Calls:     none
////////////////////////////////////////////////////////////////////////
void MakeSearch (const string License[], const string Make[], const string Model[], const int Year[], ofstream& outFile, int NumCar, string SearchData){
	int Idx=0;
	int Found=0; // after loop is tested, if this is still 0, then the error message is outputed
	
	outFile << "Searching for manufacturer: " << SearchData << endl;
			
	for (Idx=0; (Idx < SIZE ); Idx++){
		if ( (Make[Idx]) == (SearchData) ){
			outFile << License[Idx] << "	";
			Found=1;
		}
	}
	
	if (Found==0) {
			outFile << SearchData << " not found";
		}

		outFile << endl << "------------------------------------------------------------" << endl;
		Idx++;


}

  //////////////////////////////////////////////////////////////////////
//  On my honor:														//
//																		//
//    - I have not discussed the C++ language code in my program with	//
//      anyone other than my instructor or the teaching assistants		//
//      assigned to this course.										//
//																		//
//    - I have not used C++ language code obtained form another student,//
//      or any other unauthorized source, either modified or unmodified.//
//																		//
//    - If any C++ language code or documentation used in my program	//
//      was obtained from another source, such as a text book or course	//
//      notes, that has been clearly noted with a proper citation in	//
//      the comments of my program.										//
//																		//
//    - I have not designed this program in such a way as to defeat or	//
//      interfere with the normal operation of the Curator System.		//
//																		//
//     Will Butler														//
  //////////////////////////////////////////////////////////////////////
