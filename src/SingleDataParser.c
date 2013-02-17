#include <stdio.h>
#include <string.h>
#include "Args.h"
#include "Global.h" 
#include "SingleDataParser.h"

int totalSingleCount = 0;

static void findSingleTotal (singleFrequencyData *singleData) {
	for (int i = 0; i < 26; i++) {
		totalSingleCount += singleData[i].occurance;
	}	
}

static void findSingleFrequency(singleFrequencyData *singleData) {
	for (int i = 0; i < 26; i++) {
		singleData[i].frequency = ((double)singleData[i].occurance / totalSingleCount) * 100;
	}
}

void parseSingleData(char *input, singleFrequencyData *singleData){
	for (int i = 0; input[i] != '\0'; i++) {
		for (int j = 0; j<26; j++) {			
			if(input[i] == singleData[j].letter) {
				singleData[j].occurance ++;
			}
		}
	}
	findSingleTotal(singleData);
	findSingleFrequency(singleData);
}

