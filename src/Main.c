#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
//our header files
#include "Global.h" 
#include "Args.h"
#include "SingleDataParser.h"
#include "PairDataParser.h"
#include "Helpers.h"

char *input;

singleFrequencyData singleFreqData[26];	// initialize array to length of alphabet for the single letter data
pairFrequencyData pairFreqData[676];	// initialize array length to the number of letter pairs the alphabet makes

int main( int argc, char* argv[] ) {

	parseArgs(argc, argv);				// call parsArgs in Args.c to check/determine if any options are called with ellfa

	if (globalArgs.help) {				// checks first to see if -h option is called and if it is displays the help message and exits
		printHelp();
		exit(EXIT_SUCCESS);		
	} 
	else if (globalArgs.versionInfo) {	// checks for -v to print the version info and exits
		printVersion();
		exit(EXIT_SUCCESS);
	}

	setUpFiles();						// checks user input options to see if they want to read/write to a file if the paths entered are valid

	//allocate memory for reading for a file
	if (globalArgs.inFilePath != NULL) {		
		size_t len;	

		fseek(globalArgs.inFile, 0, SEEK_END);
		len = ftell(globalArgs.inFile);
		rewind(globalArgs.inFile);		
		//Alocating memory for input
		input = (char*) malloc(sizeof(char) * len + 1);
		input[len]= '\0';

		if(input == NULL) {
			printf("Could not allocate memory");
			exit(EXIT_FAILURE);
		}

		fread(input, sizeof(char), len, globalArgs.inFile);
		fclose(globalArgs.inFile);		

	}
	else {
		input = getln(input);
	}

//All the buisness logic to parse the data
	initAlphabet(singleFreqData);		// calles function in helpers to see if a letter exists in the input
	initPairs(pairFreqData);
	
	makeAllLowercase(input);

	parseSingleData(input, singleFreqData);
	parsePairData(input, pairFreqData);

	if(globalArgs.outFilePath != NULL && (globalArgs.csv == 0)) {
		writeToFile(singleFreqData, pairFreqData);
	}
	else if (globalArgs.outFilePath != NULL && (globalArgs.csv != 0)) {
		writeToCsv(singleFreqData, pairFreqData);
	}
	else {
		printResults(singleFreqData, pairFreqData);
	}
	return 0;
}

