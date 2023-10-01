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

            //average red, blue, green of neighbors
            temp[i][j].rgbtRed = round(total_red/counter);
            temp[i][j].rgbtBlue = round(total_blue/counter);
            temp[i][j].rgbtGreen = round(total_green/counter);
        }
    }

    //copy to the real image
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


// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //kernel Gx
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};

    //kernel Gy
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            int redGx = 0;
            int redGy = 0;
            int greenGx = 0;
            int greenGy = 0;
            int blueGx = 0;
            int blueGy = 0;

            //loop through neighboring pixels
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    int current_i = i + x;
                    int current_j = j + y;

                    //check for edge pixels
                    if ((current_i < 0) || (current_i > height - 1) || (current_j < 0) || (current_j > width - 1))
                    {
                        continue;
                        // image[current_i][current_j].rgbtRed = 0;
                        // image[current_i][current_j].rgbtGreen = 0;
                        // image[current_i][current_j].rgbtBlue = 0;
                    }
                    // Calculate Gx for each color
                    redGx += image[current_i][current_j].rgbtRed * Gx[x + 1][y + 1];
                    greenGx += image[current_i][current_j].rgbtGreen * Gx[x + 1][y + 1];
                    blueGx += image[current_i][current_j].rgbtBlue * Gx[x + 1][y + 1];

                    // Calculate Gy for each color
                    redGy += image[current_i][current_j].rgbtRed * Gy[x + 1][y + 1];
                    greenGy += image[current_i][current_j].rgbtGreen * Gy[x + 1][y + 1];
                    blueGy += image[current_i][current_j].rgbtBlue * Gy[x + 1][y + 1];


                }
            }

            //calculate sqrt Gx^2 and Gy^2 for each color + maximum 255
            int sqrtRed = round(sqrt(redGx * redGx + redGy * redGy));
            int sqrtGreen = round(sqrt(greenGx * greenGx + greenGy * greenGy));
            int sqrtBlue = round(sqrt(blueGx * blueGx + blueGy * blueGy));

            if (sqrtRed > 255)
            {
                sqrtRed = 255;
            }
            if (sqrtBlue > 255)
            {
                sqrtBlue = 255;
            }
            if (sqrtGreen > 255)
            {
                sqrtGreen = 255;
            }

            //store in temp
            temp[i][j].rgbtRed = sqrtRed;
            temp[i][j].rgbtBlue = sqrtBlue;
            temp[i][j].rgbtGreen = sqrtGreen;

        }
    }

    //copy to the real image
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
