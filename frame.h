/*
    author: James Ross

    This header handles all the individual frame functionalities

    filename: frame.h */

#ifndef __FRAME_H__
#define __FRAME_H__
                    /* headers */
#include <inttypes.h>


                    /* definitions */
#define ROLLS     2    /* rolls per frame */
#define R1        0    /* roll 1 */
#define R2        1    /* roll 2 */
#define ROLL_INIT '-'  /* initializer for all playable rolls */

                    /* structs */
/* a single bowling frame */
typedef struct singleFrame
{
    uint64_t frameNum;    /* frames designated number */
    uint64_t frameVal;    /* frames individual score */

    char roll[ROLLS];     /* result of roll */
} frame;

                    /* public prototypes */

/* Play a single frame for a given player */
void play_frame(frame *currFrame);

/* play bonus roll on 10th frame, sets roll values appropriately,
   returns 1 on success, 0 if incorrect frame was given */
uint64_t yes_bonus_r(frame *currFrame);

/* display a single frame */
void display_frame(frame *toDisplay);

#endif
