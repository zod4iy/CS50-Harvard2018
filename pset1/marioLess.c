#include <stdio.h>
#include <cs50.h>

int main(void)
{
 int n;

    do
    {
     printf ("Height(0-24):");
     n = get_int();
     }
     while (n<0 || n>=24);

for  (int i=0; i<n; i++)
{
      for (int l=0; l<n-i-1; l++)
      {
          printf(" ");
      }
      for (int j=0; j<i+2; j++)
      {
          printf("#");
      }

      printf("\n");
}
return 0;
}