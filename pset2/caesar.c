#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int alphaB(int n, int k);
int alphaS(int n, int k);

int main(int argc, string argv[])
{
    if (argc == 1 || argc > 2)
    {
        printf("Usage: ./caesar k\n");
        return 1;
    }
    float key;
    float after_point, key_check_float; // variables for check
    string k = argv[1];
    key = atof(k);
    after_point = modff(key, &key_check_float);

    if (key <= 0 || after_point > 0)
    {
        printf("Usage: ./caesar k\n");
        return 1;
    }

    string plaintext = get_string("plaintext:  ");
    int n = strlen(plaintext);
    int plain_t[n];
    char ciphertext[n];

    printf("ciphertext: ");

    for (int i = 0; i < n; i++)
    {
        plain_t[i] = (int) plaintext[i];

       if (plaintext[i] < 'A' || plaintext[i] > 'z' || plaintext[i] == '[' || plaintext[i] == '\\' || plaintext[i] == ']'
            || plaintext[i] == '^' || plaintext[i] == '_' || plaintext[i] == '\'')
       {
           ciphertext[i] = plaintext[i];
       }
       else if (isupper(plaintext[i]))
       {
           plain_t[i] = alphaB(plain_t[i], key);
           ciphertext[i] = 'A' + plain_t[i];
       }
       else
       {
           plain_t[i] = alphaS(plain_t[i], key);
           ciphertext[i] = 'a' + plain_t[i];
       }

    printf("%c", ciphertext[i]);
   }
   printf("\n");
   return 0;
}

int alphaB(int n, int k)
{
    if (n % 65 + k % 26 > 25)
    {
        n = n % 65 + k % 26 - 26;
    }
    else
    {
        n = n % 65 + k % 26;
    }

    return n;
}

int alphaS(int n, int k)
{
    if (n % 97 + k % 26 > 25)
    {
        n = n % 97 + k % 26 - 26;
    }
    else
    {
        n = n % 97 + k % 26;
    }

    return n;
}