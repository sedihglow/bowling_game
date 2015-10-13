/*
    author: James Ross
    note: if you found it, ask before using other than to bowl! thx :D


    handles the game flow during a multiplayer session

    filename: multiplayer.h
*/

#ifndef __MULTIPLAYER_H__
#define __MULTIPLAYER_H__

#ifndef __PLAYER_H__
#include "player.h"
#endif



#include <inttypes.h>

/* Keep score of an entire game from start to finish */ 
void playfull_multi(player **allplayers, const uint64_t numPlayers);

#endif
