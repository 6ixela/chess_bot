#include "bot.h"

#include <stdlib.h>

int evalBoard(struct board *board)
{
    int res = 0;
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 8; j++)
        {
            struct piece *p = board->board[i * 8 + j];
            
            if (p == NULL)
                continue;
            char color = p->color ? -1 : 1;
            
           res += p->value * color;
        } 
    }
    return res;
}