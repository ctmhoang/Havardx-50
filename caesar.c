#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void caesar_cipher(int key);

int main(int argc, string agrv[])
{
    if(argc == 2 && (agrv[1][0] == '-' || isdigit(agrv[1][0])))
    {
        for(int i = 1, n = strlen(agrv[1]); i < n; i ++)
        {
            if(!isdigit(agrv[1][i]))
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
        caesar_cipher(atoi(agrv[1]));
        return 0;
    }
        printf("Usage: ./caesar key\n");
        return 1;
}

void caesar_cipher(int key)
{
    string text = get_string("plaintext: ");
    for(int i = 0, n = strlen(text) ; i < n; i++)
    {
        if(isalpha(text[i]))
        {
            int char_rep;
            bool is_upper = false;
            if(isupper(text[i]))
            {
                is_upper = true;
            }
            char_rep = is_upper ? text[i] - 'A' : text[i] - 'a';
            char_rep = (char_rep + key) % 26;
            text[i] = is_upper ? char_rep + 'A' : char_rep + 'a';
        }
    }
    printf("ciphertext: %s\n", text);
}
