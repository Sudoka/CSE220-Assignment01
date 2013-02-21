#include "Global.h"

#ifndef SINGLEDATAPARSER_H	
#define SINGLEDATAPARSER_H

// allows other files to call the function in SingleDataPArser.c


extern int totalSingleCount;
void parseSingleData(char *input, singleFrequencyData *singleData);		

#endif