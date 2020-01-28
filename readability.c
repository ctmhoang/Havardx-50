#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int count_letters(string input);
int count_words(string input);
int count_sentences(string input);
float per_100_words(int input, int words);
void Coleman_Liau_index(int l, int w, int s);

int main(void)
{
    string text = get_string("Text: ");
    Coleman_Liau_index(count_letters(text), count_words(text), count_sentences(text));
}

int count_letters(string input)
//Letters can be any uppercase or lowercase alphabetic characters, but shouldn’t include any punctuation, digits, or other symbols.
{
    int count = 0;
    for (int i = 0 ; i < strlen(input) ; i++)
    {
        if (isalpha(input[i]))
        {
            count ++;
        }
    }
    return count;
}
int count_words(string input)
//assumed that a sentence will not start or end with a space, and a sentence will not have multiple spaces in a row.
{
    if (input[0] == ' ' || strcmp("", input) == 0)
    {
        return 0;
    }
    int count = 1;
    for (int i = 0 ; i < strlen(input) ; i++)
    {
        if (input[i] == ' ')
        {
            count ++;
        }
    }
    return count;
}

int count_sentences(string input)
// considered any sequence of characters that ends with a . or a ! or a ? to be a sentence
{
    int count = 0;
    for (int i = 0 ; i < strlen(input) ; i++)
    {
        if (input[i] == '.' || input[i] == '!' || input[i] == '?')
        {
            count ++;
        }
    }
    return count;
}
void Coleman_Liau_index(int l, int w, int s)
{
    float L = per_100_words(l, w), S = per_100_words(s, w);
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 0)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

float per_100_words(int input, int words)
{
    if (words == 100)
    {
        return input;
    }
    float mul_num = 100.0 / words;
    return input * mul_num;
}
