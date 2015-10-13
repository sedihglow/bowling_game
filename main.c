/*
    author: james ross

    Main does stuff and things, with that stuff, to see if the stuff makes 
    sense when the stuff goes down. Like animals. but bowling.

    file: main.c
*/

                    /* headers */
#define __need_timespec
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <inttypes.h>
#include <time.h>

#include "game.h"         /* game functionalities */

                    /* definitions */

                    /* macros */


                    /* wtf prototypes */



int main(int argc, char *argv[])
{
    struct timespec *ts = NULL;
    ts = (struct timespec*) malloc(sizeof(struct timespec));
    clock_gettime(CLOCK_BOOTTIME, ts);
    free(ts);

    if(argc == 1 || argc > 2)
    {
        fprintf(stderr,"\n\nCommand must give number of players\n"
                       "$ bowling #ofplayers\n");
        return -1;
    } /* end if */

    play_bowling(strtoul(argv[1], NULL, 10));

    return 0;
} /* end main */
