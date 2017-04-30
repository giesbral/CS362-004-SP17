/*
	Alex Giesbrecht - giesbral@oregonstate.edu
	4/26/2017
	CS362_400_S2017

	Unit Test for function fullDeckCount()
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TEST_FUNCTION "fullDeckCount()"
#define TEST_COUNT 8

int main() {

	struct gameState preState, postState;
	int kingdom[10] = { adventurer, smithy, village, outpost, sea_hag, mine, cutpurse, tribute, embargo, minion };

	int seed = 1000;
	int testCard;
	int numPlayers = 2;
	int thisPlayer = 0;
	int changed = 0;
	int count;
	int expectedCount;
	int i;

	// 0 == failure, 1 == success
	int results[TEST_COUNT] = { 0 };

	printf("----------------- Testing Function: %s ----------------\n", TEST_FUNCTION);

	// ----------- TEST 1: thisPlayer handCount, discardCount, deckCount = 0; card = adventurer --------------

	printf("TEST 1: thisPlayer handCount, discardCount, deckCount = 0; testCard = adventurer\n");

	// initialize game state
	initializeGame(numPlayers, kingdom, seed, &preState);

	// set test card
	testCard = adventurer;

	expectedCount = 0;

	// remove all cards in player deck
	for (i = 0; i < MAX_DECK; i++)
	{
		preState.deck[thisPlayer][i] = -1;
		preState.hand[thisPlayer][i] = -1;
		preState.discard[thisPlayer][i] = -1;
	}

	// set the deckCount for thisPlayer
	preState.handCount[thisPlayer] = 0;
	preState.discardCount[thisPlayer] = 0;
	preState.deckCount[thisPlayer] = 0;

	// copy the pre-test game state to the post-test game state
	memcpy(&postState, &preState, sizeof(struct gameState));

	printf("\tCounting instances of testCard...\n");
	count = fullDeckCount(thisPlayer, testCard, &postState);

	// check if count is correct
	printf("\tadventurer count = %d, expected %d\n", count, expectedCount);
	if (count == 0)
	{
		// check if deck counts are the same
		printf("\tthisPlayer deck count = %d, expected = %d\n", postState.deckCount[thisPlayer], preState.deckCount[thisPlayer]);
		printf("\tthisPlayer hand count = %d, expected = %d\n", postState.handCount[thisPlayer], preState.handCount[thisPlayer]);
		printf("\tthisPlayer discard count = %d, expected = %d\n", postState.discardCount[thisPlayer], preState.discardCount[thisPlayer]);

		if (preState.deckCount[thisPlayer] == postState.deckCount[thisPlayer] && 
			preState.handCount[thisPlayer] == postState.handCount[thisPlayer] && 
			preState.discardCount[thisPlayer] == postState.discardCount[thisPlayer])
		{
			// check if deck contents are the same (just the first card in each, in this case)
			printf("\tChecking if deck contents are the same...\n");
			if (postState.deck[thisPlayer][0] == preState.deck[thisPlayer][0] &&
				postState.hand[thisPlayer][0] == preState.hand[thisPlayer][0] &&
				postState.discard[thisPlayer][0] == preState.discard[thisPlayer][0])
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
	}
	else
	{
		printf("TEST 1: FAILED\n");
	}

	printf("\n");

	// ----------- TEST 2: thisPlayer handCount = 1; discardCount, deckCount = 0, card = adventurer, card count = 1 (in hand) --------------

	printf("TEST 2: thisPlayer handCount = 1; discardCount, deckCount = 0, card = adventurer, card count = 1 (in hand)\n");

	// initialize game state
	initializeGame(numPlayers, kingdom, seed, &preState);

	// set test card
	testCard = adventurer;

	expectedCount = 1;

	// remove all cards in player deck
	for (i = 0; i < MAX_DECK; i++)
	{
		preState.deck[thisPlayer][i] = -1;
		preState.hand[thisPlayer][i] = -1;
		preState.discard[thisPlayer][i] = -1;
	}

	// set cards in player deck
	preState.hand[thisPlayer][0] = adventurer;

	// set the deck counts for thisPlayer
	preState.handCount[thisPlayer] = 1;
	preState.discardCount[thisPlayer] = 0;
	preState.deckCount[thisPlayer] = 0;

	// copy the pre-test game state to the post-test game state
	memcpy(&postState, &preState, sizeof(struct gameState));

	printf("\tCounting instances of testCard...\n");
	count = fullDeckCount(thisPlayer, testCard, &postState);

	// check if count is correct
	printf("\tadventurer count = %d, expected %d\n", count, expectedCount);
	if (count == 1)
	{

		// check if deck counts are the same
		printf("\tthisPlayer deck count = %d, expected = %d\n", postState.deckCount[thisPlayer], preState.deckCount[thisPlayer]);
		printf("\tthisPlayer hand count = %d, expected = %d\n", postState.handCount[thisPlayer], preState.handCount[thisPlayer]);
		printf("\tthisPlayer discard count = %d, expected = %d\n", postState.discardCount[thisPlayer], preState.discardCount[thisPlayer]);

		if (preState.deckCount[thisPlayer] == postState.deckCount[thisPlayer] &&
			preState.handCount[thisPlayer] == postState.handCount[thisPlayer] &&
			preState.discardCount[thisPlayer] == postState.discardCount[thisPlayer])
		{
			// check if deck contents are the same (just the first card in each, in this case)
			printf("\tChecking if deck contents are the same...\n");
			if (postState.deck[thisPlayer][0] == preState.deck[thisPlayer][0] &&
				postState.hand[thisPlayer][0] == preState.hand[thisPlayer][0] &&
				postState.discard[thisPlayer][0] == preState.discard[thisPlayer][0])
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

	// ----------- TEST 3: thisPlayer deckCount = 1; handCount, discardCount = 0, card = adventurer, card count = 1 (in deck) --------------

	printf("TEST 3: thisPlayer deckCount = 1; handCount, discardCount = 0, card = adventurer, card count = 1 (in deck)\n");

	// initialize game state
	initializeGame(numPlayers, kingdom, seed, &preState);

	// set test card
	testCard = adventurer;

	expectedCount = 1;

	// remove all cards in player deck
	for (i = 0; i < MAX_DECK; i++)
	{
		preState.deck[thisPlayer][i] = -1;
		preState.hand[thisPlayer][i] = -1;
		preState.discard[thisPlayer][i] = -1;
	}

	// set cards in player deck
	preState.deck[thisPlayer][0] = adventurer;

	// set the deck counts for thisPlayer
	preState.handCount[thisPlayer] = 0;
	preState.discardCount[thisPlayer] = 0;
	preState.deckCount[thisPlayer] = 1;

	// copy the pre-test game state to the post-test game state
	memcpy(&postState, &preState, sizeof(struct gameState));

	printf("\tCounting instances of testCard...\n");
	count = fullDeckCount(thisPlayer, testCard, &postState);

	// check if count is correct
	printf("\tadventurer count = %d, expected %d\n", count, expectedCount);
	if (count == 1)
	{
		// check if deck counts are the same
		printf("\tthisPlayer deck count = %d, expected = %d\n", postState.deckCount[thisPlayer], preState.deckCount[thisPlayer]);
		printf("\tthisPlayer hand count = %d, expected = %d\n", postState.handCount[thisPlayer], preState.handCount[thisPlayer]);
		printf("\tthisPlayer discard count = %d, expected = %d\n", postState.discardCount[thisPlayer], preState.discardCount[thisPlayer]);

		if (preState.deckCount[thisPlayer] == postState.deckCount[thisPlayer] &&
			preState.handCount[thisPlayer] == postState.handCount[thisPlayer] &&
			preState.discardCount[thisPlayer] == postState.discardCount[thisPlayer])
		{
			// check if deck contents are the same (just the first card in each, in this case)
			printf("\tChecking if deck contents are the same...\n");
			if (postState.deck[thisPlayer][0] == preState.deck[thisPlayer][0] &&
				postState.hand[thisPlayer][0] == preState.hand[thisPlayer][0] &&
				postState.discard[thisPlayer][0] == preState.discard[thisPlayer][0])
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

	// ----------- TEST 4: thisPlayer discardCount = 1; handCount, deckCount = 0, card = adventurer, card count = 1 (in discard) --------------

	printf("TEST 4: thisPlayer discardCount = 1; handCount, deckCount = 0, card = adventurer, card count = 1 (in discard)\n");

	// set test card
	testCard = adventurer;

	expectedCount = 1;

	// remove all cards in player deck
	for (i = 0; i < MAX_DECK; i++)
	{
		preState.deck[thisPlayer][i] = -1;
		preState.hand[thisPlayer][i] = -1;
		preState.discard[thisPlayer][i] = -1;
	}

	// set cards in player deck
	preState.discard[thisPlayer][0] = adventurer;

	// set the deck counts for thisPlayer
	preState.handCount[thisPlayer] = 0;
	preState.discardCount[thisPlayer] = 1;
	preState.deckCount[thisPlayer] = 0;

	// copy the pre-test game state to the post-test game state
	memcpy(&postState, &preState, sizeof(struct gameState));

	printf("\tCounting instances of testCard...\n");
	count = fullDeckCount(thisPlayer, testCard, &postState);

	// check if count is correct
	printf("\tadventurer count = %d, expected %d\n", count, expectedCount);
	if (count == 1)
	{
		// check if deck counts are the same
		printf("\tthisPlayer deck count = %d, expected = %d\n", postState.deckCount[thisPlayer], preState.deckCount[thisPlayer]);
		printf("\tthisPlayer hand count = %d, expected = %d\n", postState.handCount[thisPlayer], preState.handCount[thisPlayer]);
		printf("\tthisPlayer discard count = %d, expected = %d\n", postState.discardCount[thisPlayer], preState.discardCount[thisPlayer]);

		if (preState.deckCount[thisPlayer] == postState.deckCount[thisPlayer] &&
			preState.handCount[thisPlayer] == postState.handCount[thisPlayer] &&
			preState.discardCount[thisPlayer] == postState.discardCount[thisPlayer])
		{
			// check if deck contents are the same (just the first card in each, in this case)
			printf("\tChecking if deck contents are the same...\n");
			if (postState.deck[thisPlayer][0] == preState.deck[thisPlayer][0] &&
				postState.hand[thisPlayer][0] == preState.hand[thisPlayer][0] &&
				postState.discard[thisPlayer][0] == preState.discard[thisPlayer][0])
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

	// ----------- TEST 5: thisPlayer discardCount, handCount, deckCount = 5, card = adventurer, card count = 0 --------------

	printf("TEST 5: thisPlayer discardCount, handCount, deckCount = 5, card = adventurer, card count = 0\n");

	// initialize game state
	initializeGame(numPlayers, kingdom, seed, &preState);

	// set test card
	testCard = adventurer;

	expectedCount = 0;

	// remove all cards in player deck
	for (i = 0; i < MAX_DECK; i++)
	{
		preState.deck[thisPlayer][i] = -1;
		preState.hand[thisPlayer][i] = -1;
		preState.discard[thisPlayer][i] = -1;
	}

	// set the deck counts for thisPlayer
	preState.handCount[thisPlayer] = 5;
	preState.discardCount[thisPlayer] = 5;
	preState.deckCount[thisPlayer] = 5;

	// set cards in player decks
	for (i = 0; i < preState.deckCount[thisPlayer]; i++)
	{
		preState.deck[thisPlayer][i] = copper;
	}

	for (i = 0; i < preState.discardCount[thisPlayer]; i++)
	{
		preState.discard[thisPlayer][i] = copper;
	}

	for (i = 0; i < preState.handCount[thisPlayer]; i++)
	{
		preState.hand[thisPlayer][i] = copper;
	}

	// copy the pre-test game state to the post-test game state
	memcpy(&postState, &preState, sizeof(struct gameState));

	printf("\tCounting instances of testCard...\n");
	count = fullDeckCount(thisPlayer, testCard, &postState);

	// check if count is correct
	printf("\tadventurer count = %d, expected %d\n", count, expectedCount);
	if (count == 0)
	{
		// check if deck counts are the same
		printf("\tthisPlayer deck count = %d, expected = %d\n", postState.deckCount[thisPlayer], preState.deckCount[thisPlayer]);
		printf("\tthisPlayer hand count = %d, expected = %d\n", postState.handCount[thisPlayer], preState.handCount[thisPlayer]);
		printf("\tthisPlayer discard count = %d, expected = %d\n", postState.discardCount[thisPlayer], preState.discardCount[thisPlayer]);

		if (preState.deckCount[thisPlayer] == postState.deckCount[thisPlayer] &&
			preState.handCount[thisPlayer] == postState.handCount[thisPlayer] &&
			preState.discardCount[thisPlayer] == postState.discardCount[thisPlayer])
		{
			// check if deck contents are the same
			printf("\tChecking if deck contents are the same...\n");
			for (i = 0; i < preState.deckCount[thisPlayer]; i++)
			{
				if (postState.deck[thisPlayer][i] != preState.deck[thisPlayer][i])
				{
					changed = 1;
				}
			}

			if (changed == 0)
			{
				for (i = 0; i < preState.handCount[thisPlayer]; i++)
				{
					if (postState.hand[thisPlayer][i] != preState.hand[thisPlayer][i])
					{
						changed = 1;
					}
				}

				if (changed == 0)
				{
					for (i = 0; i < preState.discardCount[thisPlayer]; i++)
					{
						if (postState.discard[thisPlayer][i] != preState.discard[thisPlayer][i])
						{
							changed = 1;
						}
					}

					if (changed == 0)
					{
						results[4] = 1;
						printf("TEST 5: SUCCESS\n");
					}
					else
					{
						printf("TEST 5: FAILED\n");
					}
				}
				else
				{
					printf("TEST 5: FAILED\n");
				}
			}
			else
			{
				printf("TEST 5: FAILED\n");
			}
		}
		else
		{
			printf("TEST 5: FAILED\n");
		}
	}
	else
	{
		printf("TEST 5: FAILED\n");
	}

	printf("\n");

	// ----------- TEST 6: thisPlayer discardCount, handCount, deckCount = 5, card = adventurer, card count = 3 (one in each deck) --------------

	printf("TEST 6: thisPlayer discardCount, handCount, deckCount = 5, card = adventurer, card count = 3 (one in each deck)\n");

	// initialize game state
	initializeGame(numPlayers, kingdom, seed, &preState);

	// set test card
	testCard = adventurer;

	expectedCount = 3;

	// remove all cards in player deck
	for (i = 0; i < MAX_DECK; i++)
	{
		preState.deck[thisPlayer][i] = -1;
		preState.hand[thisPlayer][i] = -1;
		preState.discard[thisPlayer][i] = -1;
	}

	// set the deck counts for thisPlayer
	preState.handCount[thisPlayer] = 5;
	preState.discardCount[thisPlayer] = 5;
	preState.deckCount[thisPlayer] = 5;

	// set cards in player decks
	for (i = 0; i < preState.deckCount[thisPlayer]; i++)
	{
		preState.deck[thisPlayer][i] = copper;
	}

	for (i = 0; i < preState.discardCount[thisPlayer]; i++)
	{
		preState.discard[thisPlayer][i] = copper;
	}

	for (i = 0; i < preState.handCount[thisPlayer]; i++)
	{
		preState.hand[thisPlayer][i] = copper;
	}

	preState.deck[thisPlayer][0] = adventurer;
	preState.discard[thisPlayer][0] = adventurer;
	preState.hand[thisPlayer][0] = adventurer;

	// copy the pre-test game state to the post-test game state
	memcpy(&postState, &preState, sizeof(struct gameState));

	printf("\tCounting instances of testCard...\n");
	count = fullDeckCount(thisPlayer, testCard, &postState);

	// check if count is correct
	printf("\tadventurer count = %d, expected %d\n", count, expectedCount);
	if (count == 3)
	{
		// check if deck counts are the same
		printf("\tthisPlayer deck count = %d, expected = %d\n", postState.deckCount[thisPlayer], preState.deckCount[thisPlayer]);
		printf("\tthisPlayer hand count = %d, expected = %d\n", postState.handCount[thisPlayer], preState.handCount[thisPlayer]);
		printf("\tthisPlayer discard count = %d, expected = %d\n", postState.discardCount[thisPlayer], preState.discardCount[thisPlayer]);

		if (preState.deckCount[thisPlayer] == postState.deckCount[thisPlayer] &&
			preState.handCount[thisPlayer] == postState.handCount[thisPlayer] &&
			preState.discardCount[thisPlayer] == postState.discardCount[thisPlayer])
		{
			// check if deck contents are the same
			printf("\tChecking if deck contents are the same...\n");
			for (i = 0; i < preState.deckCount[thisPlayer]; i++)
			{
				if (postState.deck[thisPlayer][i] != preState.deck[thisPlayer][i])
				{
					changed = 1;
				}
			}

			if (changed == 0)
			{
				for (i = 0; i < preState.handCount[thisPlayer]; i++)
				{
					if (postState.hand[thisPlayer][i] != preState.hand[thisPlayer][i])
					{
						changed = 1;
					}
				}

				if (changed == 0)
				{
					for (i = 0; i < preState.discardCount[thisPlayer]; i++)
					{
						if (postState.discard[thisPlayer][i] != preState.discard[thisPlayer][i])
						{
							changed = 1;
						}
					}

					if (changed == 0)
					{
						results[5] = 1;
						printf("TEST 6: SUCCESS\n");
					}
					else
					{
						printf("TEST 6: FAILED\n");
					}
				}
				else
				{
					printf("TEST 6: FAILED\n");
				}
			}
			else
			{
				printf("TEST 6: FAILED\n");
			}
		}
		else
		{
			printf("TEST 6: FAILED\n");
		}
	}
	else
	{
		printf("TEST 6: FAILED\n");
	}

	printf("\n");

	// ----------- TEST 7: thisPlayer handCount, discardCount, deckCount = -1; card = adventurer --------------

	printf("TEST 7: thisPlayer handCount, discardCount, deckCount = -1; testCard = adventurer\n");

	// initialize game state
	initializeGame(numPlayers, kingdom, seed, &preState);

	// set test card
	testCard = adventurer;

	expectedCount = 0;

	// remove all cards in player deck
	for (i = 0; i < MAX_DECK; i++)
	{
		preState.deck[thisPlayer][i] = -1;
		preState.hand[thisPlayer][i] = -1;
		preState.discard[thisPlayer][i] = -1;
	}

	// set the deckCount for thisPlayer
	preState.handCount[thisPlayer] = -1;
	preState.discardCount[thisPlayer] = -1;
	preState.deckCount[thisPlayer] = -1;

	// copy the pre-test game state to the post-test game state
	memcpy(&postState, &preState, sizeof(struct gameState));

	printf("\tCounting instances of testCard...\n");
	count = fullDeckCount(thisPlayer, testCard, &postState);

	// check if count is correct
	printf("\tadventurer count = %d, expected %d\n", count, expectedCount);
	if (count == 0)
	{
		// check if deck counts are the same
		printf("\tthisPlayer deck count = %d, expected = %d\n", postState.deckCount[thisPlayer], preState.deckCount[thisPlayer]);
		printf("\tthisPlayer hand count = %d, expected = %d\n", postState.handCount[thisPlayer], preState.handCount[thisPlayer]);
		printf("\tthisPlayer discard count = %d, expected = %d\n", postState.discardCount[thisPlayer], preState.discardCount[thisPlayer]);

		if (preState.deckCount[thisPlayer] == postState.deckCount[thisPlayer] &&
			preState.handCount[thisPlayer] == postState.handCount[thisPlayer] &&
			preState.discardCount[thisPlayer] == postState.discardCount[thisPlayer])
		{
			// check if deck contents are the same (just the first card in each, in this case)
			printf("\tChecking if deck contents are the same...\n");
			if (postState.deck[thisPlayer][0] == preState.deck[thisPlayer][0] &&
				postState.hand[thisPlayer][0] == preState.hand[thisPlayer][0] &&
				postState.discard[thisPlayer][0] == preState.discard[thisPlayer][0])
			{
				results[6] = 1;
				printf("TEST 7: SUCCESS\n");
			}
			else
			{
				printf("TEST 7: FAILED\n");
			}
		}
		else
		{
			printf("TEST 7: FAILED\n");
		}
	}
	else
	{
		printf("TEST 7: FAILED\n");
	}

	printf("\n");

	// ----------- TEST 8: thisPlayer handCount, discardCount, deckCount = MAX_DECK + 1; card = adventurer --------------

	printf("TEST 8: thisPlayer handCount, discardCount, deckCount = MAX_DECK + 1; testCard = adventurer\n");

	// initialize game state
	initializeGame(numPlayers, kingdom, seed, &preState);

	// set test card
	testCard = adventurer;

	expectedCount = 0;

	// remove all cards in player deck
	for (i = 0; i < MAX_DECK; i++)
	{
		preState.deck[thisPlayer][i] = -1;
		preState.hand[thisPlayer][i] = -1;
		preState.discard[thisPlayer][i] = -1;
	}

	// set the deckCount for thisPlayer
	preState.handCount[thisPlayer] = MAX_DECK + 1;
	preState.discardCount[thisPlayer] = MAX_DECK + 1;
	preState.deckCount[thisPlayer] = MAX_DECK + 1;

	// copy the pre-test game state to the post-test game state
	memcpy(&postState, &preState, sizeof(struct gameState));

	printf("\tCounting instances of testCard...\n");
	count = fullDeckCount(thisPlayer, testCard, &postState);

	// check if count is correct
	printf("\tadventurer count = %d, expected %d\n", count, expectedCount);
	if (count == 0)
	{
		// check if deck counts are the same
		printf("\tthisPlayer deck count = %d, expected = %d\n", postState.deckCount[thisPlayer], preState.deckCount[thisPlayer]);
		printf("\tthisPlayer hand count = %d, expected = %d\n", postState.handCount[thisPlayer], preState.handCount[thisPlayer]);
		printf("\tthisPlayer discard count = %d, expected = %d\n", postState.discardCount[thisPlayer], preState.discardCount[thisPlayer]);

		if (preState.deckCount[thisPlayer] == postState.deckCount[thisPlayer] &&
			preState.handCount[thisPlayer] == postState.handCount[thisPlayer] &&
			preState.discardCount[thisPlayer] == postState.discardCount[thisPlayer])
		{
			// check if deck contents are the same (just the first card in each, in this case)
			printf("\tChecking if deck contents are the same...\n");
			if (postState.deck[thisPlayer][0] == preState.deck[thisPlayer][0] &&
				postState.hand[thisPlayer][0] == preState.hand[thisPlayer][0] &&
				postState.discard[thisPlayer][0] == preState.discard[thisPlayer][0])
			{
				results[7] = 1;
				printf("TEST 8: SUCCESS\n");
			}
			else
			{
				printf("TEST 8: FAILED\n");
			}
		}
		else
		{
			printf("TEST 8: FAILED\n");
		}
	}
	else
	{
		printf("TEST 8: FAILED\n");
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