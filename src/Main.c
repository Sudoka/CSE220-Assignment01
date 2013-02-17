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

singleFrequencyData singleFreqData[26];
pairFrequencyData pairFreqData[676];

int main( int argc, char* argv[] ) {

	parseArgs(argc, argv);

	if (globalArgs.help) {
		printHelp();
		exit(EXIT_SUCCESS);		
	} 
	else if (globalArgs.versionInfo) {
		printVersion();
		exit(EXIT_SUCCESS);
	}
	else if (globalArgs.inFilePath !=NULL) {		
		size_t len;
		globalArgs.inFile = fopen(globalArgs.inFilePath, "r");

		if(globalArgs.inFile == NULL) {
			printf("ellfa: could not open %s\n", globalArgs.inFilePath);
			return EXIT_FAILURE;
		}

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
	initAlphabet(singleFreqData);
	initPairs(pairFreqData);
	
	makeAllLowercase(input);

	parseSingleData(input, singleFreqData);
	parsePairData(input, pairFreqData);

	if(globalArgs.outFilePath != NULL && (globalArgs.csv == 0)) {
		writeToFile(singleFreqData, pairFreqData);
	}
	else if (globalArgs.outFilePath != NULL && (globalArgs.csv > 0)) {
		writeToCsv(singleFreqData, pairFreqData);
	}
	else {
		printResults(singleFreqData, pairFreqData);
	}
	return 0;
}

