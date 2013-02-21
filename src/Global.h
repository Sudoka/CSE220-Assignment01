#include <stdio.h>
#ifndef GLOBAL
#define GLOBAL

struct globalArgs_t {            
   int csv;          //CSV option
   char* inFilePath;
   FILE* inFile;
   char* outFilePath;
   FILE* outFile;
   int help;         //help option
   int versionInfo;  //version option
};

 typedef struct {                // allows other files to call singleFrequencyData
   char letter;
   int occurance;
   float frequency;
} singleFrequencyData;

typedef struct {                 // allows other files to call pairFrequencyData
	char pair[3];
	int occurance;
	float frequency;
} pairFrequencyData;

extern struct globalArgs_t globalArgs;    // allows other files to use the variable globalArgs

#endif
