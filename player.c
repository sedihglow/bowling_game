/*
    author: James Ross
    note: if you found it, and want to use it while bowling, invite me. :D
    
    handles all the functions declared in player.h aswell as any private
    functions used in the functionality of player.

    filename: player.c
*/
                    
                    /* headers */
#include "player.h"
                    
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define NDEBUG /* prevents assert.h */
#include <assert.h>
                    /* definitions */

                    /* macros */

/* initializes a player for the game, returns player or NULL if failure,
   sets errno to proper error code,
   EINVAL = players name was NULL or invalid
   EAGAIN = memory failed to allocate */
player* create_player(const char *name)/*#{{{*/
{
    player *new = NULL;            /* new player */
    frame *current = NULL;
    register uint64_t f = 0;       /* used as current frame number */
    register uint64_t temp = 0;    /* temp used in init to improve loop */

    register size_t nameLength = 0;   /* size_t might be smaller than 32bit */

    /* check for validity of name */
    if(name == NULL || name[nameLength = strlen(name)] != '\0')
    {
        errno = EINVAL;
        return NULL;
    } /* end if */

    ++nameLength; /* nameLength = strlen(name) + 1 */

    new = (player*) malloc(sizeof(player)); 
    new -> scoreTotal = 0;
    new -> name = (char*) malloc(sizeof(char) * nameLength);
    strncpy(new -> name, name, nameLength);

    new -> allFrames = (frame*) malloc(sizeof(frame) * MAXFRAMES);  
    /* initialize all the frames */
    current = (new -> allFrames);
    temp = MAXFRAMES + 1;
    for(f = 1; f < temp; ++f, ++current)
    {
        current -> frameNum = f;
        current -> frameVal = 0;

        memset(current -> roll, ROLL_INIT, ROLLS);
    } /* end for */

    /* only the last roll in frame 11 is '\0' for boundary purposes */
    new -> allFrames[MAXFRAMES - 1].roll[R2] = '\0';

    return new;
} /* end create_player #}}} */

/* remove a player from the game. returns 1 if sucess, 0 if nothing to free */
uint64_t remove_player(player *toRemove)/*#{{{*/
{
    if(toRemove == NULL)
    {
        return 0;
    } /* end if */

    free(toRemove -> name);
    free(toRemove -> allFrames);
    free(toRemove);

    return 1;
} /* end remove_player #}}}*/

/* display player information, including its current frames */
void display_player(player *toDisplay)/*#{{{*/
{
    frame *current = NULL;
    
    if(toDisplay != NULL)
    {
        printf("\nPlayer Name: %s\n",toDisplay -> name);
        
        current = toDisplay -> allFrames;
        do
        {
            display_frame(current);
            ++current;
        }while(current -> roll[R1] != ROLL_INIT && 
               current -> roll[R2] != '\0'); /* end do-while */

        /* handle frame 11 (last roll of frame 10) */
        if(current -> roll[R1] != '-' && current -> roll[R2] == '\0')
        {
            display_frame(current);
        } /* end if */

        printf("\nCurrent total score: %" PRIu64, toDisplay -> scoreTotal);
    } /* end if */
} /* end display_player #}}} */
