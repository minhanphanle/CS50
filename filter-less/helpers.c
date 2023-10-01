#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //loop through row
    for (int i = 0; i < height; i++)
    {
        //loop through column
        for (int j = 0; j < width; j++)
        {
            int average = round((image[i][j].rgbtBlue + image[i][j].rgbtRed +
                            image[i][j].rgbtGreen)/3.0);

            image[i][j].rgbtBlue = average;
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //loop through row
    for (int i = 0; i < height; i++)
    {
        //loop through column
        for (int j = 0; j < width; j++)
        {
            float red = image[i][j].rgbtRed;
            float green = image[i][j].rgbtGreen;
            float blue = image[i][j].rgbtBlue;

            int sepiaRed = round(.393 * red + .769 * green + .189 * blue);
            int sepiaGreen = round(.349 * red + .686 * green + .168 * blue);
            int sepiaBlue = round(.272 * red + .534 * green + .131 * blue);

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    //loop through row
    for (int i = 0; i < height; i++)
    {
        //loop through column
        for (int j = 0; j < (width/2); j++)
        {
            temp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //create a copy of the photo
    RGBTRIPLE temp[height][width];

    //loop through row
    for (int i = 0; i < height; i ++)
    {
        //loop through column
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];

            int counter = 0;
            float total_red = 0;
            float total_blue = 0;
            float total_green = 0;

            //neighboring pixel
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    int current_i = i + x;
                    int current_j = j + y;

                    //check for valid neighbors
                    if ((current_i < 0) || (current_i > height - 1) || (current_j < 0) || (current_j > width - 1))
                    {
                        continue;
                    }

                    total_red += image[current_i][current_j].rgbtRed;
                    total_blue += image[current_i][current_j].rgbtBlue;
                    total_green += image[current_i][current_j].rgbtGreen;
                    counter++;
                }
            }

            temp[i][j].rgbtRed = round(total_red/counter);
            temp[i][j].rgbtBlue = round(total_blue/counter);
            temp[i][j].rgbtGreen = round(total_green/counter);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
        }
    }

    return;
}
