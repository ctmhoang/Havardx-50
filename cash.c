#include <cs50.h>
#include <stdio.h>
#include <math.h>

float get_pos_float(void);
int tot_coins(int coins);

int main(void)
{
    float dollars = get_pos_float();
    int coins = round(dollars * 100);
    printf("%i\n",tot_coins(coins));
}

float get_pos_float(void)
{
    float res;
    do
    {
        res = get_float("Change owed: ");
    }while(res < 0);
    return res;
}

int tot_coins(int coins)
{   
    int quaters = coins / 25, dimes = (coins - quaters * 25) / 10,
    nickles = (coins - quaters * 25 - dimes * 10) / 5, pennies = coins - quaters * 25 - dimes * 10 - nickles * 5;
    return quaters + dimes + nickles + pennies;   
}
