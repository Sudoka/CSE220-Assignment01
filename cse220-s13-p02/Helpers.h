#include "Global.h"
#ifndef HELPERS_H
#define HELPERS_H

//makes all files in helpers.c available for other source code files to call

void writeToFile(singleFrequencyData *singleFreqData, pairFrequencyData *pairFreqData);
void writeToCsv(singleFrequencyData *singleFreqData, pairFrequencyData *pairFreqData);
void printResults(singleFrequencyData *singleFreqData, pairFrequencyData *pairFreqData);

void makeAllLowercase(char* str);

void initAlphabet(singleFrequencyData *singleFreqData);
void initPairs(pairFrequencyData *pairFreqData);

char *getln(char *line);

void printHelp();
void printVersion();

void setUpFiles();
FILE *seeIfFileExits(char *path, char *option);

#endif