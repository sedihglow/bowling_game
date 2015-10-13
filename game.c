/*
    author: James Ross
    note: if you found it, ask before using unless its bowling! then invite :P

    handles the raw functionalities of the same, such as score and display as
    described in game.h

    filename: game.c
*/

                    /* headers */
#include "game.h"
#include "client.h"

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#define NDEBUG /* prevents assert.h */
#include <assert.h>

                    /* private functions */

                    /* functions source */
/* introduce the game, and some of its functionalities */
void introduction()/*#{{{*/
{
    printf("\n\n----Insert game introduction here----\n\n");
} /* end introduction #}}} */

/* start the proper version of the game (single/multi) */
uint64_t play_bowling(const uint64_t numPlayers)/*#{{{*/
{
    player *allPlayers[numPlayers]; /* C90 does not allow variable length // */
    char *playerNames[numPlayers];  /* arrays, To make pedantic, malloc these two **'s */
    register uint64_t i = 0;

    assert(numPlayers > 0); /* 0 players not possible, should i make this a
                               return error? Function runs fine w/o */
    /* gather player names */
    for(/*i=0*/; i < numPlayers; ++i)
    {
        printf("\nEnter player %" PRIu64 "'s name.\n>> ", i + 1);
        playerNames[i] = gather_pname(numPlayers);
        check_errno("play_bowling: gather_pname: failed to get name")
    } /* end for */

    /* initialize each player with their name */
    for(i = 0; i < numPlayers; ++i)
    {
        assert(playerNames[i] != NULL);

        allPlayers[i] = create_player(playerNames[i]);
        /* playerName no longer required after creation! save dat runtime mem */
        free(playerNames[i]);
    } /* end for */

    /* game mode */
    if(numPlayers == 1)
    {
        playfull_single(*allPlayers);
    } /* end if */
    else
    {   
        /* assumes not 0, see assertion */
        playfull_multi(allPlayers, numPlayers);
    } /* end else */
    
    end_game(allPlayers, numPlayers);

    return 1;
} /* end play_bowling #}}} */

/* calculated the total score a player currently has, not including potential
   bonus roll */
int64_t calc_score(frame *currFrame)/*#{{{*/
{
    register uint64_t first = 0;     /* value of first roll after current */
    register uint64_t second = 0;    /* value of second roll after current */
    register uint64_t highFrame = 0; /* current highest frame to calculate */
    register uint64_t totalScore = 0;/* potentially does not count init frame */

    char *currRoll = NULL;

    assert(currFrame != NULL && currFrame -> frameNum > 0);

    highFrame  = currFrame -> frameNum;
    currRoll = currFrame -> roll;
    
    /* handle whatever the initial frame is. 10 && 2 have special cases */

    first = conv_r(0, currRoll[R1]);
    second = conv_r(0, currRoll[R2]); /* 0 causes a '/' to return 10 */

    if((first != 10 && second != 10) || highFrame == 10)/* 10 = X and / */
    {   
        totalScore += currFrame -> frameVal = first + second;
        second = conv_r(first, currRoll[R2]); /* get real value */
    } /* end if */
    else 
    {   /* handles what happens if first frame ended in '/' */
        --currFrame;
        if(highFrame == 2 && currFrame -> roll[R2] == '/')
        {
            totalScore += currFrame -> frameVal = 10 + first;
        } /* end if */

        /* if previous frame was a strike, adjust the value. This will
           happen no matter what after next frame, but doing this makes
           the results accurate right away, rather than after next frame input,
           END result is OK without this. */
        if(currFrame -> roll[R1] == 'X' && second == 10)
        {
            currFrame -> frameVal = 20;
        } /* end if */

        ++currFrame; /* go back to current */

        second = conv_r(first, currRoll[R2]); /* get real value */
    } /* end else if */

    /* rest of frames */
    for(--highFrame, --currFrame; highFrame > 0; --highFrame, --currFrame)
    {
        currRoll = currFrame -> roll;

        if(currRoll[R1] != 'X' && currRoll[R2] != '/')
        {
            first = conv_r(0, currRoll[R1]);
            second = conv_r(first, currRoll[R2]);
            totalScore += currFrame -> frameVal = first + second;
        } /* end if */
        /* handle a spare and a strike situation */
        else if(currRoll[R2] == '/')
        {
            totalScore += currFrame -> frameVal = 10 + first;
            first = conv_r(0, currRoll[R1]);
            second = conv_r(first, currRoll[R2]);

            --currFrame;
            ++currFrame;
        } /* end if */
        else /* if(currFrame -> roll[R1] == 'X') */
        {
            totalScore += currFrame -> frameVal = 10 + first + second;
            second = first;
            first = conv_r(0, currRoll[R1]);
        } /* end if */
    } /* end for */
    
    return totalScore;
} /* end calc_score #}}} */

/* returns the result of frame 11, the bonus roll of frame 10 */
/* OPT: NOTE: dont like that it goes through all frames every time, could adjust
   if desired */
int64_t calc_bonus_r(frame *currFrame)/*#{{{*/
{
    register uint64_t totalScore = 0;

    if(currFrame -> frameNum == 11)
    {
        totalScore = currFrame -> frameVal = conv_r(0, currFrame -> roll[R1]);
        return totalScore;
    } /* end if */
    
    return -1;
} /* end calc_bonus_r #}}} */

/* converts a bowling roll into its numerical equivalent. Pass NULL for preR,
   unless calculating first roll. Used for calculating spare value, no spare on
   first roll. */
uint64_t conv_r(const uint64_t preR, const char toConv)/*#{{{*/
{
    char toStr[2] = {'\0'};   /* adds null to toConv for conversion */
    toStr[0] = toConv;

    assert(check_roll(toConv) == 0 || toConv == '\0' || toConv == '-');

    if(toConv == '\0' || toConv == '-')
    {
        return 0;
    } /* end if */

    if(toConv == '/')
    {
        return 10 - preR;
    } /* end if */

    if(toConv == 'X')
    {
        return 10;
    } /* end if */

    /* toConv is neither a strike nore spare */
    return strtoul(toStr, NULL, 10);
} /* end conv_r #}}} */

/* display current game results */
/* BUG NOTE: If there is a tie, it is not considered */
void display_game(player **players, uint64_t *leadScore,  const uint64_t numPlayers)/*#{{{*/
{
    register uint64_t i = 0;
    register uint64_t winner = 0;

    for(/*i=0*/; i < numPlayers; ++i)
    {
        display_player(players[i]);
        if(leadScore && players[i] -> scoreTotal > *leadScore)
        {
            *leadScore = players[i] -> scoreTotal; 
            winner = i;
        } /* end if */
    } /* end for */
    
    printf("\n\nThe current top player is: %s\n\n", players[winner] -> name);
} /* end display_game #}}} */

/* end the current game */
void end_game(player **allPlayers, const int64_t numPlayers)/*#{{{*/
{
    register uint64_t i = 0; 

    for(i = 0; i < numPlayers; ++i)
    {
        remove_player(allPlayers[i]);
    } /* end for */
} /* end end_game #}}} */

