#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int h = get_int("Height: ");
    for(int i = 0; i <h ; i++)
    {
        for(int j = 0 ; j < h-i-1 ; j ++)
        {
                printf(" ");
        }
        for(int j = 0 ; j < i + 1; j ++)
        {
            printf("#");
        }
        printf("\n");
    }
}
