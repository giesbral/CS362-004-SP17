/*
	Alex Giesbrecht - giesbral@oregonstate.edu
	4/26/2017
	CS362_400_S2017

	Unit Test for Adventurer card
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TEST_CARD "Adventurer"

int main() {

	struct gameState preState, postState;
	int kingdom[10] = { adventurer, smithy, village, outpost, sea_hag, mine, cutpurse, tribute, embargo, minion };
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
	int i, k;

	// 0 == failure, 1 == success
	int failedFlag = 0;

	// initialize game state
	initializeGame(numPlayers, kingdom, seed, &preState);

	printf("----------------- Testing Card: %s ----------------\n", TEST_CARD);

	// ----------- TEST 1: > 2 Treasures Available --------------

	printf("TEST 1: At least two treasures available in deck\n");

	const int actionsUsed1 = 1;
	const int playedCount1 = 1;
	const int adventurerPosition1 = 0;
	const int cardsGained1 = 2;

	// setting up player's hand
	for (i = 0; i < MAX_HAND; i++)
	{
		preState.hand[thisPlayer][i] = -1;
	}

	preState.handCount[thisPlayer] = 5;

	// setting player's hand to all copper, except for adventurer
	for (i = 0; i < preState.handCount[thisPlayer]; i++)
	{
		preState.hand[thisPlayer][i] = copper;
	}

	preState.hand[thisPlayer][adventurerPosition1] = adventurer;

	// setting up player's deck
	for (i = 0; i < MAX_DECK; i++)
	{
		preState.deck[thisPlayer][i] = -1;
	}

	preState.deckCount[thisPlayer] = 5;

	// setting player's deck to all gold
	for (i = 0; i < preState.deckCount[thisPlayer]; i++)
	{
		preState.deck[thisPlayer][i] = gold;
	}

	// copy the pre-test game state to the post-test game state
	memcopy(&postState, &preState, sizeof(struct gameState));

	printf("Playing %s...\n", TEST_CARD);
	playAdventurer(&preState, adventurerPosition1, thisPlayer);

	// checking hand count
	printf("TEST: thisPlayer hand count = %d, expected = %d\n", postState.handCount[thisPlayer], (preState.handCount[thisPlayer] + cardsGained1 - playedCount1));

	if (postState.handCount[thisPlayer] != (preState.handCount[thisPlayer] + cardsGained1 - playedCount1))
	{
		failedFlag = 1;
		goto endTest1;
	}

	// checking deck count
	printf("TEST: thisPlayer deck count = %d, expected = %d\n", postState.deckCount[thisPlayer], (preState.deckCount[thisPlayer] - cardsGained1));

	if (postState.deckCount[thisPlayer] != (preState.deckCount[thisPlayer] - cardsGained1))
	{
		failedFlag = 1;
		goto endTest1;
	}

	// cards drawn from deck the same as the new cards in the player's hand?
	printf("TEST: cards drawn from deck are the same as the new cards in the player's hand\n");

	for (i = preState.handCount[thisPlayer]; i < postState.handCount[thisPlayer]; i++)
	{
		for (k = preState.deckCount[thisPlayer] - 1; k >= postState.deckCount[thisPlayer]; k--)
		{
			if (postState.hand[thisPlayer][i] != preState.deck[thisPlayer][k])
			{
				failedFlag = 1;
				goto endTest1;
			}
		}
	}

	// adventurer should not be in the player's hand
	printf("TEST: player's hand should not contain an adventurer card\n");

	if (postState.hand[thisPlayer][adventurerPosition1] != adventurer)
	{
		failedFlag = 1;
		goto endTest1;
	}

	// playedCardCount should be +1
	printf("TEST: played count = %d, expected = %d\n", postState.playedCardCount, (preState.playedCardCount + playedCount1));

	if (postState.playedCardCount != (preState.playedCardCount + playedCount1))
	{
		failedFlag = 1;
		goto endTest1;
	}

	// adventurer should be in played pile
	printf("TEST: adventurer should be in played cards\n");

	if (postState.playedCards[0] != adventurer)
	{
		failedFlag = 1;
		goto endTest1;
	}

	// number of remaining actions correct?
	printf("TEST: actions count = %d, expected = %d\n", postState.numActions, (preState.numActions - actionsUsed1));

	if (postState.numActions != (preState.numActions - actionsUsed1))
	{
		failedFlag = 1;
		goto endTest1;
	}

endTest1:

	if (failedFlag == 0)
	{
		printf("TEST %s: SUCCESS\n", TEST_CARD);
	}
	else
	{
		printf("TEST %s: FAILED\n", TEST_CARD);
		return 0;
	}

//	// ----------- TEST 2: < 2 Treasures Available --------------
//
//	printf("TEST 2: less than two treasures available in deck\n");
//
//	// thread id
//	pthread_t ptid;
//
//	int completed = -1;
//	int pid;
//
//	// setting up player's hand
//	for (i = 0; i < MAX_HAND; i++)
//	{
//		preState.hand[thisPlayer][i] = -1;
//	}
//
//	preState.handCount[thisPlayer] = 5;
//
//	// setting player's hand to all copper, except for adventurer
//	for (i = 0; i < preState.handCount[thisPlayer]; i++)
//	{
//		preState.hand[thisPlayer][i] = copper;
//	}
//
//	preState.hand[thisPlayer][adventurerPosition1] = adventurer;
//
//	// setting up player's deck
//	for (i = 0; i < MAX_DECK; i++)
//	{
//		preState.deck[thisPlayer][i] = -1;
//	}
//
//	preState.deckCount[thisPlayer] = 5;
//
//	// setting player's deck to all estates
//	for (i = 0; i < preState.deckCount[thisPlayer]; i++)
//	{
//		preState.deck[thisPlayer][i] = estate;
//	}
//
//	preState.deck[thisPlayer][0] = gold;
//
//	// copy the pre-test game state to the post-test game state
//	memcopy(&postState, &preState, sizeof(struct gameState));
//
//	printf("Playing %s...\n", TEST_CARD);
//
//	pthread_create(&ptid, NULL, playAdventurer, NULL);
//	completed = playAdventurer(&preState, adventurerPosition1, thisPlayer);
//
//endTest2:
//
//	if (failedFlag == 0)
//	{
//		printf("TEST %s: SUCCESS\n", TEST_CARD);
//	}
//	else
//	{
//		printf("TEST %s: FAILED\n", TEST_CARD);
//
//	}

	// ----------- TESTS COMPLETE --------------

	printf("\n >>>>> Testing complete %s <<<<<\n\n", TEST_CARD);

	return 0;
}