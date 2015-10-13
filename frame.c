/*
    author: James Ross
    note: if you found it, and want to use it while bowling, invite me. :D
    
    handles all the functionalities described in frame.h
    
    filename: frame.c
*/


                    /* headers */
#include "frame.h"
#include "client.h"
#include "game.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h> 
#define NDEBUG /* prevents assert.h */
#include <assert.h>

                    /* function source code */

/* Play a single frame for a given player, 1 on success 0 on failure */
void play_frame(frame *currFrame)/*#{{{*/
{
    char *currRoll = NULL;

    assert(currFrame != NULL); 

    currRoll = currFrame -> roll;

   
        printf("\nRoll 1 ");
    do
    {
        currRoll[R1] = gather_roll();
        /* first roll cannot be a spare. */
    }while(currRoll[R1] == '/'); /* end do-while */
    
    if(currRoll[R1] != 'X' || currFrame -> frameNum == 10)
    {
        printf("\nRoll 2 ");
        currRoll[R2] = gather_roll();
    } /* end if */
    
    if(conv_r(0, currRoll[R1]) + conv_r(0, currRoll[R2]) > 9 &&
        currRoll[R1] != 'X') /* 10 + is a spare */
    {
        currRoll[R2] = '/';
    } /* end if */
} /* end play_frame #}}} */

/* play bonus roll on 10th frame, sets roll values appropriately,
   returns 1 on success, 0 if incorrect frame was given */
uint64_t yes_bonus_r(frame *currFrame)/*#{{{*/
{
    char *currRoll = NULL;

    assert(currFrame != NULL); 

    currRoll = currFrame -> roll;

    if(currRoll[R2] == '\0')
    {
        printf("Frame 10 bonus roll! ");
        currRoll[R1] = gather_roll();
        return 1;
    } /* end if */
    
    return 0;
} /* end yes_bonus_r #}}} */

/* display a single frame, if toDisplay is NULL, nothing displays */
void display_frame(frame *toDisplay)/*#{{{*/
{
    if(toDisplay != NULL)
    {
        printf("Frame #%" PRIu64 "\t"
               "R1: %c R2: %c\t"
               "Individual frame score: %" PRIu64 "\n", toDisplay -> frameNum,
               toDisplay -> roll[R1], toDisplay -> roll[R2], toDisplay -> frameVal);
    } /* end if */
} /* end display_frame #}}} */
