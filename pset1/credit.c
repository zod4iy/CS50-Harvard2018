#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    long long cc_number;
    int n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11, n12, n13, n14, n15, n16;
    int sum2, check_sum;
    do
    {
        cc_number = get_long_long("Number: ");
    }
    while (cc_number<=0);
   // It must be array
    n1 = cc_number%10;
    n2 = (cc_number%100-cc_number%10)/10;
    n3 = (cc_number%1000-cc_number%100)/100;
    n4 = (cc_number%10000-cc_number%1000)/1000;
    n5 = (cc_number%100000-cc_number%10000)/10000;
    n6 = (cc_number%1000000-cc_number%100000)/100000;
    n7 = (cc_number%10000000-cc_number%1000000)/1000000;
    n8 = (cc_number%100000000-cc_number%10000000)/10000000;
    n9 = (cc_number%1000000000-cc_number%100000000)/100000000;
    n10 = (cc_number%10000000000-cc_number%1000000000)/1000000000;
    n11 = (cc_number%100000000000-cc_number%10000000000)/10000000000;
    n12 = (cc_number%1000000000000-cc_number%100000000000)/100000000000;
    n13 = (cc_number%10000000000000-cc_number%1000000000000)/1000000000000;
    n14 = (cc_number%100000000000000-cc_number%10000000000000)/10000000000000;
    n15 = (cc_number%1000000000000000-cc_number%100000000000000)/100000000000000;
    n16 = (cc_number%10000000000000000-cc_number%1000000000000000)/1000000000000000;

    int a[8] = {n2*2,n4*2,n6*2,n8*2,n10*2,n12*2,n14*2,n16*2};
    for (int i=0; i<8; i++)
    {
        if(a[i]>=10)
        {
            a[i]=1+a[i]%10;
        }
    }
    sum2 = a[0]+a[1]+a[2]+a[3]+a[4]+a[5]+a[6]+a[7];
    check_sum = sum2 + n1 + n3 + n5 + n7 + n9 + n11 + n13 + n15;
    if (check_sum%10 == 0 && cc_number >=1e14 && cc_number<1e15 && n15 == 3 && n14>= 4 && n14<=7 && n14 != 5 && n14 != 6) //  validate Amex
    {
        printf("AMEX\n");
    }
    else if (check_sum%10 == 0 && cc_number >=1e15 && cc_number<1e16 && n16 == 5 && n15>= 1 && n15<6) //  validate Master Card
    {
        printf("MASTERCARD\n");
    }
    else if (check_sum%10 == 0 && cc_number >=1e12 && cc_number<1e13 && n13 == 4) //  validate Visa 13 digits
    {
        printf("VISA\n");
    }
    else if (check_sum%10 == 0 && cc_number >=1e15 && cc_number<1e16 && n16 == 4) //  validate Visa 16 digits
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
return 0;
}
