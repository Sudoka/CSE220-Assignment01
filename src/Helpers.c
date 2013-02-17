#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Global.h"
#include "SingleDataParser.h"
#include "PairDataParser.h"

void writeToFile(singleFrequencyData *singleFreqData, pairFrequencyData *pairFreqData) {

	globalArgs.outFile = fopen(globalArgs.outFilePath, "w");

	if(globalArgs.outFile == NULL) {
		printf("ellfa: could not open: %s\n",globalArgs.outFilePath);
		exit(EXIT_FAILURE);
	}

	fprintf(globalArgs.outFile, "%d letters\n",totalSingleCount );
	for (int i = 0; i <26; i++) {
		fprintf(globalArgs.outFile, "%c",singleFreqData[i].letter);
		fprintf(globalArgs.outFile, "%10d",  singleFreqData[i].occurance);
		fprintf(globalArgs.outFile, "%10.5f\n", singleFreqData[i].frequency);
	}
	fprintf(globalArgs.outFile, "%d digraphs\n", totalPairCount);
	for (int i = 0; i <676; i++) {
		fprintf(globalArgs.outFile, "%s", pairFreqData[i].pair);
		fprintf(globalArgs.outFile, "%9d", pairFreqData[i].occurance);
		fprintf(globalArgs.outFile, " %.5f\n", pairFreqData[i].frequency);

	}
	fclose(globalArgs.outFile);
}

void writeToCsv(singleFrequencyData *singleFreqData, pairFrequencyData *pairFreqData) {

	globalArgs.outFile = fopen(globalArgs.outFilePath, "w");

	if(globalArgs.outFile == NULL) {
		printf("could not open: %s\n",globalArgs.outFilePath);
		exit(EXIT_FAILURE);
	}

	fprintf(globalArgs.outFile, "%d,\"letters\"\n", totalSingleCount);

	for (int i =0; i<26; i++) {
		fprintf(globalArgs.outFile, "\"%c\",",singleFreqData[i].letter);
		fprintf(globalArgs.outFile, "%d,",singleFreqData[i].occurance);
		fprintf(globalArgs.outFile, "%.5f\n", singleFreqData[i].frequency);
	}

	fprintf(globalArgs.outFile, "%d,\"digraphs\"\n", totalPairCount);

	for (int i = 0; i<676; i++) {
		fprintf(globalArgs.outFile, "\"%s\",",pairFreqData[i].pair);
		fprintf(globalArgs.outFile, "%d,",pairFreqData[i].occurance);
		fprintf(globalArgs.outFile, "%.5f\n", pairFreqData[i].frequency);
	}
}

void printResults(singleFrequencyData *singleFreqData, pairFrequencyData *pairFreqData) {
	printf("%d letters\n",totalSingleCount );
	for (int i = 0; i <26; i++) {
		printf("%c%10d%10.5f\n",singleFreqData[i].letter, singleFreqData[i].occurance, singleFreqData[i].frequency);
	}
	printf("%d diagraphs\n", totalPairCount);
	for (int i = 0; i <676; i++) {
		printf("%s%9d %.5f\n",pairFreqData[i].pair, pairFreqData[i].occurance, pairFreqData[i].frequency);
	}
}

void makeAllLowercase(char* str) {
	for (int i = 0; str[i] != '\0'; i++) {
		str[i] = tolower(str[i]);
	}
}

void initAlphabet(singleFrequencyData *singleFreqData) {
	for (int i = 'a'; i<= 'z'; i++) {		
		singleFreqData[i-'a'].letter = (char) i;
	}
}

void initPairs(pairFrequencyData *pairFreqData) {
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

char *getln(char *line)
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

void printHelp() {
	printf("Usage: ellfa [option]...\n");
	printf("Read English language text and calculate letter frequencies.\n\n");
	printf("Options:\n");
	printf("\t%s\t\t%s\n", "-c", "Print results in csv format.");
	printf("\t%s\t\t%s\n", "-f file", "Read the text from 'file'.");
	printf("\t%s\t\t%s\n", "-h", "Display this help messgae.");
	printf("\t%s\t\t%s\n", "-o file", "Write the results 'file'.");
	printf("\t%s\t\t%s\n", "-v", "Read the Display version info and exit.");
}

void printVersion() {
	printf("ellfa: version 1.0 (2013.1.16)\n");
	printf("Brian Blanchard <brian.blanchard@webfilings.com> and Brittney Russell <bsrussell15@gmail.com>\n");
}