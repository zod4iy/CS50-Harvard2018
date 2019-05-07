#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
  float n, x, y, dollars;
  float q=0;
  float d=0;
  float nick=0;
  float p=0;
  float numCoins;
  do
  {
      printf("Change owed:");
      n = get_float();
  }
  while (n<0);
  x = modff(n, &dollars);
  x = roundf(x*100);
  //printf("Cent:%.0f\n",x);
  //printf("Dollars:%.0f\n",dollars);
  y = x;
  x=x+dollars*100;
  while (x-25>=0)
  {
      q=q+1;
      x=x-25;
  }
  while (x-10>=0)
  {
      d=d+1;
      x=x-10;
  }
  while (x-5>=0)
  {
      nick=nick+1;
      x=x-5;
  }
  while (x-1>=0)
  {
      p=p+1;
      x=x-1;
  }
  numCoins = q+d+nick+p;
 // printf("Dollars:%.0f\n",dollars);
 // printf("Cent:%.0f\n",y);
  printf("%.0f\n",numCoins);
  return 0;
}
