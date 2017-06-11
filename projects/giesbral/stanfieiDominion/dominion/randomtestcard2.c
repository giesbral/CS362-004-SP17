/*
	Alex Giesbrecht - giesbral@oregonstate.edu
	5/9/2017
	CS362_400_S2017
	Assignment 4

	Random Test for Adventurer card
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TEST_CARD_NAME "Adventurer"
#define NUM_TESTS 200
#define NUM_KINGDOM 10
#define NUM_TEMP_KINGDOM 20

/*********************************************************************************************************************************
// Function: randDec
//
// Input: seed, lower bound, upper bound
// Results: returns a randomly generated decimal number between lower bound and upper bound
//
// generates a random decimal number between low and high
**********************************************************************************************************************************/
int randDec(int low, int high)
{
	return rand() % (high - low + 1) + low;
}

/*********************************************************************************************************************************
// Function: shuffleArray
//
// Input: array of int by reference, size of array by value
// Results: array of ints is shuffled
//
// Randomizes the order of the contents of an array
**********************************************************************************************************************************/
void shuffleArr(int* array, int n) {

	int k, i, temp;

	for (i = 0; i < n; i++)
	{
		// randomly determine the index of the elements to swap
		k = rand() % (n - i) + i;

		// swap elements to shuffle
		temp = array[k];
		array[k] = array[i];
		array[i] = temp;
	}
}

