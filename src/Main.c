#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//our header files
#include "Global.h" 
#include "Args.h"
#include "SingleDataParser.h"
#include "PairDataParser.h"

char *input;

singleFrequencyData singleFreqData[26];
pairFrequencyData pairFreqData[676];


static void writeToFile() {
	globalArgs.outFile = fopen(globalArgs.outFilePath, "a+");

	fprintf(globalArgs.outFile, "%d letters\n",totalSingleCount );
	for (int i = 0; i <26; i++) {
		fprintf(globalArgs.outFile, "%c%9d%.5f\n",singleFreqData[i].letter, singleFreqData[i].occurance, singleFreqData[i].frequency);
	}
	fprintf(globalArgs.outFile, "%d digraphs\n", totalPairCount);
	for (int i = 0; i <676; i++) {
		fprintf(globalArgs.outFile, "%s%9d%.5f\n",pairFreqData[i].pair, pairFreqData[i].occurance, pairFreqData[i].frequency);
	}
	fclose(globalArgs.outFile);
}

static void printResults() {
	printf("%d letters\n",totalSingleCount );
	for (int i = 0; i <26; i++) {
		printf("%c%9d %.5f\n",singleFreqData[i].letter, singleFreqData[i].occurance, singleFreqData[i].frequency);
	}
	printf("%d diagraphs\n", totalPairCount);
	for (int i = 0; i <676; i++) {
		printf("%s%9d %.5f\n",pairFreqData[i].pair, pairFreqData[i].occurance, pairFreqData[i].frequency);
	}
}

static void makeAllLowercase(char* str) {
	for (int i = 0; str[i] != '\0'; i++) {
		str[i] = tolower(str[i]);
	}
}

static void initAlphabet() {
	for (int i = 'a'; i<= 'z'; i++) {		
		singleFreqData[i-'a'].letter = (char) i;
	}
}

static void initPairs() {
	int count = 0;
	while (count <676) {
		for(int i ='a'; i<='z'; i++) {
			for (int j = 'a'; j <= 'z' ; j++) {			
				pairFreqData[count].pair[0] = (char) i;
				pairFreqData[count].pair[1] = (char) j;
				pairFreqData[count].pair[2] = '\0';
				count++;
			}
		}

	}
}

static char *getln(char *line)
{
    char *tmp = NULL;
    size_t size = 0, index = 0;
    int ch = EOF;

    while (ch) {
        ch = getc(stdin);

        if (ch == EOF || ch == '\n') {
            ch = 0;
        }
      
        if (size <= index) {
            size += 64;
            tmp = realloc(line, size);
            if (!tmp) {
                free(line);
                line = NULL;
                break;
            }
            line = tmp;
        }

        line[index++] = ch;
    }

    return line;
}

static void printHelp() {
	printf("Options:\n");
	printf("\t%s\t\t%s\n", "-c", "Print results in csv format.");
	printf("\t%s\t\t%s\n", "-f file", "Read the text from 'file'.");
	printf("\t%s\t\t%s\n", "-h", "Display this help messgae.");
	printf("\t%s\t\t%s\n", "-o file", "Write the results 'file'.");
	printf("\t%s\t\t%s\n", "-v", "Read the Display version info and exit.");
}

static void printVersion() {
	printf("ellfa: version 1.0 (2013.1.16)\n");
	printf("Brian Blanchard <brian.blanchard@webfilings.com> and Brittney Russell <bsrussell15@gmail.com>\n");
}

int main( int argc, char* argv[] ) {

	parseArgs(argc, argv);

	if (globalArgs.help) {
		printHelp();
		exit(EXIT_SUCCESS);		
	} 
	else if(globalArgs.versionInfo) {
		printVersion();
		exit(EXIT_SUCCESS);
	}
	else if (globalArgs.inFilePath !=NULL) {		
		size_t len;
		globalArgs.inFile = fopen(globalArgs.inFilePath, "r");

		if(globalArgs.inFile == NULL) {
			fprintf(stderr, "ellfa: could not open %s\n", globalArgs.inFilePath);
			return EXIT_FAILURE;
		}

		fseek(globalArgs.inFile, 0, SEEK_END);
		len = ftell(globalArgs.inFile);
		rewind(globalArgs.inFile);
		printf("%d\n", (int)len);

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
		input = getln(input);
	}

//All the buisness logic to parse the data
	initAlphabet();
	initPairs();
	
	makeAllLowercase(input);

	parseSingleData(input, singleFreqData);
	parsePairData(input, pairFreqData);

	// printResults();
	writeToFile();


	return 0;
}

