#include "helpers.h"
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_NEIGHBORS 9


void swap(RGBTRIPLE* x, RGBTRIPLE* y);
RGBTRIPLE* get_neighbors(int height, int width, RGBTRIPLE image[height][width], int i, int j, int* neighbor_num);


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = round( (float) (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3 );
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int originalRed, originalGreen, originalBlue;
    int sepiaRed, sepiaGreen,sepiaBlue;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            originalRed = image[i][j].rgbtRed;
            originalGreen = image[i][j].rgbtGreen;
            originalBlue = image[i][j].rgbtBlue;

            sepiaRed = round( (float) (0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue) );
            sepiaGreen = round( (float) (0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue) );
            sepiaBlue = round( (float) (0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue) );

            if (sepiaRed > 255)
                image[i][j].rgbtRed = 255;
            else
                image[i][j].rgbtRed = sepiaRed;

            if (sepiaGreen > 255)
                image[i][j].rgbtGreen = 255;
            else
                image[i][j].rgbtGreen = sepiaGreen;

            if (sepiaBlue > 255)
                image[i][j].rgbtBlue = 255;
            else
                image[i][j].rgbtBlue = sepiaBlue;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < floor( (float) width/2); j++)
        {
            swap(&image[i][j], &image[i][width - 1 - j]);
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // for saving the original pixels
    RGBTRIPLE image_copy[height][width];

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            image_copy[i][j] = image[i][j];

    // blurring the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            int averageRed = 0, averageGreen = 0, averageBlue = 0;
            int totalRed = 0, totalGreen = 0, totalBlue = 0;
            int neighbor_num = 0;

            RGBTRIPLE* pointer = get_neighbors(height, width, image_copy, i, j, &neighbor_num);
            RGBTRIPLE neighbors[neighbor_num];

            for (int k = 0; k < neighbor_num; k++)
                neighbors[k] = * (pointer + k);

            free(pointer);

            for (int k = 0; k < neighbor_num; k++)
            {
                totalRed += neighbors[k].rgbtRed;
                totalGreen += neighbors[k].rgbtGreen;
                totalBlue += neighbors[k].rgbtBlue;
            }

            averageRed = round( (float) totalRed / neighbor_num );
            averageGreen = round( (float) totalGreen / neighbor_num );
            averageBlue = round( (float) totalBlue / neighbor_num );

            image[i][j].rgbtRed = averageRed;
            image[i][j].rgbtGreen = averageGreen;
            image[i][j].rgbtBlue = averageBlue;
        }
    }
}


void swap(RGBTRIPLE* x, RGBTRIPLE* y)
{
    RGBTRIPLE temp = *x;
    *x = *y;
    *y = temp;
}

RGBTRIPLE* get_neighbors(int height, int width, RGBTRIPLE image[height][width], int i, int j, int* neighbor_num)
{
    RGBTRIPLE* array = malloc(sizeof(RGBTRIPLE) * MAX_NEIGHBORS);
    int item = 0;

    // CORNER CASES
    // corner: top left
    if (i == 0 && j == 0)
    {
        *neighbor_num = 4;
        array[0] = image[0][0];
        array[1] = image[0][1];
        array[2] = image[1][0];
        array[3] = image[1][1];
    }
    // corner: top right
    else if (i == 0 && j == width - 1)
    {
        *neighbor_num = 4;
        array[0] = image[0][width - 1];
        array[1] = image[0][width - 2];
        array[2] = image[1][width - 2];
        array[3] = image[1][width - 1];
    }
    // corner: bottom left
    else if (i == height - 1 && j == 0)
    {
        *neighbor_num = 4;
        array[0] = image[height - 1][0];
        array[1] = image[height - 1][1];
        array[2] = image[height - 2][0];
        array[3] = image[height - 2][1];
    }
    // corner: bottom right
    else if (i == height - 1 && j == width - 1)
    {
        *neighbor_num = 4;
        array[0] = image[height - 1][width - 1];
        array[1] = image[height - 1][width - 2];
        array[2] = image[height - 2][width - 1];
        array[3] = image[height - 2][width - 2];
    }

    // EDGE CASES
    // top edge
    else if (i == 0 && 0 < j && j < width - 1)
    {
        *neighbor_num = 6;
        for (int row = 0; row < 2; row++)
            for (int column = 0; column < 3; column++)
                array[item++] = image[i + row][j - 1 + column];
    }
    // bottom edge
    else if (i == height - 1 && 0 < j && j < width - 1)
    {
        *neighbor_num = 6;
        for (int row = 0; row < 2; row++)
            for (int column = 0; column < 3; column++)
                array[item++] = image[i - row][j - 1 + column];
    }
    // left edge
    else if (0 < i && i < height - 1 && j == 0)
    {
        *neighbor_num = 6;
        for (int row = 0; row < 3; row++)
            for (int column = 0; column < 2; column++)
                array[item++] = image[i - 1 + row][j + column];
    }
    // right edge
    else if (0 < i && i < height - 1 && j == width - 1)
    {
        *neighbor_num = 6;
        for (int row = 0; row < 3; row++)
            for (int column = 0; column < 2; column++)
                array[item++] = image[i - 1 + row][j - column];
    }

    // REGULAR CASES
    else
    {
        *neighbor_num = 9;
        for (int row = 0; row < 3; row++)
            for (int column = 0; column < 3; column++)
                array[item++] = image[i - 1 + row][j - 1 + column];
    }

    return array;
}