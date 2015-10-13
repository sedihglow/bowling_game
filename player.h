/*
    author: James Ross
    note: if you found it, and want to use it while bowling, invite me. :D

    this header handles all player information and functionalities.

    filename: player.h */

#ifndef __PLAYER_H__
#define __PLAYER_H__

                    /* headers */
#include <inttypes.h>
#include "frame.h"

                    /* definitions */
#define MAXFRAMES 11   /* 10th frame requires 2 singleFrame's for 3 rolls */


                    /* structs */
/* an individual player of the game //i just lost the game ;D */
typedef struct Player
{
    struct singleFrame *allFrames; /* players frames */
    uint64_t scoreTotal;           /* current total calculatable score */
    char *name;                    /* player name */
} player;

                    /* public functions */

/* initializes a player for the game, returns player or NULL if failure.
   errno gets set on error,
   EINVAL = players name was NULL or invalid
   EAGAIN = memory failed to allocate */
player* create_player(const char *name);

/* remove a player from the game. */
uint64_t remove_player(player *toRemove);

/* display player information, including its current frames */
void display_player(player *toDisplay);
#endif
