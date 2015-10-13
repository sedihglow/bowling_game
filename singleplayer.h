/*
    author: James Ross
    note: if you found it, ask before using it for something other than bowling.
          thx :D

    handles the flow of the game in a single player instance.

    filename: singleplayer.h
*/

#ifndef __SINGLEPLAYER_H__
#define __SINGLEPLAYER_H__
                    
                    /* headers */
#ifndef __PLAYER_H__
#include "player.h"
#endif


                    /* definitions */
/* MAXFRAMES = 11, as defined in frame.h, which is obtained through player.h */

/* Keep score of an entire game from start to finish */ 
void playfull_single(player *currentp);

#endif
