#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// card test adventurer
int main(int argc, char** argv)
{
    int retValue;
    struct gameState game;
    int player = 0;
    int i;
    int cardPos;
    int errorPresent = 0;
    int bonus;
    int treasureCount = 0;
    int player_turn;

    // initialize game modeled from playdom.c
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
           sea_hag, tribute, smithy};

    initializeGame(2, k, 1, &game);
    player_turn = game.whoseTurn;
    printf("\nTESTING Adventurer Card\n");

    cardPos = 0;

    for(i = 0; i < 5; i++)
    {
        game.hand[player][i] = estate;
    }

    game.hand[player][0] = smithy;

    game.handCount[player] = 5;
    game.playedCardCount = 0;
    game.numActions = 0;

    for(i = 0; i < 10; i++)
    {
        game.deck[player][i] = estate;
    }

    game.deckCount[player] = 10;

    game.discard[player][0] = gold;
    game.discard[player][1] = gold;
    game.discard[player][2] = gold;
    game.discard[player][3] = gold;

    game.discardCount[player] = 4;

    // try card with shuffle
    retValue = cardEffect(adventurer, 0, 0, 0, &game, cardPos, &bonus);

    if(retValue != 0)
    {
        printf("\nError in adventurer card with shuffle, returned an error incorrectly.\n");
        errorPresent = 1;
    }
    else
        printf("TEST PASSED\n");

    if(game.handCount[player] != 6)
    {
        printf("\nError in adventurer card with shuffle, did not gain 2 cards.\n");
        errorPresent = 1;
    }
    else
    {
        for(i = 0; i < 6; i++)
        {
            if(game.hand[player][i] == gold)
            {
                treasureCount++;
            }
        }

        if(treasureCount != 2)
        {
            printf("\nError in adventurer card with shuffle, did not gain two treasure cards.\n");
            errorPresent = 1;
        }
        else
            printf("TEST PASSED\n");
    }
    if(game.whoseTurn == player_turn)
    {
        printf("TEST PASSED\n");
    }
    else
        printf("Error in adventurer card, player turn changed.\n");
    if(errorPresent == 0)
    {
        printf("All tests passed: Adventurer Card\n");
    }

    return 0;
}
