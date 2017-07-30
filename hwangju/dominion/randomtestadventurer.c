#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>


// card random test adventurer
int main(int argc, char** argv)
{
    int retValue;
    struct gameState game;
    int player = 0;
    int i, j;
    int cardPos, numCardsInHand, numCardsInDiscard, selectedCard;
    int errorPresent = 0;
    int bonus;
    int treasureCount = 0;
    int prevTreasureCount = 0;
    int errorTotal = 0;
    int errorFoundThisRun;

    // initialize game modeled from playdom.c
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    srand(time(NULL));

    for(j = 0; j < 1000; j++)
    {
        initializeGame(2, k, 1, &game);

        errorFoundThisRun = 0;
        player = rand() % 2;
        game.whoseTurn = player;

        numCardsInHand = rand() % 10 + 1;
        game.handCount[player] = numCardsInHand;

        numCardsInDiscard = rand() % 10 + 10;
        game.discardCount[player] = numCardsInDiscard;

        cardPos = rand() % numCardsInHand;

        treasureCount = 0;

        // fill hand
        for(i = 0; i < numCardsInHand; i++)
        {
               selectedCard = rand() % 11; // choose from first ten cards

               // keep running total of the treasure count so far
               if(selectedCard == copper || selectedCard == silver || selectedCard == gold)
               {
                   treasureCount++;
               }

               game.hand[player][i] = selectedCard;
        }

        // put the position of the adventurer card in the hand
        game.hand[player][cardPos] = adventurer;

        // fill discard
        for(i = 0; i < numCardsInDiscard; i++)
        {
               selectedCard = rand() % 11; // choose from first ten cards

               game.discard[player][i] = selectedCard;
        }

        // insure we have at least two treasure cards as without them we can get a condition of an infinite loop
        // where the function keeps searchign for treasure cards without ever finding them. Could be considered a bug
        game.discard[player][numCardsInDiscard - 2] = copper;
        game.discard[player][numCardsInDiscard - 1] = silver;

        game.playedCardCount = 0;
        game.numActions = 0;

        prevTreasureCount = treasureCount;

        // try card with shuffle
        retValue = cardEffect(adventurer, 0, 0, 0, &game, cardPos, &bonus);

        treasureCount = 0;

        if(retValue != 0)
        {
            printf("\nError in adventurer card random test, returned error incorrectly in run %d.\n", j);
            printf("Number of cards in hand previous: %d, number of cards in hand after adventurer: %d\n", numCardsInHand, game.handCount[player]);
            printf("previous treasure count in hand: %d, treasure count after adventurer: %d\n", prevTreasureCount, treasureCount);
            errorPresent = 1;
            errorFoundThisRun = 1;
        }

        if(game.handCount[player] != numCardsInHand + 1)
        {
            printf("\nError in adventurer card random test, did not gain two cards in run %d.\n", j);
            printf("Number of cards in hand previous: %d, number of cards in hand after adventurer: %d\n", numCardsInHand, game.handCount[player]);
            errorPresent = 1;
            errorFoundThisRun = 1;
        }


        for(i = 0; i < game.handCount[player]; i++)
        {
            if(game.hand[player][i] == copper || game.hand[player][i] == silver || game.hand[player][i] == gold)
            {
                treasureCount++;
            }
        }

        if(treasureCount != prevTreasureCount + 2)
        {
            printf("\nError in adventurer card random test, did not gain two treasure cards in run %d.\n", j);
            printf("previous treasure count in hand: %d, treasure count after adventurer: %d\n", prevTreasureCount, treasureCount);
            errorPresent = 1;
            errorFoundThisRun = 1;
        }

        if(errorFoundThisRun == 1)
        {
            errorTotal++;
        }

    }

    if(errorPresent == 0)
    {
        printf("\nNo error found in adventurer random tests.\n");
    }
    else
    {
        errorTotal = errorTotal/1000 * 100;
        printf("\nErrors found in %d%% of runs\n", errorTotal);
    }

    return 0;
}
