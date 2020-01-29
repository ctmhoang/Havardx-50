#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void substitute_text(string keys);
int get_index(char letter, string text);

int main(int agrc, string agrv[])
{
    if(agrc == 2)
    {
        if(strlen(agrv[1]) != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
        for(int i = 0; i < 26; i++)
        {
            char letter = agrv[1][i];
            if(!isalpha(letter))
            {
                printf("Key must only contain alphabetic characters.\n");
                return 1;
            }
            else if(get_index(letter, agrv[1]) != i)
            {
                printf("Key must not contain repeated characters.\n");
                return 1;
            }
        }
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    substitute_text(agrv[1]);
    return 0;
}

void substitute_text(string keys)
{
    string text = get_string("plaintext: ");
    for(int i = 0 , n = strlen(text); i < n ; i++)
    {
        if(isalpha(text[i]))
        {
            bool is_upper = false;
            if(isupper(text[i]))
            {
                is_upper = true;
            }
            int letter_rep = is_upper ? text[i] - 'A' : text[i] - 'a';
            text[i] = is_upper ? toupper(keys[letter_rep]) : tolower(keys[letter_rep]);
        }
    }
    printf("ciphertext: %s\n" ,text);
}

int get_index(char letter, string text)
{
    int len = -1;
    for(int i = 0, n = strlen(text); i < n; i++)
    {
        if(text[i] == letter)
        {
            len = i;
            break;
        }
    }
    return len;
}
