#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// test udpateCoins
int main(int argc, char** argv)
{
    struct gameState game;
    int player;
    int i;
    int expectedValue;
    int retValue;
    int changedValue = 0;
    int errorPresent = 0;
    player = 1;

    game.handCount[player] = 5;

    // test 5 copper coins
    for (i = 0; i < 5; i++)
    {
        game.hand[player][i] = copper;
    }

    expectedValue = 5;

    retValue = updateCoins(player, &game, 0);

    if(retValue != 0)
    {
        printf("\nError in updateCoins, returned with an error value incorrectly.\n");
        errorPresent = 1;
    }

    if(game.coins != expectedValue)
    {
        printf("\nError in updateCoins, returned unexpected coin amount in test 5 copper coins.\n");
        errorPresent = 1;
    }

    game.coins = 0;

    // test 0 coins and if function changes cards in hand
    for(i = 0; i < 5; i++)
    {
        game.hand[player][i] = 0;
    }

    expectedValue = 0;

    retValue = updateCoins(player, &game, 0);

    for(i = 0; i < 5; i++)
    {
        if(game.hand[player][i] != 0)
        {
            changedValue = 1;
        }
    }

    if(retValue != 0)
    {
        printf("\nError in updateCoins, returned with an error value incorrectly.\n");
        errorPresent = 1;
    }
    if(game.coins != expectedValue)
    {
        printf("\nError in updateCoins, returned unexpected coin amount in test 0 coins.\n");
        errorPresent = 1;
    }

    if(changedValue != 0)
    {
        printf("\nError in udpateCoins, changed the value of the cards passed in.\n");
        errorPresent = 1;
    }

    game.coins = 0;
    expectedValue = 100;

    // test 0 coins and a bonus
    for(i = 0; i <  5; i++)
    {
        game.hand[player][i] = 0;
    }

    retValue = updateCoins(player, &game, 100);

    if(retValue != 0)
    {
        printf("\nError in updateCoins, returned with an error value incorrectly.\n");
        errorPresent = 1;
    }
    if(game.coins != expectedValue)
    {
        printf("\nError in updateCoins, returned unexpected coin amount in test 0 coins and a bonus.\n");
        errorPresent = 1;
    }

    // test 5 silver coins
    game.coins = 0;
    expectedValue = 10;

    for(i = 0; i <  5; i++)
    {
        game.hand[player][i] = silver;
    }

    retValue = updateCoins(player, &game, 0);

    if(retValue != 0)
    {
        printf("\nError in updateCoins, returned with an error value incorrectly.\n");
        errorPresent = 1;
    }
    if(game.coins != expectedValue)
    {
        printf("\nError in updateCoins, returned unexpected coin amount in test 5 silver coins.\n");
        errorPresent = 1;
    }

    // test 5 gold coins
    game.coins = 0;
    expectedValue = 15;

    for(i = 0; i < 5; i++)
    {
        game.hand[player][i] = gold;
    }

    retValue = updateCoins(player, &game, 0);

    if(retValue != 0)
    {
        printf("\nError in updateCoins, returned with an error value incorrectly.\n");
        errorPresent = 1;
    }
    if(game.coins != expectedValue)
    {
        printf("\nError in updateCoins, returned unexpected coin amount in test 5 gold coins.\n");
        errorPresent = 1;
    }

    // test 1 copper 1 silver and 1 gold
    game.coins = 0;
    expectedValue = 6;

    for(i = 0; i< 5; i++)
    {
        game.hand[player][i] = 0;
    }

    game.hand[player][0] = copper;
    game.hand[player][1] = silver;
    game.hand[player][2] = gold;

    retValue = updateCoins(player, &game, 0);

    if(retValue != 0)
    {
        printf("\nError in updateCoins, returned with an error value incorrectly.\n");
        errorPresent = 1;
    }

    if(game.coins != expectedValue)
    {
        printf("\nError in updateCoins, returned unexpected coin amount in test 1 copper 1 silver and 1 gold.\n");
        errorPresent = 1;
    }

    if(errorPresent == 0)
    {
        printf("\nNo Errors found in udpateCoins\n\n");
    }

    return 0;
}
