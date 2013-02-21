#include <string.h>
#include <stdlib.h>
#include "Global.h"
#include "Args.h"

// this file checks and displays any input arguments the user could enter

struct globalArgs_t globalArgs;									// declares struct defined in global.c to allow use in this file

char *optarg;

void parseArgs(int numArgs, char* args[]) {
	if(numArgs == 1) {											// if there are no arguments continue running.
		return;
	}

	// initialize local variables
	globalArgs.csv = 0;
	globalArgs.inFilePath = NULL;
	globalArgs.outFilePath = NULL;
	globalArgs.help = 0;
	globalArgs.versionInfo = 0;

	for (int i = 1; i < numArgs; i++) {							// this for loop runs through the user input and checks for specific options
		if((strcmp(args[i], "-c")) == 0) {						
			globalArgs.csv = 1;
		}
		else if((strcmp(args[i], "-h")) == 0) {					
			globalArgs.help = 1;
		}
		else if((strcmp(args[i], "-v")) == 0) {					
			globalArgs.versionInfo = 1;
		}
		else if((strcmp(args[i], "-f")) == 0) {					// checks to see if -f option is entereed
			if (i == numArgs-1) {								// if there is no file after -f to read from display error message
				printf("expecting argument following -f\n");
				exit(EXIT_FAILURE);
			}
			optarg = args[i+1];

			if(optarg[0] == '-') {
				printf("ellfa: requires argument\n");			// if user enteres - an no arguement, display error message 
				exit(EXIT_FAILURE);
			}
			else {
				globalArgs.inFilePath = optarg;					// if -f is entered correctly with a file afterit, read from file
			}
		}
		else if((strcmp(args[i], "-o")) == 0) {					// checks to see if -o option is entereed
			if (i == numArgs-1) {								// if there is no file after -o to write to display error message
				printf("expecting argument following -o\n");
				exit(EXIT_FAILURE);
			}
			optarg = args[i+1];

			if(optarg[0] == '-') {								// if user enteres - an no arguement, display error message 
				printf("ellfa: requires argument\n");
				exit(EXIT_FAILURE);
			}
			else {
				globalArgs.outFilePath = optarg;				// if -o is entered correctly with a file afterit, write to designated file
			}
		}
		else if(args[i][0] == '-' && (args[i][1] != 'c' && args[i][1] != 'h' && args[i][1] != 'v' && args[i][1] != 'f' && args[i][1] != 'o')) {
			printf("ellfa: invalid option\n");					// if the user enters in a - with an unvalid argument display error message
			exit(EXIT_FAILURE);
		}
		else {
			if (optarg == NULL) {								
				printf("ellfa: unexpected string\n");
				exit(EXIT_FAILURE);
			}
			else if (strcmp(optarg, args[i])) {					
				printf("ellfa: unexpected string\n");
				exit(EXIT_FAILURE);
			}
		}
	}
}