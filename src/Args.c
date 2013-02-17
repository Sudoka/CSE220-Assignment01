#include <string.h>
#include <stdlib.h>
#include "Global.h"
#include "Args.h"

struct globalArgs_t globalArgs;

char *optarg;

void parseArgs(int numArgs, char* args[]) {
	if(numArgs == 1) {
		return;
	}

	globalArgs.csv = 0;
	globalArgs.inFilePath = NULL;
	globalArgs.outFilePath = NULL;
	globalArgs.help = 0;
	globalArgs.versionInfo = 0;

	for (int i = 1; i < numArgs; i++) {			
		if((strcmp(args[i], "-c")) == 0) {
			globalArgs.csv = 1;
		}
		else if((strcmp(args[i], "-h")) == 0) {
			globalArgs.help = 1;
		}
		else if((strcmp(args[i], "-v")) == 0) {
			globalArgs.versionInfo = 1;
		}
		else if((strcmp(args[i], "-f")) == 0) {
			if (i == numArgs-1) {
				printf("expecting argument following -f\n");
				exit(EXIT_FAILURE);
			}
			optarg = args[i+1];

			if(optarg[0] == '-') {
				printf("ellfa: requires argument\n");
				exit(EXIT_FAILURE);
			}
			else {
				globalArgs.inFilePath = optarg;
			}			
		}
		else if((strcmp(args[i], "-o")) == 0) {
			if (i == numArgs-1) {
				printf("expecting argument following -o\n");
				exit(EXIT_FAILURE);
			}
			optarg = args[i+1];

			if(optarg[0] == '-') {
				printf("ellfa: requires argument\n");
				exit(EXIT_FAILURE);
			}
			else {
				globalArgs.outFilePath = optarg;
			}
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