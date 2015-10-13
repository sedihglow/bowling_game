/*
    author: James Ross
    note: If you found it, ask before using it! thx! :D

    Handles the I/O with the player and the program

    multiplayer and singleplayer headers handle player control flow.
    
    filename: client.c
*/

                    /* headers */
#include "client.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <inttypes.h>
#include <errno.h>

                    /* private global variables */
/* throw away for input flush macro */
static char __CH__ = 1; /* initialized to 1 to not confuse eof/null/'\0' */

                    /* private prototypes */

                    /* structs */

                    /* definitions */

                    /* macros */


                    /* function source */
/* gather an individual player name, returns NULL on error */
char* gather_pname()/*#{{{*/
{
    char *newName = NULL;
    register size_t nameLength = 0;
    char buffer[N_MAX] = {'\0'};
   
    if(fgets(buffer, N_MAX, stdin) == NULL)
    {
        errno = EIO;
        return NULL;
    } /* end if */
    if(buffer[N_MAX - 1] != '\0')
    {
        input_flush()
    } /* end if */

    nameLength = strlen(buffer);
    buffer[nameLength - 1] = '\0';
    newName = (char*) malloc(sizeof(char) * nameLength);
    strncpy(newName, buffer, nameLength);    

    return newName;
} /* end gather_pname #}}} */

/* gather a single roll input */
char gather_roll()/*#{{{*/
{
    char result = '\0';
    
    do
    {
        printf(">> ");
        result = getchar(); 
        input_flush()
    
        if(result == 'x')
        {
            result = toupper(result);
        } /* end if */
    }while(check_roll(result)); /* end do-while */

    return result;
} /* end gater_roll #}}} */
