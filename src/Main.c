#include <stdio.h>
#include <stdlib.h>
#ifndef GLOBAL
#define GLOBAL
#include "global.h"
#endif

char* input;

void printHelp() {
	printf("Options:\n");
	printf("\t%s\t\t%s\n", "-c", "Print results in csv format.");
	printf("\t%s\t\t%s\n", "-f file", "Read the text from 'file'.");
	printf("\t%s\t\t%s\n", "-h", "Display this help messgae.");
	printf("\t%s\t\t%s\n", "-o file", "Write the results 'file'.");
	printf("\t%s\t\t%s\n", "-v", "Read the Display version info and exit.");
}

int main( int argc, char* argv[] ) {	
	parseArgs(argc, argv);

	if (globalArgs.help) {
		printHelp();
		exit(EXIT_SUCCESS);		
	} 
	else if (globalArgs.inFilePath !=NULL) {
		size_t len;
		globalArgs.inFile = fopen(globalArgs.inFilePath, "r");

		if(globalArgs.inFile == NULL) {
			fprintf(stderr, "File does not exist: %s\n", globalArgs.inFilePath);
			return 1;
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
		input = (char*) malloc(10000);
		fgets(input, 10000, stdin);
		free(input);
	}

	printf("%s", input);

	return 0;

}

