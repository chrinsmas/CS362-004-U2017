#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>


// card random test village
int main(int argc, char** argv)
{
    int retValue;
    struct gameState game;
    int player = 0;
    int i, j;
    int cardPos, numCardsInHand, selectedCard, numActionsPrev;
    int errorPresent = 0;
    int errorTotal = 0;
    int errorPresentThisRun;

    int bonus;

    srand(time(NULL));

    // initialize game modeled from playdom.c
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    for(j = 0; j < 1000; j++)
    {
        initializeGame(2, k, 1, &game);

        errorPresentThisRun = 0;
        player = rand() % 2;
        game.whoseTurn = player;

        numCardsInHand = rand() % 10 + 1;
        game.handCount[player] = numCardsInHand;

        cardPos = rand() % numCardsInHand;
        numActionsPrev = rand() % 5;

        // fill hand
        for(i = 0; i < numCardsInHand; i++)
        {
               selectedCard = rand() % 11; // choose from first ten cards

               game.hand[player][i] = selectedCard;
        }

        game.playedCardCount = 0;
        game.numActions = numActionsPrev;

        retValue = cardEffect(village, 0, 0, 0, &game, cardPos, &bonus);

        if(retValue != 0)
        {
            printf("\nError in village card, returned an error incorrectly in run %d\n", j);
            errorPresentThisRun = 1;
        }

        if(game.handCount[player] != numCardsInHand)
        {
            printf("\nError in village card, did not gain a card in run %d\n", j);
            printf("Previous hand count: %d Post village card: %d \n", game.handCount[player], numCardsInHand);
            errorPresentThisRun = 1;
        }

        if(game.numActions != numActionsPrev + 2)
        {
            printf("\nError in village card, did not gain two actions in run %d\n", j);
            errorPresentThisRun = 1;
        }

        if(errorPresentThisRun == 1)
        {
            errorTotal++;
            errorPresent = 1;
        }

    }

    if(errorPresent == 0)
    {
        printf("\nNo error found in village random tests.\n");
    }
    else
    {
        errorTotal = (errorTotal / 1000) * 100;
        printf("\nErrors found in %d%% runs of village random tests.\n", errorTotal);
    }

    return 0;
}
