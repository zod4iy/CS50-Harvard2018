// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

typedef struct node
   {
       char word[46];
       struct node *next;
   }
   node;

// create a global variable

node* htable[26];
unsigned int num_words;

// This function will be used in load()
int hash_function(node* node)
{
    int x = (node->word[0])%97;
    return x;
}


// Returns true if word is in dictionary else false
bool check(const char *word)
{

     char copy_word[46];

     for (int i = 0, l = strlen(word); i < l; i++)
        {

            if((int)word[i] >= 65 && (int)word[i] <= 90)
            {
                copy_word[i] = word[i] + 32;
            }
            else
            {
                copy_word[i] = word[i];
            }
        }

    int last = strlen(word);
    copy_word[last] = '\0';

    int hash_v = (copy_word[0])%97;
    node* cursor = htable[hash_v];
    while (cursor != NULL)
    {

        if (strcmp(copy_word, cursor->word) == 0)
        {
            return true;

        }
        cursor = cursor->next;
    }

return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
   FILE* inptr = fopen(dictionary, "r");
   if (inptr == NULL)
   {
       return false;
   }

   char c;
   num_words = 0;

   while (feof(inptr) == 0)
   {
       c = fgetc(inptr);
       if ((int)c == 10)
       num_words++;
   }
   fseek(inptr, 0, SEEK_SET);

   for (int i = 0; i < 26; i++)
   {
       htable[i] = NULL;
   }

   for (int i = 0; i < num_words; i++)
   {

    node* n = malloc(sizeof(node));
    if (n == NULL)
      {
        return false;
      }

       n->next = NULL;

      char dicw[46];
      fscanf(inptr, "%s", dicw);
      strcpy(n->word, dicw);

      int index = hash_function(n);

      for (int j = 0; j < 26; j++)
      {

         if (htable[j] == NULL && j == index)
         {
              htable[j] = n;

         }
         else if (htable[j] != NULL && j == index)
         {
             n->next = htable[j];
             htable[j] = n;

         }
      }


   }

    fclose(inptr);
    return true;

}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
  return num_words;

}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node* cursor;
    for (int i = 0; i < 26; i++)
    {
        cursor = htable[i];
        while (cursor != NULL)
        {
            node* temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
    }

    if (cursor == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}
