// Helper functions for music

#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int numenator = (int)fraction[0]%48;
    int denominator =(int)fraction[2]%48;
    int d;

    if (denominator == 8)
    {
        d = numenator;
    }
    else
    {
        d = 8/denominator;
    }
return d;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    int f;
    int n = strlen(note);
    int oct;
    int k;
    for (int i = 0; i < n; i++)
    {
        if(note[i]>='0' && note[i]<='9')
        {
            oct = (int)note[i]%48;
        }
    }

    k = 0.5*pow(2, oct);
    // oct1[] = {33, 35, 37, 39, 41, 44, 46, 49, 52, 55, 58, 62}; // start C1...
    if (n == 2)
    {
        switch(note[0])
        {
        case 'C':
        f = roundf(32.7*k);
        break;
        case 'D':
        f = roundf(36.71*k);
        break;
        case 'E':
        f = roundf(41.2*k);
        break;
        case 'F':
        f = roundf(43.65*k);
        break;
        case 'G':
        f = roundf(49*k);
        break;
        case 'A':
        f = roundf(55*k);
        break;
        case 'B':
        f = roundf(61.74*k);
        break;
        }
    }

if (n == 3)
    {
        switch(note[0]+note[1])
        {
        case 'C' + '#':
        case 'D' + 'b':
        f = roundf(34.65*k);
        break;
        case 'D' + '#':
        case 'E' + 'b':
        f = roundf(38.89*k);
        break;
        case 'F' + '#':
        case 'G' + 'b':
        f = roundf(46.25*k);
        break;
        case 'G' + '#':
        case 'A' + 'b':
        f = roundf(51.91*k);
        break;
        case 'A' + '#':
        case 'B' + 'b':
        f = roundf(58.27*k);
        break;

        }

    }

    return f;

}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    int n = strlen(s);
    for (int i = 0; i < n; i++)
    {
        if ((int)s[i] != 32)
        return false;
    }

    return true;
}
