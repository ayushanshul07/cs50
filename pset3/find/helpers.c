/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{	
    int low = 0;
    int high = n - 1;
    int mid = (high + low) / 2;
    while(low <= high)
    {
        mid = (high + low) / 2;
        if (values[mid] > value)
            high = mid - 1;
        else if(values[mid] < value)
            low = mid + 1;
        else
            return true;
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    for(int i = 0 ; i < n ;++i)
    {
        bool change = false;
        for(int j = 0 ; j < (n - i - 1) ;++j)
        {
            if (values[j] > values[j + 1])
            {
                int temp = values[j];
                values[j] = values[j + 1];
                values[j + 1] = temp;
                change = true;
            }		
        }
        if (!change)
            break;
    }
    return;
}
