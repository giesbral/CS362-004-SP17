/*
Alex Giesbrecht - giesbral@oregonstate.edu
4/26/2017
CS362_400_S2017

Unit Test for Outpost card
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define TEST_CARD "Outpost"

int main() {

	struct gameState preState, postState;
	int kingdom[10] = { adventurer, smithy, village, outpost, sea_hag, mine, cutpurse, tribute, embargo, minion };
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
	int i;

	// 0 == failure, 1 == success
	int failedFlag = 0;

	// initialize game state
	initializeGame(numPlayers, kingdom, seed, &preState);

	const int playedCount = 1;
	const int outpostPosition = 0;
	const int cardsGained = 0;

	printf("----------------- Testing Card: %s ----------------\n", TEST_CARD);

	// setting up player's hand
	for (i = 0; i < MAX_HAND; i++)
	{
		preState.hand[thisPlayer][i] = -1;
	}

	preState.handCount[thisPlayer] = 5;

	// setting player's hand to all copper, except for outpost
	for (i = 0; i < preState.handCount[thisPlayer]; i++)
	{
		preState.hand[thisPlayer][i] = copper;
	}

	preState.hand[thisPlayer][outpostPosition] = outpost;

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

	printf("\tPlaying Outpost...\n");
	playOutpost(&postState, outpostPosition, thisPlayer);

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

	// outpost should not be in the player's hand
	printf("\tTEST: player's hand should not contain an outpost card\n");

	if (postState.hand[thisPlayer][outpostPosition] == outpost)
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

	// outpost should be in played pile
	printf("\tTEST: outpost should be in played cards\n");

	if (postState.playedCards[0] != outpost)
	{
		failedFlag = 1;
		goto endTest;
	}

	// number of remaining actions correct?
	//printf("\tTEST: actions count = %d, expected = %d\n", postState.numActions, (preState.numActions - actionsUsed));

	//if (postState.numActions != (preState.numActions - actionsUsed))
	//{
	//	failedFlag = 1;
	//	goto endTest;
	//}

	// outpostPlayed should equal 1
	printf("\tTEST: outpostPlayed should equal 1\n");

	if (postState.outpostPlayed != 1)
	{
		failedFlag = 1;
		goto endTest;
	}

	// end thisPlayer's turn
	printf("\tEnding player's turn...\n");

	endTurn(&postState);

	// should still be thisPlayer's turn
	printf("\tTEST: whoseTurn should be 0\n");

	if (postState.whoseTurn != 0)
	{
		failedFlag = 1;
		goto endTest;
	}

	// player should have 3 cards in their hand
	printf("\tTEST: hand count should be 3");

	if (postState.handCount[thisPlayer] != 3)
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