#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// test discardCard
int main(int argc, char** argv)
{
    struct gameState game;
    int errorPresent = 0;
    int player;
    int handPos;

    player = 1;
    handPos = 1;
    game.playedCardCount = 0;

    // check discarding last card in hand and that played card count doesn't get incremented incorrectly
    game.hand[player][handPos] = 1;
    game.handCount[player] = 2;

    discardCard(handPos, player, &game, 0);

    if(game.hand[player][handPos] != -1)
    {
        printf("\nError in discardCard, the card that was discarded was not set to played.\n");
        errorPresent = 1;
    }

    if(game.handCount[player] != 1)
    {
        printf("\nError in discardCard, the users hand count was not decremented when last card in hand is discarded. Note: not only card, last card position wise\n");
        errorPresent = 1;
    }

    if(game.playedCardCount != 01)
    {
        printf("\nError in discardCard, the played card count was incremented when a card should not have been trashed.\n");
        errorPresent = 1;
    }

    // check discarding only card in hand
    game.handCount[player] = 1;
    game.hand[player][handPos] = 1;

    discardCard(handPos, player, &game, 0);

    if(game.handCount[player] != 0)
    {
        printf("\nError in discardCard, the users hand count was not decremented when only card in hand is discarded.\n");
        errorPresent = 1;
    }

    // check discarding middle card in hand with other cards surrounding it and trashing cards
    game.playedCardCount = 0;
    game.handCount[player] = 3;
    game.hand[player][handPos] = 1;
    game.hand[player][2] = 5; // set last card to unique value

    discardCard(handPos, player, &game, 0);

    if(game.handCount[player] != 2)
    {
        printf("\nError in discardCard, the users hand count was not decremented when a middle card in hand is discarded.\n");
        errorPresent = 1;
    }

    if(game.hand[player][handPos] != 5)
    {
        printf("\nError in discardCard, the value of the card in the discarded card's position was not updated to the value of the last card in the user's hand when a middle card in hand is discarded.\n");
        errorPresent = 1;
    }

    if(game.hand[player][2] != -1)
    {
        printf("\nError in discardCard, the value of the card in the last card's position was not set to played when a middle card in hand is discarded.\n");
        errorPresent = 1;
    }

    if(game.playedCards[0] != 1)
    {
        printf("\nError in discardCard, the correct card value was not added to the played cards pile when trashed.\n");
        errorPresent = 1;
    }

    if(game.playedCardCount != 1)
    {
        printf("\nError in discardCard, the played card count was not incremented after a card should have been trashed.\n");
        errorPresent = 1;
    }

    if(errorPresent == 0)
    {
        printf("\nNo Errors found in discardCard\n");
    }

    return 0;
}
