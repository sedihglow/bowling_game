/*
    author: James Ross
    note: if you found it, ask before using unless its bowling! then invite :P

    handles the raw functionalities of the same, such as score and display

    filename: game.h
*/

#ifndef __GAME_H__
#define __GAME_H__

#include <inttypes.h>
#include "singleplayer.h"
#include "multiplayer.h"

                    /* macros */
#define check_errno(errmsg) if(errno){ perror(errmsg);\
                                       errno = 0;\
                                       return 0;}

                    /* public functions */
/* introduce the game, and some of its functionalities */
void introduction();

/* start the proper version of the game (single/multi) */
uint64_t play_bowling(const uint64_t numPlayers);

/* calculated the total score a player currently has unless starting frame is
   11, in which case it returns frame 11's frameVal */
int64_t calc_score(frame *currFrame); 

/* returns the result of frame 11, the bonus roll of frame 10 */
int64_t calc_bonus_r(frame *currFrame);

/* converts a bowling roll into its numerical equivalent. Pass NULL for preR,
   unless calculating first roll. Used for calculating spare value, no spare on
   first roll. */
uint64_t conv_r(const uint64_t preR, const char toConv);

/* display current gamre results */
void display_game(player **players, uint64_t *leadScore, const uint64_t numPlayers);

/* end the current game */
void end_game();

#endif
