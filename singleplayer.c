/*
    author: James Ross
    note: if you found it, ask before using it for something other than bowling.
          thx :D

    handles the flow of the game in a single player instance as described in
    singleplayer.h

    filename: singleplayer.c
*/


                    /* headers */
#include "singleplayer.h"
#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#define NDEBUG /* prevents assert.h */
#include <assert.h>

                    /* function source */

/* Keep score of an entire game from start to finish */ 
void playfull_single(player *currentp)/*#{{{*/
{
    frame *currFrame = NULL;       /* current frame in play */
    uint64_t *scoreTotal = NULL;   /* total score for current player */

    register uint64_t i = 0;

    char previousR2 = '\0';
    char previousR1 = '\0';

    assert(currentp != NULL);
    
    /* single player specific opening */
    printf("\nYou are playing single player, get some!\n");

    scoreTotal = &currentp -> scoreTotal;

    /* go through each frame for the player, and play it! */
    currFrame = currentp -> allFrames;
    for(i = 1; i < MAXFRAMES; ++i, ++currFrame) /* all but frame 11 */
    {
        /* get 2 rolls */
        printf("\nEnter in current frame results.");
        play_frame(currFrame);

        /* fill in fv and score */
        *scoreTotal = calc_score(currFrame); 
        
       display_game(&currentp, NULL, 1);
    } /* end for */

    /* current frame is currently on frame 11/11, pointers are fun! */
    --currFrame;
    previousR2 = currFrame -> roll[R2];
    previousR1 = currFrame -> roll[R1];
    ++currFrame;
    if(previousR2 == '/' || previousR1 == 'X')
    {
        yes_bonus_r(currFrame);
        *scoreTotal += calc_bonus_r(currFrame);
    } /* end if */
   
    /* clear the screen before printing final results */
    system("clear");
    printf("\n\n\nYou finished a single player game! alone!\n");

    display_game(&currentp, NULL, 1);

} /* end playfull_single #}}} */


