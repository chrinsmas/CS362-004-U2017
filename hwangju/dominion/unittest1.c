#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>


// is game over tests
int main(int argc, char** argv)
{
    struct gameState game;
    int i;
    int retValue;
    int errorPresent = 0;
    int valueChanged = 0;

    // should return that game is not over
    // fill all supply counts with 20 cards
    for (i = 0; i < 25; i++)
    {
        game.supplyCount[i] = 20;
    }

    retValue = isGameOver(&game);

    if(retValue == 1)
    {
        printf("\nError in isGameOver, game over returned when all cards are greater than 0\n");
        errorPresent = 1;
    }

    // check that all card values are still set to 20 and have not been changed
    for(i = 0; i < 25; i++)
    {
        if(game.supplyCount[i] != 20)
        {
            valueChanged = 1;
        }
    }

    if(valueChanged == 1)
    {
        printf("\nError in isGameOver, value of supplyCount for cards is being changed when being returned from the function.\n");
        errorPresent = 1;
    }

    // set province = 0 so game over should return true
    game.supplyCount[3] = 0;

    retValue = isGameOver(&game);

    if(retValue == 0)
    {
        printf("\nError in isGameOver, function returned false when game state contains 0 province cards\n");
        errorPresent = 1;
    }

    // reset province to have a value and then run the test again with each card being 0
    game.supplyCount[3] = 10;

    for(i = 0; i < 24; i++)
    {
        // province card should end game so remove that from the test of the other cards
        if(i != 3)
        {
            game.supplyCount[i] = 0;

            retValue = isGameOver(&game);

            if(retValue == 1)
            {
                printf("\nError in isGameOver, function returned true when game state supply count for card %d contains 0 cards\n", i);
                errorPresent = 1;
            }

            game.supplyCount[i] = 20;
        }
    }

    // set two cards to 0 and check to see if proper return value is provided
    game.supplyCount[0] = 0;
    game.supplyCount[1] = 0;

    retValue = isGameOver(&game);

    if(retValue == 1)
    {
        printf("\nError in isGameOver, function returned true when game state supply count for 2 cards contains 0 \n");
        errorPresent = 1;
    }

    // set third card to 0 and check to see if false is returned
    game.supplyCount[2] = 0;
    retValue = isGameOver(&game);

    if(retValue == 0)
    {
        printf("\nError in isGameOver, function returned false when game state supply count for 3 cards contains 0 \n");
        errorPresent = 1;
    }

    if(errorPresent == 0)
    {
        printf("\nNo errors found in isGameOver unit tests\n");
    }

    return 0;
}
