#include <cs50.h>
#include <stdio.h>
#include <math.h>

void validate_card(long numbers);
int handle_Luhn(int digit);

int main(void)
{
        validate_card(get_long("Number: "));
}

void validate_card(long numbers)
{
        int counter = 0, totMul2 = 0, totOthers = 0;
        long clone = numbers;
        while(clone > 0)
        {
                counter ++;
                int tempNum = clone % 10;
                clone /= 10;
                if(counter % 2 == 1)
                {
                        totOthers += tempNum;
                }
                else
                {
                        totMul2 += handle_Luhn(tempNum);
                }
        }
        int totAll = totMul2 + totOthers;
        if (totAll % 10 != 0){
                printf("INVALID\n");
        }
        else
        {
                int strNum = numbers / pow(10,counter - 2);
                if(counter == 15 && (strNum == 34 || strNum == 37))
                {
                        printf("AMEX\n");
                }
                else if ((counter == 13 || counter == 16) && strNum / 10 == 4)
                {
                        printf("VISA\n");
                }
                else if (counter == 16 && strNum / 10 == 5 && strNum % 10 >= 0 && strNum % 10 <= 5)
                {
                        printf("MASTERCARD\n");
                }
                else
                {
                        printf("INVALID\n");
                }
        }
}

int handle_Luhn(int digit)
{
    if(digit < 5)
    {
        return digit * 2;    
    }
    else
    {
        digit *= 2;
        return digit % 10 + digit / 10;
    }
}
