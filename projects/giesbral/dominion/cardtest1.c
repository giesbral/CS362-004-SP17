/*
	Alex Giesbrecht - giesbral@oregonstate.edu
	4/26/2017
	CS362_400_S2017

	Unit Test for Smithy card
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TEST_CARD "Smithy"

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

	// ----------- TEST 1: 5 cards in player deck --------------

	printf("TEST 1: 5 cards in player deck\n");

	int playedCount = 1;
	int smithyPosition = 0;
	int cardsGained = 3;

	// setting up player's hand
	for (i = 0; i < MAX_HAND; i++)
	{
		preState.hand[thisPlayer][i] = -1;
	}

	preState.handCount[thisPlayer] = 5;
	
	// setting player's hand to all copper, except for smithy
	for (i = 0; i < preState.handCount[thisPlayer]; i++)
	{
		preState.hand[thisPlayer][i] = copper;
	}

	preState.hand[thisPlayer][smithyPosition] = smithy;

	// setting up player's deck
	for (i = 0; i < MAX_DECK; i++)
	{
		preState.deck[thisPlayer][i] = -1;
	}

	preState.deckCount[thisPlayer] = 5;

	// setting player's deck to entirely estates
	for (i = 0; i < preState.deckCount[thisPlayer]; i++)
	{
		preState.deck[thisPlayer][i] = estate;
	}

	// copy the pre-test game state to the post-test game state
	memcpy(&postState, &preState, sizeof(struct gameState));

	printf("\tPlaying Smithy...\n");
	playSmithy(&postState, smithyPosition, thisPlayer);

	// checking hand count
	printf("\tTEST: thisPlayer hand count = %d, expected = %d\n", postState.handCount[thisPlayer], (preState.handCount[thisPlayer] + cardsGained - playedCount));

	if (postState.handCount[thisPlayer] != (preState.handCount[thisPlayer] + cardsGained - playedCount))
	{
		failedFlag = 1;
		goto endTest;
	}

	// checking deck count
	printf("\tTEST: thisPlayer deck count = %d, expected = %d\n", postState.deckCount[thisPlayer], (preState.deckCount[thisPlayer] - cardsGained));

	if (postState.deckCount[thisPlayer] != (preState.deckCount[thisPlayer] - cardsGained))
	{
		failedFlag = 1;
		goto endTest;
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
				goto endTest;
			}
		}			
	}
	
	// smithy should not be in the player's hand
	printf("\tTEST: player's hand should not contain a smithy card\n");
				
	if (postState.hand[thisPlayer][smithyPosition] == smithy)
	{
		failedFlag = 1;
		goto endTest;
	}

	// playedCardCount should be +1
	printf("\tTEST: played count = %d, expected = %d\n", postState.playedCardCount, (preState.playedCardCount + playedCount));

	if (postState.playedCardCount != (preState.playedCardCount + playedCount))
	{
		failedFlag = 1;
		goto endTest;
	}
	
	// smithy should be in played pile
	printf("\tTEST: smithy should be in played cards\n");
	printf("\tPlayed card value = %d, expected %d\n", postState.playedCards[preState.playedCardCount], smithy);

	if (postState.playedCards[preState.playedCardCount] != smithy)
	{
		failedFlag = 1;
		goto endTest;
	}

endTest:
	
	if (failedFlag == 0)
	{
		printf("TEST 1: SUCCESS\n");
	}
	else
	{
		printf("TEST 1: FAILED\n");
	}

	// ----------- TEST 0: 0 cards in player deck --------------

	printf("TEST 2: 0 cards in player deck, 0 cards in discard\n");

	int failedFlag2 = 0;
	playedCount = 1;
	smithyPosition = 0;
	cardsGained = 0;

	// setting up player's hand
	for (i = 0; i < MAX_HAND; i++)
	{
		preState.hand[thisPlayer][i] = -1;
	}

	preState.handCount[thisPlayer] = 5;

	// setting player's hand to all copper, except for smithy
	for (i = 0; i < preState.handCount[thisPlayer]; i++)
	{
		preState.hand[thisPlayer][i] = copper;
	}

	preState.hand[thisPlayer][smithyPosition] = smithy;

	// setting up player's deck
	for (i = 0; i < MAX_DECK; i++)
	{
		preState.deck[thisPlayer][i] = -1;
	}

	preState.deckCount[thisPlayer] = 0;

	// copy the pre-test game state to the post-test game state
	memcpy(&postState, &preState, sizeof(struct gameState));

	printf("\tPlaying Smithy...\n");
	playSmithy(&postState, smithyPosition, thisPlayer);

	// checking hand count
	printf("\tTEST: thisPlayer hand count = %d, expected = %d\n", postState.handCount[thisPlayer], (preState.handCount[thisPlayer] + cardsGained - playedCount));

	if (postState.handCount[thisPlayer] != (preState.handCount[thisPlayer] + cardsGained - playedCount))
	{
		failedFlag2 = 1;
		goto endTest2;
	}

	// checking deck count
	printf("\tTEST: thisPlayer deck count = %d, expected = %d\n", postState.deckCount[thisPlayer], (preState.deckCount[thisPlayer] - cardsGained));

	if (postState.deckCount[thisPlayer] != (preState.deckCount[thisPlayer] - cardsGained))
	{
		failedFlag2 = 1;
		goto endTest2;
	}

	// smithy should not be in the player's hand
	printf("\tTEST: player's hand should not contain a smithy card\n");

	if (postState.hand[thisPlayer][smithyPosition] == smithy)
	{
		failedFlag2 = 1;
		goto endTest2;
	}

	// playedCardCount should be +1
	printf("\tTEST: played count = %d, expected = %d\n", postState.playedCardCount, (preState.playedCardCount + playedCount));

	if (postState.playedCardCount != (preState.playedCardCount + playedCount))
	{
		failedFlag2 = 1;
		goto endTest2;
	}

	// smithy should be in played pile
	printf("\tTEST: smithy should be in played cards\n");
	printf("\tPlayed card value = %d, expected %d\n", postState.playedCards[preState.playedCardCount], smithy);

	if (postState.playedCards[preState.playedCardCount] != smithy)
	{
		
		failedFlag2 = 1;
		goto endTest2;
	}

endTest2:

	if (failedFlag2 == 0)
	{
		printf("TEST 2: SUCCESS\n");
	}
	else
	{
		printf("TEST 2: FAILED\n");
	}

	// ----------- TESTS COMPLETE --------------

	printf("\n >>>>> Testing complete %s <<<<<\n\n", TEST_CARD);

	return 0;
}