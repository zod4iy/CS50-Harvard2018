#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int alphaB(char p, int key);
int alphaS(char p, int key);

int main(int argc, string argv[])
{
    if (argc == 1 || argc > 2)               // chek argc = 2
    {
        printf("Usage: ./vigenere k\n");
        return 1;
    }

    string k = argv[1];
    int n1 = strlen(k);

    for (int i = 0; i < n1; i++)        // chek in the keyword should be only alphabetical characters
    {
        if (isalpha(k[i]))
        {
            k[i] = k[i];
        }
        else
        {
            printf("Usage: ./vigenere k\n");
            return 1;
        }
    }

    string p = get_string("plaintext :");
    int n2 = strlen(p);
    int key[n2];
    char c[n2]; // this is "ciphertext"
    int i1 = 0;

    for (int i = 0; i < n2; i++) // make keyword reused ciclilaly
    {
        if (isalpha(p[i]))
        {
            i1 = i1 % n1;
            key[i] = (int)k[i1];
            i1++;
        }
        else
        {
            key[i] = 0;
        }

    //  printf("%c", key[i]);
    }

    int num_p[n2];
    printf("ciphertext:");
    for (int i = 0; i < n2; i++)
    {
        if (isalpha(p[i]) && isupper(p[i]))
        {
            num_p[i] = alphaB(p[i], key[i]);   // make array of numbers = alphabetical index of char + key
            c[i] = 'A' + num_p[i];
        }
        else if (isalpha(p[i]) && islower(p[i]))
        {
            num_p[i] = alphaS(p[i], key[i]);
            c[i] = 'a' + num_p[i];
        }
        else
        {
            c[i] = p[i];
        }
        printf("%c", c[i]);
    }
    printf("\n");
    return 0;
}

int alphaB(char p, int key)
{
    int k;
    if ((int)p % 65 + key % 65 > 25 && key < 97)
    {
        k = (int)p % 65 + key % 65 - 26;
    }
    else if ( (int)p % 65 + key % 65 <= 25 && key < 97)
    {
        k = (int)p % 65 + key % 65;
    }

    if ((int)p % 65 + key % 97 > 25 && key >= 97)
    {
        k = (int)p % 65 + key % 97 - 26;
    }
    else if ((int)p % 65 + key % 97 <= 25 && key >= 97)
    {
        k = (int)p % 65 + key % 97;
    }

    return k;
}

int alphaS(char p, int key)
{
    int k;
     if ((int)p % 97 + key % 65 > 25 && key < 97)
    {
        k = (int)p % 97 + key % 65 - 26;
    }
    else if ((int)p % 97 + key % 65 <= 25 && key < 97)
    {
        k = (int)p % 97 + key % 65;
    }

    if ((int)p % 97 + key % 97 > 25 && key >= 97)
    {
        k = (int)p % 97 + key % 97 - 26;
    }
    else if ((int)p % 97 + key % 97 <= 25 && key >= 97)
    {
        k = (int)p % 97 + key % 97;
    }

    return k;
}