#include <stdio.h>
#ifndef GLOBAL
#define GLOBAL
#include "global.h"
#endif

int main( int argc, char* argv[] ) {
	parseArgs(argc, argv);
	if (globalArgs.help) {
		printf("Options:\n");
		printf("\t%s\t\t%s\n", "-c", "Print results in csv format.");
		printf("\t%s\t\t%s\n", "-f file", "Read the text from 'file'.");
		printf("\t%s\t\t%s\n", "-h", "Display this help messgae.");
		printf("\t%s\t\t%s\n", "-o file", "Write the results 'file'.");
		printf("\t%s\t\t%s\n", "-v", "Read the Display version info and exit.");
	}
}
