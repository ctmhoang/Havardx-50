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

void swapRGBt(RGBTRIPLE *pixel, RGBTRIPLE *oPixel)
{
    RGBTRIPLE tmp;

    tmp.rgbtBlue = pixel->rgbtBlue;
    tmp.rgbtGreen = pixel->rgbtGreen;
    tmp.rgbtRed = pixel->rgbtRed;

    pixel->rgbtBlue = oPixel->rgbtBlue;
    pixel->rgbtGreen = oPixel->rgbtGreen;
    pixel->rgbtRed = oPixel->rgbtRed;

    oPixel->rgbtBlue = tmp.rgbtBlue;
    oPixel->rgbtGreen = tmp.rgbtGreen;
    oPixel->rgbtRed = tmp.rgbtRed;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE *mPixel  = &image[i][j];
            RGBTRIPLE *pixel  = &image[i][width - j - PADDING];

            swapRGBt(mPixel, pixel);
        }
    }
}
