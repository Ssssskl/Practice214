#include <stdio.h>


void neg_max_str(double a[5][2])
{
    int maxim = 0, maxim_str;
    for (int j = 0; j < 2; j++)
    {
        int count = 0;
        for (int i = 0; i < 5; i++)
        {
            if (a[i][j] < 0)
                count++;
        }
        if (count>maxim)
        {
            maxim = count;
            maxim_str = j;
        }      
    }
    for (int i = 0; i < 5; i++)
    {
        printf ("%lf", *a[maxim_str]);
    }   
}
