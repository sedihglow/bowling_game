/*
    author: James Ross
    note: if you found it, ask before using other than to bowl! thx :D


    handles the game flow during a multiplayer session

    filename: multiplayer.c
*/

                    /* headers */
#include "multiplayer.h"
#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#define NDEBUG /* prevents assert.h */
#include <assert.h>



void playfull_multi(player **allPlayers, const uint64_t numPlayers)
{
    player *currentp = NULL;     /* playing in process of rolling */
    frame *currFrame = NULL;     /* current frame in play */
    uint64_t *scoreTotal = NULL; /* total score for current player */
    uint64_t leadScore = 0;
    /* decrements each time a player rolls */
    register uint64_t played = 0;
    register uint64_t i = 0;
    register uint64_t p = 0;

    char previousR2 = '\0';
    char previousR1 = '\0';

    assert(allPlayers != NULL && *allPlayers != NULL && numPlayers > 1);

    /* multiplayer specific opening */
    printf("\nMulti-player bitches, get some!\n");    
    
    /* go through each frame for each player, and play it! */
    for(i = 1; i < MAXFRAMES; ++i) /* all but frame 11 */
    {
        played = numPlayers;
        p = 0;
       
        do
        {
            currentp = allPlayers[p];
            scoreTotal = &currentp -> scoreTotal;
            currFrame = &currentp -> allFrames[i - 1];

            /* get 2 rolls */
            printf("\n%s's turn", currentp -> name);
            printf("\nEnter in frame %" PRIu64 " results.", i);
            play_frame(currFrame);

            /* fill in fv and score */
            *scoreTotal = calc_score(currFrame); 
        
            
            /* handle bonus roll! sucks to have all these inner loops and ifs */
            if(currFrame -> frameNum == 10)
            {
                previousR2 = currFrame -> roll[R2];
                previousR1 = currFrame -> roll[R1];
                ++currFrame;
                if(previousR2 == '/' || previousR1 == 'X')
                {
                    yes_bonus_r(currFrame);
                    *scoreTotal += calc_bonus_r(currFrame);
                } /* end if */
            } /* end if */

            display_game(&currentp, &leadScore, 1);

           --played;
           ++p;
        }while(played > 0); /* end do-while */
    } /* end for */
     
    /* clear the screen before printing final results */
    system("clear");
    printf("\n\n\nYou finished a single player game! alone!\n");

    display_game(allPlayers, &leadScore, numPlayers);

} /* end playful_multi */

