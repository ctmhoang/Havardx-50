#include "helpers.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>


#define PADDING  1
#define MAX_RGB_VAL 255


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float avg;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            BYTE *b = &image[i][j].rgbtBlue;
            BYTE *g = &image[i][j].rgbtGreen;
            BYTE *r = &image[i][j].rgbtRed;
            avg = (*b + *g + *r) / 3.0;
            *b = (BYTE) round(avg);
            *g = (BYTE) round(avg);
            *r = (BYTE) round(avg);
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


void copyPixelsFromTmp(int height, int width, RGBTRIPLE mutated[height][width], RGBTRIPLE origin[height][width])
{
    for(int i = 0 ; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            origin[i][j].rgbtBlue = mutated[i][j].rgbtBlue;
            origin[i][j].rgbtGreen = mutated[i][j].rgbtGreen;
            origin[i][j].rgbtRed = mutated[i][j].rgbtRed;
        }
    }
}

void boxBlur(int currCol, int currRow, int maxHeight, int maxWidth, RGBTRIPLE originImage[maxHeight][maxWidth], RGBTRIPLE *mutatedPixel)
{
    int r = 0;
    int g = 0;
    int b = 0;
    float counter = 0;

    for(int i = -1 ; i < 2 ; i++)
    {
        if(currCol + i < 0 || currCol + i > maxHeight - PADDING) continue;

        for(int j = -1 ; j < 2 ; j++)
        {
            if(j + currRow < 0 || j + currRow > maxWidth - PADDING) continue;
            counter ++;
            r += originImage[currCol +  i][currRow + j].rgbtRed;
            b += originImage[currCol +  i][currRow + j].rgbtBlue;
            g += originImage[currCol +  i][currRow + j].rgbtGreen;
        }
    }

    mutatedPixel->rgbtBlue = round(b / counter);
    mutatedPixel->rgbtGreen = round(g / counter);
    mutatedPixel->rgbtRed = round(r / counter);
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE mutatedImage[height][width];

    for(int i = 0 ; i < height ; i ++)
    {
        for(int j = 0 ; j < width ; j++)
        {
            boxBlur(i, j, height, width, image, &mutatedImage[i][j]);
        }
    }
    copyPixelsFromTmp(height, width, mutatedImage, image);
}

const int GX[3][3] = {{-1,0,1}, {-2,0,2}, {-1,0,1}};
const int GY[3][3] = {{-1,-2,-1}, {0,0,0}, {1,2,1}};

BYTE safeRGBval(int val){
    return val > MAX_RGB_VAL ? MAX_RGB_VAL : val;
}


typedef struct {
    int r;
    int b;
    int g;
} RGBOVERFLOW;

RGBOVERFLOW calcGx(int currCol, int currRow, int height, int width, RGBTRIPLE image [height][width])
{
    RGBOVERFLOW res;

    int r = 0;
    int g = 0;
    int b = 0;

   for(int i = -1 ; i < 2 ; i++)
    {
        if(currCol + i < 0 || currCol + i > height - PADDING) continue;

        for(int j = -1 ; j < 2 ; j++)
        {
            if(j + currRow < 0 || j + currRow > width - PADDING) continue;

            r += image[currCol +  i][currRow + j].rgbtRed * GX[i+ 1][j + 1];
            b += image[currCol +  i][currRow + j].rgbtBlue * GX[i+ 1][j + 1];
            g += image[currCol +  i][currRow + j].rgbtGreen * GX[i+ 1][j + 1];
        }
    }

    res.r = r;
    res.b = b;
    res.g = g;
    return res;
}

RGBOVERFLOW calcGy(int currCol, int currRow, int height, int width, RGBTRIPLE image [height][width])
{
   RGBOVERFLOW res;

    int r = 0;
    int g = 0;
    int b = 0;

    for(int i = -1 ; i < 2 ; i++)
    {
        if(currCol + i < 0 || currCol + i > height - PADDING) continue;

        for(int j = -1 ; j < 2 ; j++)
        {
            if(j + currRow < 0 || j + currRow > width - PADDING) continue;

            r += image[currCol +  i][currRow + j].rgbtRed * GY[i+ 1][j + 1];
            b += image[currCol +  i][currRow + j].rgbtBlue * GY[i+ 1][j + 1];
            g += image[currCol +  i][currRow + j].rgbtGreen * GY[i+ 1][j + 1];

        }
    }

    res.r = r;
    res.b = b;
    res.g = g;
    return res;
}


void combineTwoKernel(RGBOVERFLOW x, RGBOVERFLOW y, RGBTRIPLE *mutatedPixel)
{
    mutatedPixel->rgbtRed = safeRGBval(round(hypot(x.r, y.r)));
    mutatedPixel->rgbtBlue = safeRGBval(round(hypot(x.b, y.b)));
    mutatedPixel->rgbtGreen =  safeRGBval(round(hypot(x.g, y.g)));
}

void sobelOp(int currCol, int currRow, int height, int width, RGBTRIPLE image [height][width], RGBTRIPLE *mutatedPixel)
{

    combineTwoKernel(calcGx(currCol, currRow, height, width, image), calcGy(currCol, currRow, height, width, image), mutatedPixel);
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE mutatedImage[height][width];


    for(int i = 0 ; i < height ; i ++)
    {
        for(int j = 0 ; j < width ; j ++)
        {
            sobelOp(i, j, height, width, image, &mutatedImage[i][j]);
        }
    }
    copyPixelsFromTmp(height, width, mutatedImage, image);
}
