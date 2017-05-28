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

#define TEST_CARD_NAME "Adventurer"

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

	printf("----------------- Testing Card: %s ----------------\n", TEST_CARD_NAME);

	// ----------- TEST 1: > 2 Treasures Available --------------

	printf("TEST 1: At least two treasures available in deck\n");

	int playedCount1 = 1;
	int adventurerPosition1 = 0;
	int cardsGained1 = 2;

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
	memcpy(&postState, &preState, sizeof(struct gameState));

	printf("\tPlaying %s...\n", TEST_CARD_NAME);
	playAdventurer(&postState, thisPlayer);

	// checking hand count
	printf("\tTEST: thisPlayer hand count = %d, expected = %d\n", postState.handCount[thisPlayer], (preState.handCount[thisPlayer] + cardsGained1 - playedCount1));

	if (postState.handCount[thisPlayer] != (preState.handCount[thisPlayer] + cardsGained1 - playedCount1))
	{
		failedFlag = 1;
		//goto endTest1;
	}

	// checking deck count
	printf("\tTEST: thisPlayer deck count = %d, expected = %d\n", postState.deckCount[thisPlayer], (preState.deckCount[thisPlayer] - cardsGained1));

	if (postState.deckCount[thisPlayer] != (preState.deckCount[thisPlayer] - cardsGained1))
	{
		failedFlag = 1;
		//goto endTest1;
	}

	// cards drawn from deck the same as the new cards in the player's hand?
	printf("\tTEST: cards drawn from deck are the same as the new cards in the player's hand\n");

	for (i = preState.handCount[thisPlayer]; i < postState.handCount[thisPlayer]; i++)
	{
		for (k = preState.deckCount[thisPlayer] - 1; k >= postState.deckCount[thisPlayer]; k--)
		{
			if (postState.hand[thisPlayer][i] != preState.deck[thisPlayer][k])
			{
				failedFlag = 1;
				//goto endTest1;
			}
		}
	}

	// adventurer should not be in the player's hand
	printf("\tTEST: player's hand should not contain an adventurer card\n");

	if (postState.hand[thisPlayer][adventurerPosition1] != adventurer)
	{
		failedFlag = 1;
		//goto endTest1;
	}

	// playedCardCount should be +1
	printf("\tTEST: played count = %d, expected = %d\n", postState.playedCardCount, (preState.playedCardCount + playedCount1));

	if (postState.playedCardCount != (preState.playedCardCount + playedCount1))
	{
		failedFlag = 1;
		//goto endTest1;
	}

	// adventurer should be in played pile
	printf("\tTEST: adventurer should be in played cards\n");

	if (postState.playedCards[0] != adventurer)
	{
		failedFlag = 1;
		//goto endTest1;
	}

	// number of remaining actions correct?
	//printf("\tTEST: actions count = %d, expected = %d\n", postState.numActions, (preState.numActions - actionsUsed1));

	//if (postState.numActions != (preState.numActions - actionsUsed1))
	//{
	//	failedFlag = 1;
	//	goto endTest1;
	//}

endTest1:

	if (failedFlag == 0)
	{
		printf("TEST 1: SUCCESS\n");
	}
	else
	{
		printf("TEST 1: FAILED\n");
	}

	// ----------- TEST 2: < 2 Treasures Available --------------

	printf("TEST 2: zero treasures available in deck\n");

	initializeGame(numPlayers, kingdom, seed, &preState);

	failedFlag = 0;
	playedCount1 = 1;
	adventurerPosition1 = 0;
	cardsGained1 = 0;
	int cardsDrawn = 5;

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

	// setting player's deck to all estates
	for (i = 0; i < preState.deckCount[thisPlayer]; i++)
	{
		preState.deck[thisPlayer][i] = estate;
	}

	//preState.deck[thisPlayer][0] = gold;

	// copy the pre-test game state to the post-test game state
	memcpy(&postState, &preState, sizeof(struct gameState));

	printf("\tPlaying %s...\n", TEST_CARD_NAME);

	playAdventurer(&postState, thisPlayer);

	// players hand should not have changed
	printf("\tTEST: The unplayed cards in player's hand should be the same\n");

	printf("\tpreState hand contents: ");
	for (i = adventurerPosition1 + 1; i < preState.handCount[thisPlayer]; i++)
	{
		printf("%d ", preState.hand[thisPlayer][i]);
	}

	printf("\n");

	printf("\tpostState hand contents: ");
	for (i = 0; i < postState.handCount[thisPlayer]; i++)
	{
		printf("%d ", postState.hand[thisPlayer][i]);
	}

	printf("\n");

	for (i = adventurerPosition1 + 1; i < preState.handCount[thisPlayer]; i++)
	{
		for (k = 0; k < postState.handCount[thisPlayer]; k++)
		{
			if (postState.hand[thisPlayer][k] != preState.hand[thisPlayer][i])
			{
				failedFlag = 1;
				//goto endTest2;
			}
		}
	}

	// checking hand count
	printf("\tTEST: thisPlayer hand count = %d, expected = %d\n", postState.handCount[thisPlayer], (preState.handCount[thisPlayer] + cardsGained1 - playedCount1));

	if (postState.handCount[thisPlayer] != (preState.handCount[thisPlayer] + cardsGained1 - playedCount1))
	{
		failedFlag = 1;
		//goto endTest2;
	}

	// checking deck count
	printf("\tTEST: thisPlayer deck count = %d, expected = %d\n", postState.deckCount[thisPlayer], (preState.deckCount[thisPlayer] - cardsDrawn));

	if (postState.deckCount[thisPlayer] != (preState.deckCount[thisPlayer] - cardsDrawn))
	{
		failedFlag = 1;
		//goto endTest2;
	}

	// adventurer should not be in the player's hand
	printf("\tTEST: player's hand should not contain an adventurer card\n");

	if (postState.hand[thisPlayer][adventurerPosition1] != adventurer)
	{
		failedFlag = 1;
		//goto endTest2;
	}

	// playedCardCount should be +1
	printf("\tTEST: played count = %d, expected = %d\n", postState.playedCardCount, (preState.playedCardCount + playedCount1));

	if (postState.playedCardCount != (preState.playedCardCount + playedCount1))
	{
		failedFlag = 1;
		//goto endTest2;
	}

	// adventurer should be in played pile
	printf("\tTEST: adventurer should be in played cards\n");

	if (postState.playedCards[0] != adventurer)
	{
		failedFlag = 1;
		//goto endTest2;
	}

endTest2:

	if (failedFlag == 0)
	{
		printf("TEST 2: SUCCESS\n");
	}
	else
	{
		printf("TEST 2: FAILED\n");
	}

	// ----------- TESTS COMPLETE --------------

	printf("\n >>>>> Testing complete %s <<<<<\n\n", TEST_CARD_NAME);

	return 0;
}