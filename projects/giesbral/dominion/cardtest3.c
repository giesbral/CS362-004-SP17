/*
Alex Giesbrecht - giesbral@oregonstate.edu
4/26/2017
CS362_400_S2017

Unit Test for Village card
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#define TEST_CARD "Village"

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

	const int actionsUsed = 2;
	const int actionsGained = 4;
	const int playedCount = 2;
	const int villagePosition1 = 0;
	const int villagePosition2 = 0;
	const int cardsGained = 2;


	printf("----------------- Testing Card: %s ----------------\n", TEST_CARD);

	// setting up player's hand
	for (i = 0; i < MAX_HAND; i++)
	{
		preState.hand[thisPlayer][i] = -1;
	}

	preState.handCount[thisPlayer] = 5;

	// setting player's hand to all copper, except for village
	for (i = 0; i < preState.handCount[thisPlayer]; i++)
	{
		preState.hand[thisPlayer][i] = copper;
	}

	preState.hand[thisPlayer][villagePosition1] = village;
	preState.hand[thisPlayer][villagePosition2] = village;

	// setting up player's deck
	for (i = 0; i < MAX_DECK; i++)
	{
		preState.deck[thisPlayer][i] = -1;
	}

	preState.deckCount[thisPlayer] = 5;

	// setting player's deck to entirely gold
	for (i = 0; i < preState.deckCount[thisPlayer]; i++)
	{
		preState.deck[thisPlayer][i] = gold;
	}

	// copy the pre-test game state to the post-test game state
	memcopy(&postState, &preState, sizeof(struct gameState));

	printf("Playing Village TWICE...\n");
	playVillage(&preState, villagePosition1, thisPlayer);
	playVillage(&preState, villagePosition2, thisPlayer);

	// checking hand count
	printf("TEST: thisPlayer hand count = %d, expected = %d\n", postState.handCount[thisPlayer], (preState.handCount[thisPlayer] + cardsGained - playedCount));

	if (postState.handCount[thisPlayer] != (preState.handCount[thisPlayer] + cardsGained - playedCount))
	{
		failedFlag = 1;
		goto endTest;
	}

	// checking deck count
	printf("TEST: thisPlayer deck count = %d, expected = %d\n", postState.deckCount[thisPlayer], (preState.deckCount[thisPlayer] - cardsGained));

	if (postState.deckCount[thisPlayer] != (preState.deckCount[thisPlayer] - cardsGained))
	{
		failedFlag = 1;
		goto endTest;
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
				goto endTest;
			}
		}
	}

	// village should not be in the player's hand
	printf("TEST: player's hand should not contain a village card\n");

	if (postState.hand[thisPlayer][villagePosition1] == village || postState.hand[thisPlayer][villagePosition2] == village)
	{
		failedFlag = 1;
		goto endTest;
	}

	// playedCardCount should be +2
	printf("TEST: played count = %d, expected = %d\n", postState.playedCardCount, (preState.playedCardCount + playedCount));

	if (postState.playedCardCount != (preState.playedCardCount + playedCount))
	{
		failedFlag = 1;
		goto endTest;
	}

	// village should be in played pile
	printf("TEST: village should be in played cards\n");

	if (postState.playedCards[0] != village)
	{
		failedFlag = 1;
		goto endTest;
	}

	// number of remaining actions correct?
	printf("TEST: actions count = %d, expected = %d\n", postState.numActions, (preState.numActions - actionsUsed + actionsGained));

	if (postState.numActions != (preState.numActions - actionsUsed + actionsGained))
	{
		failedFlag = 1;
		goto endTest;
	}

endTest:

	if (failedFlag == 0)
	{
		printf("TEST %s: SUCCESS\n", TEST_CARD);		
	}
	else
	{
		printf("TEST %s: FAILED\n", TEST_CARD);
		return 0;
	}

	// ----------- TESTS COMPLETE --------------

	printf("\n >>>>> Testing complete %s <<<<<\n\n", TEST_CARD);

	return 0;
}