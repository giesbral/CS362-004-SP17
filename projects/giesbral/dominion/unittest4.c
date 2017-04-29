/*
	Alex Giesbrecht - giesbral@oregonstate.edu
	4/26/2017
	CS362_400_S2017

	Unit Test for function numHandCards()
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TEST_FUNCTION "numHandCards()"
#define TEST_COUNT 2

int main() {

	struct gameState preState, postState;
	int kingdom[10] = { adventurer, smithy, village, outpost, sea_hag, mine, cutpurse, tribute, embargo, minion };
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
	int count;
	int i;

	// 0 == failure, 1 == success
	int results[TEST_COUNT] = { 0 };

	printf("----------------- Testing Function: %s ----------------\n", TEST_FUNCTION);

	// ----------- TEST 1: handCount = 0 --------------

	printf("TEST 1: handCount = 0\n");

	// initialize game state
	initializeGame(numPlayers, kingdom, seed, &preState);
	
	// set whoseTurn
	preState.whoseTurn = thisPlayer;

	// set hand counts for current player
	preState.handCount[thisPlayer] = 0;

	// copy the pre-test game state to the post-test game state
	memcpy(&postState, &preState, sizeof(struct gameState));

	printf("\tTesting numHandCards...\n");
	count = numHandCards(&preState);

	// check if handCount is correct
	if (count == 0)
	{
		printf("\tthisPlayer hand count = %d, expected = %d\n", postState.handCount[thisPlayer], preState.handCount[thisPlayer]);

		if (postState.handCount[thisPlayer] == preState.handCount[thisPlayer])
		{
			results[0] = 1;
			printf("TEST 1: SUCCESS\n");
		}
		else
		{
			printf("TEST 1: FAILED\n");
		}		
	}
	else
	{
		printf("TEST 1: FAILED\n");
	}

	printf("\n");

	// ----------- TEST 2: handCount =  initialized values --------------

	printf("TEST 2: handCount = initialized values\n");

	// initialize game state
	initializeGame(numPlayers, kingdom, seed, &preState);

	// set whoseTurn
	preState.whoseTurn = thisPlayer;

	// copy the pre-test game state to the post-test game state
	memcpy(&postState, &preState, sizeof(struct gameState));

	printf("\tTesting numHandCards...\n");
	count = numHandCards(&postState);

	// check if handCount is correct
	printf("\tthisPlayer hand count = %d, expected = %d\n", postState.handCount[thisPlayer], preState.handCount[thisPlayer]);
	if (postState.handCount[thisPlayer] == preState.handCount[thisPlayer])
	{
		results[1] = 1;
		printf("TEST 2: SUCCESS\n");
	}
	else
	{
		printf("TEST 2: FAILED\n");
	}

	printf("\n");

	// ----------- TESTS COMPLETE --------------

	printf("\n >>>>> Testing complete %s <<<<<\n", TEST_FUNCTION);

	printf("\n >>>>> Results Summary %s <<<<<\n", TEST_FUNCTION);
	for (i = 0; i < TEST_COUNT; i++)
	{
		if (results[i] == 1)
		{
			printf("\tTEST %d: SUCCESS\n", i + 1);
		}
		else
		{
			printf("\tTEST %d: FAILED\n", i + 1);
		}
	}

	printf("\n");

	return 0;
}