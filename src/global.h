struct globalArgs_t {
   int csv;  //CSV option
   char* inFile;
   char* outFile;
   int help; //help option
   int versionInfo; //version option
};

struct FrequencyData {
	char* pair;
	int occurance;
	int frequency;

};

extern struct globalArgs_t globalArgs;
extern struct FrequencyData freqData;

void parseArgs(int numArgs, char* args[]);
