#include <stdio.h>
#ifndef GLOBAL
#define GLOBAL

struct globalArgs_t {
   int csv;  //CSV option
   char* inFilePath;
   FILE* inFile;
   char* outFilePath;
   FILE* outFile;
   int help; //help option
   int versionInfo; //version option
};

 typedef struct {
   char letter;
   int occurance;
   double frequency;
} singleFrequencyData;

typedef struct {   
	char pair[3];
	int occurance;
	double frequency;
} pairFrequencyData;

extern struct globalArgs_t globalArgs;

#endif
