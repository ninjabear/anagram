#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "dict.h"

void showuse(void)
{
        printf ("use:\n\tanagrams <input_chars> [over <number> characters]\n");
}

int charInStr(const char* pszStrToCheck, const char cCharToCheck)
{
        int i;
        if (cCharToCheck=='#') { return -1; } // # means a character has been deleted
        for (i=0; i<strlen(pszStrToCheck); i++)
        {
                if (pszStrToCheck[i]==cCharToCheck)
                {
                        return i;
                }
        }
        return -1;
}

int main(int argc, char *argv[])
{
        if (argc > 3 || argc < 2) { showuse(); return -1; }
        extern struct dict wordlist[]; // dictionary in dict.h (contains pszWord - alphabetical order)
        int i = 0, j, x, nFound=0, nOnlyShowOver;
        if (argc == 3) { nOnlyShowOver = atoi(argv[2]); }
        else { nOnlyShowOver = 0; }
        char* pInputCopy = malloc(MAX_WORDLEN+1); // defined in dict.h +1 for NULL
        if (pInputCopy==NULL)
        {
                printf("malloc error!\n");
                return -1;
        }
        else
        {
                memset(pInputCopy, 0, MAX_WORDLEN+1);
                printf("\n");
        }

        while (wordlist[i].pszWord != NULL)
        {
                x=0;
                if (strlen(wordlist[i].pszWord) > nOnlyShowOver)
                {
                        memcpy(pInputCopy, argv[1], strlen(argv[1]));
                        for (j=0; j<strlen(wordlist[i].pszWord); j++)
                        {
                                int nLocInStr = charInStr(pInputCopy, wordlist[i].pszWord[j]);
                                if (nLocInStr >= 0)
                                {
                                        ++x;
                                        pInputCopy[nLocInStr] = '#';
                                }
                        }
                        if (x == j) {
                                printf ("%s is an anagram of %s\n", wordlist[i].pszWord, argv[1]);
                                ++nFound;
                        }
                        memset(pInputCopy, 0, strlen(argv[1]));
                }
                ++i;
        }

        if(nFound > 0)
        {
                printf("\nI found %d anagrams of %s over %d characters", nFound, argv[1], nOnlyShowOver);
        }
        else { printf("\nI found no anagrams over %d characters:(", nOnlyShowOver); }

        free(pInputCopy);
        return 0;
}
