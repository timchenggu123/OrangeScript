#include <iostream>
#include <fstream>
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::ifstream;

int main (int argc, char *argv[]){
	string inputFileName = argv[1];
	ifstream inputFile;
	
	//try opening the input file
	inputFile.open(inputFileName);
	if (!inputFile) {
		std::cerr << "Error: Input file cannot be opened" << endl;
		exit(1);
	}



    return 0;
}