#include <string.h>
#include "global.h"
#include "PairDataParser.h"

int totalPairCount = 0;

static void findPairTotal (pairFrequencyData *pairData) {
	for (int i = 0; i < 676; i++) {
		totalPairCount += pairData[i].occurance;
	}     	
}

static void findFrequency(pairFrequencyData *pairData) {
	for (int i = 0; i < 676; i++) {
		pairData[i].frequency = (pairData[i].occurance / totalPairCount) * 100;
	}
}

void parsePairData(char *input, pairFrequencyData *pairData) {	
	for (int i = 1; input[i] != '\0'; i++) {

		char inputPairs[3];
		inputPairs[0] = input[i-1];
		inputPairs[1] = input[i];
		inputPairs[2] = '\0';		

		for (int j = 0; j < 676; j++)
		{	
			if((strcmp(inputPairs, pairData[j].pair)) == 0) {
				pairData[j].occurance++;
			}
		}
	}
	findPairTotal(pairData);
	findFrequency(pairData);
}




