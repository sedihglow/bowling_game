/*
    author: James Ross

    Handles the I/O with the player and the program

    multiplayer and singleplayer headers handle player control flow.
    
    filename: client.h
*/


#ifndef __CLIENT_H__
#define __CLIENT_H__

                    /* definitions */
#define N_MAX 100 /* max name length */


                    /* macros */
/* clear input buffer if input was longer than size */
#define input_flush()\
while((__CH__ = getchar()) != '\n' && __CH__ != EOF);

/* checks the validity of a roll input */
#define check_roll(result)\
(((result >= '0' && result <= '9') || result == 'X' || result == '/') ? 0 : 1)

                    /* public prototypes */
/* gather an individual player name */
char* gather_pname();

/* gather a single roll input */
char gather_roll();

#endif
