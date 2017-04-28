/*
Alex Giesbrecht - giesbral@oregonstate.edu
4/26/2017
CS362_400_S2017

Unit Test for function isGameOver()
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TEST_FUNCTION "isGameOver()"
#define TEST_COUNT 5

int main() {

	struct gameState preState, postState;
	int kingdom[10] = { adventurer, smithy, village, outpost, sea_hag, mine, cutpurse, tribute, embargo, minion };

	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
	int badCount = 0;
	int failed = 0;
	int gameOver;
	int i, j, k;

	// 0 == failure, 1 == success
	int results[TEST_COUNT] = 0;

	// initialize game state
	initializeGame(numPlayers, kingdom, seed, &preState);

	printf("----------------- Testing Function: %s ----------------\n", TEST_FUNCTION);

	// ----------- TEST 1: Supply Count Province = 0, Supply Pile Counts = 0 --------------

	printf("TEST 1: Supply Count Province = 0, Supply Pile Counts = 0\n");

	// initialize game state
	initializeGame(numPlayers, kingdom, seed, &preState);

	// set supply pile counts
	for (i = 0; i <= treasure_map; i++)
	{
		preState.supplyCount[i] = 0;
	}

	printf("Testing Game Over...\n");
	gameOver = isGameOver(&preState);

	// check if gameOver is correct
	if (gameOver == 1)
	{
		results[1] = 1;
		printf("TEST 2: SUCCESS\n");
	}
	else
	{
		printf("TEST 2: FAILED\n");
	}

	// ----------- TEST 2: Supply Count Province = 0; Supply Pile Counts = initial values --------------

	printf("TEST 2: Supply Count Province = 0; Supply Pile Counts = initial values\n");

	// initialize game state
	initializeGame(numPlayers, kingdom, seed, &preState);

	// set province counts
	preState.supplyCount[province] = 0;

	printf("Testing Game Over...\n");
	gameOver = isGameOver(&preState);

	// check if gameOver is correct
	if (gameOver == 1)
	{
		results[1] = 1;
		printf("TEST 2: SUCCESS\n");
	}
	else
	{
		printf("TEST 2: FAILED\n");
	}

	// ----------- TEST 3: Supply Count Province = initial values; Supply Pile Counts = 0 --------------

	printf("TEST 3: Supply Count Province = 0; Supply Pile Counts = initial values\n");

	// initialize game state
	initializeGame(numPlayers, kingdom, seed, &preState);

	// set supply pile counts
	for (i = 0; i <= treasure_map; i++)
	{
		if (i != province)
		{
			preState.supplyCount[i] = 0;
		}
	}

	printf("Testing Game Over...\n");
	gameOver = isGameOver(&preState);

	// check if gameOver is correct
	if (gameOver == 1)
	{
		results[2] = 1;
		printf("TEST 3: SUCCESS\n");
	}
	else
	{
		printf("TEST 3: FAILED\n");
	}

	// ----------- TEST 4: Supply Count Province = initial values; Supply Pile Counts = initial values --------------

	printf("TEST 4: Supply Count Province = initial values; Supply Pile Counts = initial values\n");

	// initialize game state
	initializeGame(numPlayers, kingdom, seed, &preState);

	// copy the pre-test game state to the post-test game state
	memcopy(&postState, &preState, sizeof(struct gameState));

	printf("Testing Game Over...\n");
	gameOver = isGameOver(&preState);

	// check if gameOver is correct
	if (gameOver == 0)
	{
		// test supply pile counts
		for (i = 0; i <= treasure_map; i++)
		{
			if (preState.supplyCount[i] != postState.supplyCount[i])
			{
				badCount = 1;
			}
		}

		if (badCount == 0)
		{
			results[3] = 1;
			printf("TEST 4: SUCCESS\n");
		}
		else
		{
			printf("TEST 4: FAILED\n");
		}
	}
	else
	{
		printf("TEST 4: FAILED\n");
	}

	// ----------- TEST 5: All combinations of 3 empty supply piles --------------

	printf("TEST 5: All combinations of 3 empty supply piles\n");

	// initialize game state
	initializeGame(numPlayers, kingdom, seed, &preState);
	
	// tests every combination of 3 empty supply piles when province is not empty
	// should fail with current implementation of Game Over
	// whenever Treasure Map and/or Sea Hag is one of the empty piles (
	
	printf("Testing Game Over...\n");

	int preStateProvinceCount = preState.supplyCount[province];

	for (i = 0; i <= treasure_map; i++)
	{
		for (j = 0; j <= treasure_map; j++)
		{
			for (k = 0; k <= treasure_map; k++)
			{
				preState.supplyCount[i] = 0;
				preState.supplyCount[j] = 0;
				preState.supplyCount[k] = 0;

				preState.supplyCount[province] = preStateProvinceCount;

				gameOver = isGameOver(&preState);

				// check if gameOver is correct
				if (gameOver == 0)
				{
					failed = 1;
					goto endLoop;
				}
			}
		}
	}
		
	endLoop:
	
	if (failed == 1)
	{
		printf("TEST 5: FAILED\n");
	}
	else
	{
		results[3] = 1;
		printf("TEST 5: SUCCESS\n");
	}

	// ----------- TESTS COMPLETE --------------

	printf("\n >>>>> Testing complete %s <<<<<\n", TEST_FUNCTION);

	printf("\n >>>>> Results Summary %s <<<<<\n", TEST_FUNCTION);
	for (i = 0; i < TEST_COUNT; i++)
	{
		if (results[i] == 1)
		{
			printf("TEST %d: SUCCESS\n", i + 1);
		}
		else
		{
			printf("TEST %d: FAILED\n", i + 1);
		}
	}

	printf("\n");

	return 0;
}