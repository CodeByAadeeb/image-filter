#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            float average= (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;

            int grayscale_value = (int)(average + 0.5);

            // Assign the same grayscale value to all three channels
            image[i][j].rgbtRed = grayscale_value;
            image[i][j].rgbtGreen = grayscale_value;
            image[i][j].rgbtBlue = grayscale_value;

        
        }
    }
    return;

}


// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sepiaRed = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            float sepiaGreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            float sepiaBlue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;

            int roundedred;
            int roundedgreen;
            int roundedblue;
            if (sepiaRed - (int)sepiaRed >= 0.5) {
                roundedred = (int)sepiaRed + 1;
            } else {
                roundedred = (int)sepiaRed;
            }

            // Rounding sepiaGreen
            if (sepiaGreen - (int)sepiaGreen >= 0.5) {
                roundedgreen = (int)sepiaGreen + 1;
            } else {
                roundedgreen = (int)sepiaGreen;
            }

            // Rounding sepiaBlue
            if (sepiaBlue - (int)sepiaBlue >= 0.5) {
                roundedblue = (int)sepiaBlue + 1;
            } else {
                roundedblue = (int)sepiaBlue;
            }

            //for number greater than 255
            if (roundedred > 255)
            {
                roundedred = 255;
            }
            if (roundedgreen > 255)
            {
                roundedgreen = 255;
            }
            if (roundedblue > 255)
            {
                roundedblue = 255;
            }

            // first rounoff the number even if it is greater than 255
            // then make the function that chooses the lesser of two numbers

            image[i][j].rgbtRed = roundedred;
            image[i][j].rgbtGreen = roundedgreen;
            image[i][j].rgbtBlue = roundedblue;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Swap pixels
            // we can use pointer bcoz in function declaration it is not a pointer or can we?
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int totalRed = 0; int totalGreen = 0; int totalBlue = 0; int count = 0;


            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;


                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        totalRed += copy[ni][nj].rgbtRed;
                        totalGreen += copy[ni][nj].rgbtGreen;
                        totalBlue += copy[ni][nj].rgbtBlue;
                        count++;
                    }
                }
            }


            image[i][j].rgbtRed = (int)((totalRed / (float)count) + 0.5);
            image[i][j].rgbtGreen = (int)((totalGreen / (float)count) + 0.5);
            image[i][j].rgbtBlue = (int)((totalBlue / (float)count) + 0.5);
        }
    }
    return;
}
