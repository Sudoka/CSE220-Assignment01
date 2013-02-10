#include <unistd.h>
#ifndef GLOBAL
#define GLOBAL
#include "global.h"
#endif

static const char *optString = "cf:ho:v";

struct globalArgs_t globalArgs;

void parseArgs(int numArgs, char* args[]) {
	int opt = 0;

	globalArgs.csv = 0;
	globalArgs.inFilePath = NULL;
	globalArgs.outFileName = NULL;
	globalArgs.help = 0;
	globalArgs.versionInfo = 0;

	opt = getopt( numArgs, args, optString );
	while( opt != -1 ) {
		switch( opt ) {
			case 'c':	
				globalArgs.csv = 1;
				break;
				
			case 'f':
				globalArgs.inFilePath = optarg;
				break;
				
			case 'o':				
				globalArgs.outFileName = optarg;				
				break;
				
			case 'v':
				globalArgs.versionInfo = 1;
				break;
				
			case 'h':
				globalArgs.help = 1;
			default:			
				break;
		}
		
		opt = getopt( numArgs, args, optString );
	}
}