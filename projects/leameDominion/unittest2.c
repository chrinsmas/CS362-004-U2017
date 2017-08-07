#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


// test gaincard
int main(int argc, char** argv)
{
    struct gameState game;
    int i;
    int retValue;
    int errorPresent = 0;
    int player;
    int card;

    // fill all supply counts with 20 cards
    for (i = 0; i < 25; i++)
    {
        game.supplyCount[i] = 20;
    }

    // set supplyCount for the given card to 0 causing an error to be returned
    game.supplyCount[0] = 0;

    retValue = gainCard(0, &game, 1, 1);

    if(retValue == 0)
    {
        printf("\nError in gainCard, supplied card was 0 and gainCard did not return -1\n");
        errorPresent = 1;
    }

    // set card to -1 this time
    game.supplyCount[0] = -1;

    retValue = gainCard(0, &game, 1, 1);

    if(retValue == 0)
    {
        printf("\nError in gainCard, supplied card was -1 and gainCard did not return -1\n");
        errorPresent = 1;
    }

    game.supplyCount[0] = 20;

    // check toFlag 1
    player = 1;
    card = 1;

    game.deckCount[player] = 0;

    retValue = gainCard(card, &game, 1, player);

    // check no error returned
    if(retValue == -1)
    {
        printf("\nError in gainCard toFlag1, error returned incorrectly \n");
        errorPresent = 1;
    }

    if(game.deck[player][0] != card)
    {
        printf("\nError in gainCard toFlag1, the position in the deck was not correctly set \n");
        errorPresent = 1;
    }

    if(game.supplyCount[card] != 19)
    {
        printf("\nError in gainCard toFlag1, the supply count of the provided card was not decremented properly \n");
        errorPresent = 1;
    }

    if(game.deckCount[player] != 1)
    {
        printf("\nError in gainCard toFlag1, the deck count of the provided player was not incremented properly \n");
        errorPresent = 1;
    }

    game.supplyCount[card] = 20;

    // check toFlag2
    game.handCount[player] = 0;

    retValue = gainCard(card, &game, 2, player);

      // check no error returned
    if(retValue == -1)
    {
        printf("\nError in gainCard toFlag2, error returned incorrectly \n");
        errorPresent = 1;
    }

    if(game.hand[player][0] != card)
    {
        printf("\nError in gainCard toFlag2, the position in the hand was not correctly set \n");
        errorPresent = 1;
    }

    if(game.supplyCount[card] != 19)
    {
        printf("\nError in gainCard toFlag2, the supply count of the provided card was not decremented properly \n");
        errorPresent = 1;
    }

    if(game.handCount[player] != 1)
    {
        printf("\nError in gainCard toFlag2, the hand count of the provided player was not incremented properly \n");
        errorPresent = 1;
    }

    game.supplyCount[card] = 20;

    // check toFlag0
    game.discardCount[player] = 0;

    retValue = gainCard(card, &game, 0, player);

      // check no error returned
    if(retValue == -1)
    {
        printf("\nError in gainCard toFlag0, error returned incorrectly \n");
        errorPresent = 1;
    }

    if(game.discard[player][0] != card)
    {
        printf("\nError in gainCard toFlag0, the position in the discard was not correctly set \n");
        errorPresent = 1;
    }

    if(game.supplyCount[card] != 19)
    {
        printf("\nError in gainCard toFlag0, the supply count of the provided card was not decremented properly \n");
        errorPresent = 1;
    }

    if(game.discardCount[player] != 1)
    {
        printf("\nError in gainCard toFlag1, the deck count of the provided player was not incremented properly \n");
        errorPresent = 1;
    }

    if(errorPresent == 0)
    {
        printf("\nNo errors found in gainCard\n");
    }

    return 0;
}
