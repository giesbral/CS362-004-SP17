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

#define TEST_CARD_NAME "Council Room"

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
	const int testCard = council_room;
	const int testCardPosition = 0;
	const int cardsGained = 4;
	const int plusBuys = 1;

	printf("----------------- Testing Card: %s ----------------\n", TEST_CARD_NAME);

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

	preState.hand[thisPlayer][testCardPosition] = testCard;

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

	printf("Playing %s...\n", TEST_CARD_NAME);
	playCouncil_Room(&postState, testCardPosition, thisPlayer);

	// checking hand count
	printf("\n\tTEST: thisPlayer hand count = %d, expected = %d\n", postState.handCount[thisPlayer], (preState.handCount[thisPlayer] + cardsGained - playedCount));

	if (postState.handCount[thisPlayer] != (preState.handCount[thisPlayer] + cardsGained - playedCount))
	{
		failedFlag = 1;
		printf("\tTEST FAILED\n");
	}

	// checking deck count
	printf("\n\tTEST: thisPlayer deck count = %d, expected = %d\n", postState.deckCount[thisPlayer], (preState.deckCount[thisPlayer] - cardsGained));

	if (postState.deckCount[thisPlayer] != (preState.deckCount[thisPlayer] - cardsGained))
	{
		failedFlag = 1;
		printf("\tTEST FAILED\n");
	}

	// outpost should not be in the player's hand
	printf("\n\tTEST: player's hand should not contain an outpost card\n");

	if (postState.hand[thisPlayer][testCardPosition] == testCard)
	{
		failedFlag = 1;
		printf("\tTEST FAILED\n");
	}

	// playedCardCount should be +1
	printf("\n\tTEST: played count = %d, expected = %d\n", postState.playedCardCount, (preState.playedCardCount + playedCount));

	if (postState.playedCardCount != (preState.playedCardCount + playedCount))
	{
		failedFlag = 1;
		printf("\tTEST FAILED\n");
	}

	// outpost should be in played pile
	printf("\n\tTEST: outpost should be in played cards\n");

	if (postState.playedCards[0] != outpost)
	{
		failedFlag = 1;
		printf("\tTEST FAILED\n");
	}

	// player should have +1 buys
	printf("\n\tTEST: thisPlayer numBuys = %d, expected = %d\n", postState.numBuys, preState.numBuys + plusBuys);

	if (postState.numBuys != preState.numBuys + plusBuys)
	{
		failedFlag = 1;
		printf("\tTEST FAILED\n");
	}	

	if (failedFlag == 0)
	{
		printf("\nTEST %s: SUCCESS\n", TEST_CARD_NAME);
	}
	else
	{
		printf("\nTEST %s: FAILED\n", TEST_CARD_NAME);
	}

	// ----------- TESTS COMPLETE --------------

	printf("\n >>>>> Testing complete %s <<<<<\n\n", TEST_CARD_NAME);

	return 0;
}