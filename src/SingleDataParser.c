#include <stdio.h>
#include <string.h>
#include "Args.h"
#include "Global.h" 
#include "SingleDataParser.h"

int totalSingleCount = 0;

static void findSingleTotal (singleFrequencyData *singleData) {					// this loop finds total # of letters to calc. frequency
	for (int i = 0; i < 26; i++) {
		totalSingleCount += singleData[i].occurance;
	}	
}

static void findSingleFrequency(singleFrequencyData *singleData) {				// this loop calculates the frequncy of each letter used
	for (int i = 0; i < 26; i++) {
		singleData[i].frequency = ((float)singleData[i].occurance / (float)totalSingleCount) * 100;
	}
}

void parseSingleData(char *input, singleFrequencyData *singleData){				// this loop calculates the occurene of each letter and calls function to find freqency 
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

