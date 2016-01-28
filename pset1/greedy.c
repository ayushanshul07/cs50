#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float change;
    do
    {
        printf("O hai! How much change is owed?\n");
        change = GetFloat();
    }
    while(change < 0);
    change = change * 100;
    change = round(change);
    
    int quarters = (int) change/ 25;
    change = change - (25 * quarters);
    
    int dimes = (int) change/ 10;
    change = change - (10 * dimes);
    
    int nickels =  (int) change/ 5;
    change = change - (5 * nickels);
        
    int pennies = (int) change/ 1;
    change = change - (1 * pennies);
       
    int total = quarters + dimes + nickels + pennies;
    
    printf("%d\n",total);

}
