#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterate over each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Make temporary variable to store the changed color values in
            float k;
            // calculate the average for the red, green, and blue color values of the current pixel
            k = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            // Apply the average value to all three RGB values, making the pixel a shade of gray
            image[i][j].rgbtRed = k;
            image[i][j].rgbtGreen = k;
            image[i][j].rgbtBlue = k;

        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //establish the max value that any RGB value can hold
    const int MAX = 255;
    //iterate over each pixel of the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Apply the sepia equation to each RGB value of the current pixel
            float sepiaRed  =  round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);

            float sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);

            float sepiaBlue =  round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            //Insure that the new sepia red value does not exceed the max
            if (sepiaRed > MAX)
            {
                sepiaRed = MAX;
            }
            //Insure that the new sepia green value does not exceed the max
            if (sepiaGreen > MAX)
            {
                sepiaGreen = MAX;
            }
            //Insure that the new sepia blue value does not exceed the max
            if (sepiaBlue > MAX)
            {
                sepiaBlue = MAX;
            }
            //Assign the new values to each pixel to change the color of the image
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        int k = width - 1;
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][k];
            image[i][k] = tmp;
            k--;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    float avgred;
    float avggreen;
    float avgblue;
    int counter;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //set values back to 0
            avgred = 0;
            avggreen = 0;
            avgblue = 0;
            counter = 0;

            //current pixel average
            avgred = image[i][j].rgbtRed;
            avggreen = image[i][j].rgbtGreen;
            avgblue = image[i][j].rgbtBlue;
            counter++;

            // right pixel average
            if (j < width - 1)
            {
                avgred = avgred + image[i][j + 1].rgbtRed;
                avggreen = avggreen + image[i][j + 1].rgbtGreen;
                avgblue = avgblue + image[i][j + 1].rgbtBlue;
                counter++;
            }

            //left pixel average
            if (j > 0)
            {
                avgred = avgred + image[i][j - 1].rgbtRed;
                avggreen = avggreen + image[i][j - 1].rgbtGreen;
                avgblue = avgblue + image[i][j - 1].rgbtBlue;
                counter++;
            }

            // top pixel average
            if (i > 0)
            {
                avgred = avgred + image[i - 1][j].rgbtRed;
                avggreen = avggreen + image[i - 1][j].rgbtGreen;
                avgblue = avgblue + image[i - 1][j].rgbtBlue;
                counter++;
            }

            //bottom pixel average
            if (i < height - 1)
            {
                avgred = avgred + image[i + 1][j].rgbtRed;
                avggreen = avggreen + image[i + 1][j].rgbtGreen;
                avgblue = avgblue + image[i + 1][j].rgbtBlue;
                counter++;
            }

            //top left pixel average
            if (i > 0 && j > 0)
            {
                avgred = avgred + image[i - 1][j - 1].rgbtRed;
                avggreen = avggreen + image[i - 1][j - 1].rgbtGreen;
                avgblue = avgblue + image[i - 1][j - 1].rgbtBlue;
                counter++;
            }

            //top right pixel average
            if (i > 0 && j < width - 1)
            {
                avgred = avgred + image[i - 1][j + 1].rgbtRed;
                avggreen = avggreen + image[i - 1][j + 1].rgbtGreen;
                avgblue = avgblue + image[i - 1][j + 1].rgbtBlue;
                counter++;
            }

            //bottom right pixel average
            if (i < height - 1 && j < width - 1)
            {
                avgred = avgred + image[i + 1][j + 1].rgbtRed;
                avggreen = avggreen + image[i + 1][j + 1].rgbtGreen;
                avgblue = avgblue + image[i + 1][j + 1].rgbtBlue;
                counter++;
            }

            //bottom left pixel average
            if (i < height - 1 && j > 0)
            {
                avgred = avgred + image[i + 1][j - 1].rgbtRed;
                avggreen = avggreen + image[i + 1][j - 1].rgbtGreen;
                avgblue = avgblue + image[i + 1][j - 1].rgbtBlue;
                counter++;
            }

            //find average color of pixels
            avgred = avgred / counter;
            avggreen = avggreen / counter;
            avgblue = avgblue / counter;

            //round values
            avgred = round(avgred);
            avggreen = round(avggreen);
            avgblue = round(avgblue);

            //insure that no RGB values exceed 255
            if (avgred > 255)
            {
                avgred = 255;
            }

            if (avggreen > 255)
            {
                avggreen = 255;
            }

            if (avgblue > 255)
            {
                avgblue = 255;
            }

            tmp[i][j].rgbtRed = avgred;
            tmp[i][j].rgbtGreen = avggreen;
            tmp[i][j].rgbtBlue = avgblue;

        }

    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < height; j++)
        {
            image[i][j].rgbtRed = tmp[i][j].rgbtRed;
            image[i][j].rgbtGreen = tmp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = tmp[i][j].rgbtBlue;
        }
    }

    return;
}
