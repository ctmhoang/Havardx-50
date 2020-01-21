#include <cs50.h>
#include <stdio.h>

int get_pos(void);

int main(void)
{
    int h = get_pos();
    for(int i = 0; i <h ; i++)
    {
        for(int j = 0 ; j < h-i-1 ; j ++)
        {
                printf(" ");
        }   
        for(int j = 0 ; j < i+1 ; j ++)
        {
                printf("#");
        }  
        printf("\n");
    }
}
int get_pos(void)
{
    int res;
    do
    {
        res = get_int("Height: ");
    }while(!(res > 0 && res < 9));
    return res;
}