int main() {

	struct gameState preState, postState;

	srand(time(0));

	// loop counters
	int i, k, testLoop;

	int failureCount = 0;

	printf("----------------- Random Testing Card: %s ----------------\n", TEST_CARD_NAME);

	for (testLoop = 1; testLoop <= NUM_TESTS; testLoop++)
	{
		printf("\nTEST %d:\n", testLoop);

		// 0 == failure, 1 == success
		int failedFlag = 0;

		// randomize kingdom cards
		int kingdom[NUM_KINGDOM] = { -1 };

		int tempKingdomArr[NUM_TEMP_KINGDOM] = { adventurer,
			council_room,
			feast,
			gardens,
			mine,
			remodel,
			smithy,
			village,
			baron,
			great_hall,
			minion,
			steward,
			tribute,
			ambassador,
			cutpurse,
			embargo,
			outpost,
			salvager,
			sea_hag,
			treasure_map };

		shuffleArr(tempKingdomArr, NUM_TEMP_KINGDOM);

		for (i = 0; i < NUM_KINGDOM; ++i)
		{
			kingdom[i] = tempKingdomArr[i];
		}

		// randomize seed
		int seed = randDec(1, 1000);

		// randomize numPlayers (2-4)
		int numPlayers = randDec(2, 4);

		// randomize thisPlayer
		int thisPlayer = randDec(0, numPlayers - 1);

		// initialize game state
		initializeGame(numPlayers, kingdom, seed, &preState);

		//randomizing hand size
		preState.handCount[thisPlayer] = randDec(1, MAX_HAND);

		// clearing player's hand
		for (i = 0; i < MAX_HAND; i++)
		{
			preState.hand[thisPlayer][i] = -1;
		}

		// setting player's hand to a random assortment of cards
		for (i = 0; i < preState.handCount[thisPlayer]; i++)
		{
			preState.hand[thisPlayer][i] = randDec(curse, treasure_map);
		}

		// randomize adventurer position and add to hand
		int adventurerPosition = randDec(0, preState.handCount[thisPlayer] - 1);

		preState.hand[thisPlayer][adventurerPosition] = adventurer;

		// randomizing deck size
		preState.deckCount[thisPlayer] = randDec(0, MAX_DECK);

		// clearing player's deck
		for (i = 0; i < MAX_DECK; i++)
		{
			preState.deck[thisPlayer][i] = -1;
		}

		// setting player's deck to a random assortment of cards
		for (i = 0; i < preState.deckCount[thisPlayer]; i++)
		{
			preState.deck[thisPlayer][i] = randDec(curse, treasure_map);
		}

		// randomizing discard size
		preState.discardCount[thisPlayer] = randDec(0, MAX_DECK);

		// clearing the player's discard pile
		for (i = 0; i < MAX_DECK; i++)
		{
			preState.discard[thisPlayer][i] = -1;
		}

		// setting the player's discard pile to a random assortment of cards
		for (i = 0; i < preState.discardCount[thisPlayer]; i++)
		{
			preState.discard[thisPlayer][i] = randDec(curse, treasure_map);
		}

		// target values
		int cardsGained;
		int playedCount = 1;

		if (preState.discardCount[thisPlayer] + preState.deckCount[thisPlayer] < 2)
		{
			cardsGained = preState.discardCount[thisPlayer] + preState.deckCount[thisPlayer];
		}
		else
		{
			cardsGained = 2;
		}
		
		// copy the pre-test game state to the post-test game state
		memcpy(&postState, &preState, sizeof(struct gameState));

		// ***** Playing test card ***** //
		playAdventurer(&postState, thisPlayer);

		// checking hand count
		if (postState.handCount[thisPlayer] != (preState.handCount[thisPlayer] + cardsGained - playedCount))
		{
			failedFlag = 1;
			printf("\tFAILED ON TEST: thisPlayer hand count = %d, expected = %d\n", postState.handCount[thisPlayer], (preState.handCount[thisPlayer] + cardsGained - playedCount));
		}

		// played adventurer card should not be in the player's hand
		if (postState.hand[thisPlayer][adventurerPosition] == adventurer && preState.deck[thisPlayer][postState.deckCount[thisPlayer]] != adventurer)
		{
			failedFlag = 1;
			printf("\tFAILED ON TEST: player's hand should not contain the played adventurer card\n");
		}

		
		if (preState.deckCount[thisPlayer] >= cardsGained)
		{
			// checking deck count
			if (postState.deckCount[thisPlayer] != (preState.deckCount[thisPlayer] - (cardsGained + (postState.discardCount[thisPlayer] - preState.discardCount[thisPlayer]))))
			{
				failedFlag = 1;
				printf("\tFAILED ON TEST: thisPlayer deck count = %d, expected = %d\n", postState.deckCount[thisPlayer], (preState.deckCount[thisPlayer] - (cardsGained + (postState.discardCount[thisPlayer] - preState.discardCount[thisPlayer]))));
			}

			// cards drawn from deck the same as the new cards in the player's hand?
			// was the adventurer card played from hand position replaced with the correct card?
			if (preState.deck[thisPlayer][postState.deckCount[thisPlayer]] != postState.hand[thisPlayer][adventurerPosition] &&
				(preState.deck[thisPlayer][postState.deckCount[thisPlayer]] == copper ||
					preState.deck[thisPlayer][postState.deckCount[thisPlayer]] == silver ||
					preState.deck[thisPlayer][postState.deckCount[thisPlayer]] == gold))
			{
				failedFlag = 1;
				printf("\tFAILED ON TEST: cards drawn from deck are not the same as the new cards in the player's hand\n");
				goto continueTests;
			}

			// are the remaining cards drawn from the deck (that didn't replace the adventurer card at hand position) the same as the cards currently in the player's hand?
			i = preState.handCount[thisPlayer];
			k = preState.deckCount[thisPlayer] - 1;

			while (i < postState.handCount[thisPlayer] && k > postState.deckCount[thisPlayer])
			{
				if (postState.hand[thisPlayer][i] != preState.deck[thisPlayer][k] &&
					(preState.deck[thisPlayer][k] == copper ||
						preState.deck[thisPlayer][k] == silver ||
						preState.deck[thisPlayer][k] == gold))
				{
					failedFlag = 1;
					printf("\tFAILED ON TEST: cards drawn from deck are not the same as the new cards in the player's hand\n");
					goto continueTests;
				}

				i++;
				k--;
			}
		}
		else
		{
			// checking deck count
			if (postState.deckCount[thisPlayer] != preState.discardCount[thisPlayer] + preState.deckCount[thisPlayer] - (cardsGained + (postState.discardCount[thisPlayer])))
			{
				failedFlag = 1;
				printf("\tFAILED ON TEST: thisPlayer deck count = %d, expected = %d\n", postState.deckCount[thisPlayer], (preState.discardCount[thisPlayer] - (cardsGained + (postState.discardCount[thisPlayer]))));
			}

			// If deck count < cardsGained, was discard shuffled into deck correctly?
			if (postState.deckCount[thisPlayer] != preState.discardCount[thisPlayer] + preState.deckCount[thisPlayer] - (cardsGained + (postState.discardCount[thisPlayer])))
			{
				failedFlag = 1;
				printf("\tFAILED ON TEST: discard pile not shuffled into deck correctly\n");
			}
		}

	continueTests:

		// discard pile should have the correct number of cards
		if (postState.discardCount[thisPlayer] != preState.discardCount[thisPlayer] + (preState.deckCount[thisPlayer] - postState.deckCount[thisPlayer] - cardsGained))
		{
			failedFlag = 1;
			printf("\tFAILED ON TEST: player discard count: %d, expected: %d\n", (preState.discardCount[thisPlayer] + (preState.deckCount[thisPlayer] - postState.deckCount[thisPlayer] - cardsGained)), postState.discardCount[thisPlayer]);
		}

		// cards drawn from the deck should be treasure cards
		if (postState.hand[thisPlayer][adventurerPosition] != copper && 
			postState.hand[thisPlayer][adventurerPosition] != silver && 
			postState.hand[thisPlayer][adventurerPosition] != gold)
		{
			failedFlag = 1;
			printf("\tFAILED ON TEST: card drawn from deck at adventurerPosition is not a treasure card\n");
		}

		for (i = preState.handCount[thisPlayer]; i < postState.handCount[thisPlayer]; ++i)
		{
			if (postState.hand[thisPlayer][i] != copper && 
				postState.hand[thisPlayer][i] != silver && 
				postState.hand[thisPlayer][i] != gold)
			{
				failedFlag = 1;
				printf("\tFAILED ON TEST: cards drawn from deck are not treasure cards\n");
				break;
			}
		}

		// playedCardCount should be +1
		if (postState.playedCardCount != (preState.playedCardCount + playedCount))
		{
			failedFlag = 1;
			printf("\tFAILED ON TEST: played count = %d, expected = %d\n", postState.playedCardCount, (preState.playedCardCount + playedCount));
		}

		// adventurer should be in played pile
		if (postState.playedCards[preState.playedCardCount] != adventurer)
		{
			failedFlag = 1;
			printf("\tFAILED ON TEST: Played card value = %d, expected %d\n", postState.playedCards[preState.playedCardCount], adventurer);
		}

		if (failedFlag == 1)
		{
			++failureCount;
			printf("TEST %d: FAILED\n", testLoop);
			printf("Kingdom Cards: ");
			for (i = 0; i < NUM_KINGDOM; ++i)
			{
				printf("%d ", kingdom[i]);
			}
			printf("\n");
			printf("seed = %d\n", seed);
			printf("Number of Players: %d\n", numPlayers);
			printf("Current Player: %d\n", thisPlayer);
			printf("Hand Count: %d\n", preState.handCount[thisPlayer]);
			printf("Deck Count: %d\n", preState.deckCount[thisPlayer]);
			printf("Discard Count: %d\n", preState.discardCount[thisPlayer]);
			printf("New cards in hand: ");
			printf("%d ", preState.hand[thisPlayer][adventurerPosition]);
			for (i = preState.handCount[thisPlayer]; i < postState.handCount[thisPlayer]; i++)
			{
				printf("%d ", postState.hand[thisPlayer][i]);
			}
			printf("\n");

			printf("Cards drawn from deck: ");
			for (k = preState.deckCount[thisPlayer] - 1; k > postState.deckCount[thisPlayer]; k--)
			{
				printf("%d ", preState.deck[thisPlayer][k]);
			}
			printf("\n");
			printf("deck to adventurer: %d\n", preState.deck[thisPlayer][postState.deckCount[thisPlayer]]);
			printf("card at adventurer: %d\n", postState.hand[thisPlayer][adventurerPosition]);
		}
	}

	// ----------- TESTS COMPLETE --------------

	printf("\n >>>>> Testing complete %s: Failure Count: %d/%d <<<<<\n\n", TEST_CARD_NAME, failureCount, NUM_TESTS);

	return 0;
}