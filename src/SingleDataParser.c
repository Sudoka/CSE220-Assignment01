#include <stdio.h>
#include <string.h>
#include "Args.h"
#include "global.h" 

static int total;

void parseSingleData(char *input, singleFrequencyData *singleData){

	for(int i = 0; i <= 26; i++){
		for(int j= 0; j!= '\0'; j++){
			if(strcmp(input[j], singleData[i].letter[0]) == 0){
				singleData[i].occurance ++;
				
			}

		}
	}

}

static void findTotal(singleFrequencyData *singleData){
	for(int i = 0; i<=26; i++){
		if(singleData[i].occurance != 0){
			total += singleData[i].occurance;
		}
	}
}

void findFrequency(singleFrequencyData *singleData){
	for(int i = 0; i <=26; i++){
		singleData[i].frequency = singleData[i].occurance / total;
	}

}
