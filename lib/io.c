#include <stdio.h>
#include <stdlib.h>

#include "io.h"

// from http://stackoverflow.com/questions/314401/how-to-read-a-line-from-the-console-in-c
char * getline(void) 
{
    char * line = malloc(100), * linep = line;
    size_t lenmax = 100, len = lenmax;
    int c;

    if(line == NULL)
        return NULL;

    for(;;) {
        c = fgetc(stdin);
        if(c == EOF)
            break;

        if(c == '\'')
          continue; // prevent SQL injection attacks

        if(c == '\n')
          break;

        if(--len == 0) {
            len = lenmax;
            char * linen = realloc(linep, lenmax *= 2);

            if(linen == NULL) {
                free(linep);
                return NULL;
            }
            line = linen + (line - linep);
            linep = linen;
        }

        if((*line++ = c) == '\n')
            break;
    }
    *line = '\0';
    return linep;
}

unsigned int getchoice()
{
  char * line = NULL;
  unsigned int choice;

  if((line = getline()) == NULL)
  {
    return 0;
  }
  else
    choice = strtol(line, NULL, 10);

  free(line);
  return choice;
} 
