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

 typedef struct {
   char letter;
   int occurance;
   int frequency;
} singleFrequencyData;

typedef struct {   
	char* pair;
	int occurance;
	int frequency;
} pairFrequencyData ;

extern struct globalArgs_t globalArgs;

void parseArgs(int numArgs, char* args[]);
