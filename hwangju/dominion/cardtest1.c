#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

//set NOISY_TEST to 0 to remove prinftf's from output
#define NOISY_TEST 1

int main() {
    int p = 0;
    int handPos = 0;
    int seed = 1000;
    int numPlayer = 2;
//    int new_game;
    int hand_count, action_count, player_turn;
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
    struct gameState G;

    printf("TESTING Village Card\n");
    //clear the game state
    memset(&G, 23, sizeof(struct gameState));
    //initialize a new game
//    new_game = initializeGame(numPlayer, k, seed, &G);
    initializeGame(numPlayer, k, seed, &G);

    hand_count = G.handCount[p];
    action_count = G.numActions;
    player_turn = G.whoseTurn;

    //play village card
    playVillage(&G, handPos);
#if (NOISY_TEST == 1)
    //hand should have +0 cards
    if(G.handCount[p] == hand_count)
        printf("TEST PASSED\n");
    else
        printf("TEST FAILED\n");
    //player should have +2 action cards
    if(G.numActions == action_count + 2)
        printf("TEST PASSED\n");
    else
        printf("TEST FAILED\n");
    //player's turn should not change
    if(G.whoseTurn == player_turn)
        printf("TEST PASSED\n");
    else
        printf("TEST FAILED\n");
#endif

    hand_count = G.handCount[p];
    action_count = G.numActions;
    player_turn = G.whoseTurn;

    printf("All tests passed: Village Card\n");

    return 0;
}
