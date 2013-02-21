#include "Global.h"

#ifndef PAIR_DATA_PARSER_H
#define PAIR_DATA_PARSER_H

// allows other source code files to call "public" information in PairsDaraParser file

extern int totalPairCount;
void parsePairData(char *input, pairFrequencyData *pairData);

#endif