#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avg;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            BYTE *b = &image[i][j].rgbtBlue;
            BYTE *g = &image[i][j].rgbtGreen;
            BYTE *r = &image[i][j].rgbtRed;
            avg = (*b + *g + *r) / 3;
            *b = (BYTE) avg;
            *g = (BYTE) avg;
            *r = (BYTE) avg;
        }
    }
}
