/*
	Alex Giesbrecht - giesbral@oregonstate.edu
	4/26/2017
	CS362_400_S2017

	Unit Test for function shuffle()
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TEST_FUNCTION "shuffle()"
#define TEST_COUNT 5

int main() {

	struct gameState preState, postState;
	int kingdom[10] = { adventurer, smithy, village, outpost, sea_hag, mine, cutpurse, tribute, embargo, minion };

	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
	int shuffled;
	int t;
	int i;
	
	// 0 == failure, 1 == success
	int results[TEST_COUNT] = { 0 };

	printf("----------------- Testing Function: %s ----------------\n", TEST_FUNCTION);

	// ----------- TEST 1: thisPlayer deckCount = -1 --------------

	printf("TEST 1: thisPlayer deckCount = -1\n");

	// initialize game state
	initializeGame(numPlayers, kingdom, seed, &preState);

	// set the deckCount for thisPlayer
	preState.deckCount[thisPlayer] = -1;

	// copy the pre-test game state to the post-test game state
	memcpy(&postState, &preState, sizeof(struct gameState));

	printf("\tShuffling cards...\n");
	t = shuffle(thisPlayer, &postState);

	printf("\tshuffle exit code = %d, expected %d\n", t, -1);
	if (t == -1)
	{
		results[0] = 1;
		printf("TEST 1: SUCCESS\n");
	}
	else
	{
		printf("TEST 1: FAILED\n");
	}

	printf("\n");

	// ----------- TEST 2: thisPlayer deckCount = 0 --------------
	
	// This test should fail.
	// Shuffle is set up to return -1 if the player's deck count is less than one. 
	// However, having a deck count of zero is a legitimate game state
	// supported by the game's rules: 
	// https://boardgamegeek.com/thread/363917/bureaucrat-can-you-have-draw-deck-zero
	// https://boardgames.stackexchange.com/questions/7018/what-does-masquerade-do-when-you-have-no-cards-in-hand-library-or-discard
	// deckCount = 0 should be supported by the shuffle function.

	printf("TEST 2: thisPlayer deckCount = 0\n");

	// initialize game state
	initializeGame(numPlayers, kingdom, seed, &preState);

	// set the deckCount for thisPlayer
	preState.deckCount[thisPlayer] = 0;

	// remove all cards in player deck
	for (i = 0; i < MAX_DECK; i++)
	{
			preState.deck[thisPlayer][i] = -1;
	}

	// copy the pre-test game state to the post-test game state
	memcpy(&postState, &preState, sizeof(struct gameState));

	printf("\tShuffling cards...\n");
	t = shuffle(thisPlayer, &postState);

	printf("\tshuffle exit code = %d, expected %d\n", t, 0);
	if (t != -1)
	{
		// test that the player's deck count remains the same
		printf("\tthisPlayer deck count = %d, expected = %d\n", postState.deckCount[thisPlayer], preState.deckCount[thisPlayer]);

		if (preState.deckCount[thisPlayer] == postState.deckCount[thisPlayer])
		{
			// check that there are still no cards in the deck
			printf("\tpreState deck order = ");

			for (i = 0; i < preState.deckCount[thisPlayer]; i++)
			{
				printf("%d ", preState.deck[thisPlayer][i]);
			}

			printf("\n");

			printf("\tpostState deck order = ");

			for (i = 0; i < postState.deckCount[thisPlayer]; i++)
			{
				printf("%d ", postState.deck[thisPlayer][i]);
			}

			printf("\n");

			for (i = 0; i < preState.deckCount[thisPlayer]; i++)
			{
				if (preState.deck[thisPlayer][i] != postState.deck[thisPlayer][i])
				{
					shuffled = 1;
				}
			}
			
			// if the deck count == 0, the shuffle function shouldn't shuffle anything, even if the deck has cards in it
			if (shuffled != 1)
			{
				results[1] = 1;
				printf("TEST 2: SUCCESS\n");
			}
			else
			{
				printf("TEST 2: FAILED\n");
			}
		}
		else
		{
			printf("TEST 2: FAILED\n");
		}
	}
	else
	{
		printf("TEST 2: FAILED\n");
	}

	printf("\n");

	// ----------- TEST 3: thisPlayer deckCount = 1 --------------

	printf("TEST 3: thisPlayer deckCount = 1\n");

	// initialize game state
	initializeGame(numPlayers, kingdom, seed, &preState);

	// set the deckCount for thisPlayer
	preState.deckCount[thisPlayer] = 1;

	// remove all cards in player deck
	for (i = 0; i < MAX_DECK; i++)
	{
		preState.deck[thisPlayer][i] = -1;
	}

	// set cards in player deck
	for (i = 0; i < preState.deckCount[thisPlayer]; i++)
	{
		if ((i % 2) == 0)
		{
			preState.deck[thisPlayer][i] = copper;
		}
		else
		{
			preState.deck[thisPlayer][i] = estate;
		}
	}

	// copy the pre-test game state to the post-test game state
	memcpy(&postState, &preState, sizeof(struct gameState));

	printf("\tShuffling cards...\n");
	t = shuffle(thisPlayer, &postState);

	if (t != -1)
	{
		// test that the player's deck count remains the same
		printf("\tthisPlayer deck count = %d, expected = %d\n", postState.deckCount[thisPlayer], preState.deckCount[thisPlayer]);

		if (preState.deckCount[thisPlayer] == postState.deckCount[thisPlayer])
		{
			// check that there is only one card in the deck and the card remains the same
			printf("\tPre shuffle deck contents and order = ");

			for (i = 0; i < preState.deckCount[thisPlayer]; i++)
			{
				printf("%d ", preState.deck[thisPlayer][i]);
			}

			printf("\n");

			printf("\tPost Shuffle deck contents and order = ");

			for (i = 0; i < postState.deckCount[thisPlayer]; i++)
			{
				printf("%d ", postState.deck[thisPlayer][i]);
			}

			printf("\n");

			for (i = 0; i < preState.deckCount[thisPlayer]; i++)
			{
				if (postState.deck[thisPlayer][i] != postState.deck[thisPlayer][i])
				{
					shuffled = 1;
				}
			}

			// if the deck count == 1, the shuffle function shouldn't change the card in the deck
			if (shuffled != 1)
			{
				results[2] = 1;
				printf("TEST 3: SUCCESS\n");
			}
			else
			{
				printf("TEST 3: FAILED\n");
			}
		}
		else
		{
			printf("TEST 3: FAILED\n");
		}
	}
	else
	{
		printf("TEST 3: FAILED\n");
	}

	printf("\n");

	// ----------- TEST 4: thisPlayer deckCount = 10 ---------------

	printf("TEST 4: thisPlayer deckCount = 10\n");

	// initialize game state
	initializeGame(numPlayers, kingdom, seed, &preState);

	// set the deckCount for thisPlayer
	preState.deckCount[thisPlayer] = 10;

	// set cards in player deck
	for (i = 0; i < preState.deckCount[thisPlayer]; i++)
	{
		if ((i%2) == 0)
		{
			preState.deck[thisPlayer][i] = copper;
		}
		else
		{
			preState.deck[thisPlayer][i] = estate;
		}
	}

	// copy the pre-test game state to the post-test game state
	memcpy(&postState, &preState, sizeof(struct gameState));

	printf("\tShuffling cards...\n");
	t = shuffle(thisPlayer, &postState);

	if (t != -1)
	{
		// test that the player's deck count remains the same
		printf("\tthisPlayer deck count = %d, expected = %d\n", postState.deckCount[thisPlayer], preState.deckCount[thisPlayer]);

		if (preState.deckCount[thisPlayer] == postState.deckCount[thisPlayer])
		{
			// check the deck order
			printf("\tPre shuffle deck contents and order = ");

			for (i = 0; i < preState.deckCount[thisPlayer]; i++)
			{
				printf("%d ", preState.deck[thisPlayer][i]);
			}

			printf("\n");

			printf("\tPost Shuffle deck contents and order = ");

			for (i = 0; i < postState.deckCount[thisPlayer]; i++)
			{
				printf("%d ", postState.deck[thisPlayer][i]);
			}

			printf("\n");

			shuffled = 0;

			for (i = 0; i < preState.deckCount[thisPlayer]; i++)
			{
				if (preState.deck[thisPlayer][i] != postState.deck[thisPlayer][i])
				{
					shuffled = 1;
				}
			}

			// The shuffled function should change the order of cards in the deck
			if (shuffled == 1)
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
	}
	else
	{
		printf("TEST 4: FAILED\n");
	}

	printf("\n");

	// ----------- TEST 5: thisPlayer deckCount = 501 --------------
	
	// this test should fail
	// the function does not validate deck count to see whether 
	// or not it's greater than the size of the deck array

	printf("TEST 5: thisPlayer deckCount = 501\n");

	// initialize game state
	initializeGame(numPlayers, kingdom, seed, &preState);

	// set the deckCount for thisPlayer
	preState.deckCount[thisPlayer] = 501;

	// copy the pre-test game state to the post-test game state
	memcpy(&postState, &preState, sizeof(struct gameState));

	printf("\tShuffling cards...\n");
	t = shuffle(thisPlayer, &postState);

	printf("\tshuffle exit code = %d, expected %d\n", t, -1);
	if (t == -1)
	{
		results[4] = 1;
		printf("TEST 5: SUCCESS\n");
	}
	else
	{
		printf("TEST 5: FAILED\n");
	}

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