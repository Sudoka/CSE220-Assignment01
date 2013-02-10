#include <stdio.h>

struct globalArgs_t {
   int csv;  //CSV option
   char* inFilePath;
   FILE* inFile;
   char* outFileName;
   FILE* outFile;
   int help; //help option
   int versionInfo; //version option
};

struct pairFrequencyData {
	char* pair;
	int occurance;
	int frequency;

};

extern struct globalArgs_t globalArgs;
extern struct pairFrequencyData freqData;

void parseArgs(int numArgs, char* args[]);
