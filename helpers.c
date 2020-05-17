#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Find the average of the overall RGB value and set it equal to the average
            float averageRGB = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = image[i][j].rgbtGreen = image[i][j].rgbtRed = averageRGB;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through each pixel
    for (int i = 0; i < height; i++)
    {
        // Loop only half-way through the row
        for (int j = 0; j < width / 2; j++)
        {
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
    // Declare temporary variable
    RGBTRIPLE temp[height][width];

    // Copy original image into temp
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    // Loop through each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Define pixel position shortcuts
            #define topLeft (image[i - 1][j - 1])
            #define topMid (image[i - 1][j])
            #define topRight (image[i - 1][j + 1])
            #define left (image[i][j - 1])
            #define mid (image[i][j]) // Current pixel
            #define right (image[i][j + 1])
            #define botLeft (image[i + 1][j - 1])
            #define botMid (image[i + 1][j])
            #define botRight (image[i + 1][j + 1])

            // Calculate for upper-left pixel
            if (i == 0 && j == 0)
            {
                temp[i][j].rgbtRed = round((mid.rgbtRed + right.rgbtRed + botMid.rgbtRed + botRight.rgbtRed) / 4.0);
                temp[i][j].rgbtGreen = round((mid.rgbtGreen + right.rgbtGreen + botMid.rgbtGreen + botRight.rgbtGreen) / 4.0);
                temp[i][j].rgbtBlue = round((mid.rgbtBlue + right.rgbtBlue + botMid.rgbtBlue + botRight.rgbtBlue) / 4.0);
            }

            // Calculate for upper-right pixel
            else if (i == 0 && j == width - 1)
            {
                temp[i][j].rgbtRed = round((mid.rgbtRed + left.rgbtRed + botMid.rgbtRed + botLeft.rgbtRed) / 4.0);
                temp[i][j].rgbtGreen = round((mid.rgbtGreen + left.rgbtGreen + botMid.rgbtGreen + botLeft.rgbtGreen) / 4.0);
                temp[i][j].rgbtBlue = round((mid.rgbtBlue + left.rgbtBlue + botMid.rgbtBlue + botLeft.rgbtBlue) / 4.0);
            }

            // Calculate for bottom-left pixel
            else if (i == height - 1 && j == 0)
            {
                temp[i][j].rgbtRed = round((mid.rgbtRed + right.rgbtRed + topMid.rgbtRed + topRight.rgbtRed) / 4.0);
                temp[i][j].rgbtGreen = round((mid.rgbtGreen + right.rgbtGreen + topMid.rgbtGreen + topRight.rgbtGreen) / 4.0);
                temp[i][j].rgbtBlue = round((mid.rgbtBlue + right.rgbtBlue + topMid.rgbtBlue + topRight.rgbtBlue) / 4.0);
            }

            // Calculate for bottom-right pixel
            else if (i == height - 1 && j == width - 1)
            {
                temp[i][j].rgbtRed = round((mid.rgbtRed + left.rgbtRed + topMid.rgbtRed + topLeft.rgbtRed) / 4.0);
                temp[i][j].rgbtGreen = round((mid.rgbtGreen + left.rgbtGreen + topMid.rgbtGreen + topLeft.rgbtGreen) / 4.0);
                temp[i][j].rgbtBlue = round((mid.rgbtBlue + left.rgbtBlue + topMid.rgbtBlue + topLeft.rgbtBlue) / 4.0);
            }

            // Calculate for right edge
            else if ((i != 0 || i != height - 1) && j == 0)
            {
                temp[i][j].rgbtRed = round((mid.rgbtRed + right.rgbtRed + topMid.rgbtRed + topRight.rgbtRed + botMid.rgbtRed + botRight.rgbtRed) / 6.0);
                temp[i][j].rgbtGreen = round((mid.rgbtGreen + right.rgbtGreen + topMid.rgbtGreen + topRight.rgbtGreen + botMid.rgbtGreen + botRight.rgbtGreen) / 6.0);
                temp[i][j].rgbtBlue = round((mid.rgbtBlue + right.rgbtBlue + topMid.rgbtBlue + topRight.rgbtBlue + botMid.rgbtBlue + botRight.rgbtBlue) / 6.0);
            }

            // Calculate for left edge
            else if ((i != 0 || i != height - 1) && j == width - 1)
            {
                temp[i][j].rgbtRed = round((left.rgbtRed + mid.rgbtRed + topLeft.rgbtRed + topMid.rgbtRed  + botLeft.rgbtRed + botMid.rgbtRed) / 6.0);
                temp[i][j].rgbtGreen = round((left.rgbtGreen + mid.rgbtGreen + topLeft.rgbtGreen + topMid.rgbtGreen + botLeft.rgbtGreen + botMid.rgbtGreen) / 6.0);
                temp[i][j].rgbtBlue = round((left.rgbtBlue + mid.rgbtBlue + topLeft.rgbtBlue + topMid.rgbtBlue + botLeft.rgbtBlue + botMid.rgbtBlue) / 6.0);
            }

            // Calculate for top edge
            else if (i == 0 && (j != 0 || j != width - 1))
            {
                temp[i][j].rgbtRed = round((left.rgbtRed + mid.rgbtRed + right.rgbtRed + botLeft.rgbtRed + botMid.rgbtRed + botRight.rgbtRed) / 6.0);
                temp[i][j].rgbtGreen = round((left.rgbtGreen + mid.rgbtGreen + right.rgbtGreen + botLeft.rgbtGreen + botMid.rgbtGreen + botRight.rgbtGreen) / 6.0);
                temp[i][j].rgbtBlue = round((left.rgbtBlue + mid.rgbtBlue + right.rgbtBlue + botLeft.rgbtBlue + botMid.rgbtBlue + botRight.rgbtBlue) / 6.0);
            }

            // Calculate for bottom edge
            else if (i == height - 1 && (j != 0 || j != width - 1))
            {
                temp[i][j].rgbtRed = round((left.rgbtRed + mid.rgbtRed + right.rgbtRed + topLeft.rgbtRed + topMid.rgbtRed + topRight.rgbtRed) / 6.0);
                temp[i][j].rgbtGreen = round((left.rgbtGreen + mid.rgbtGreen + right.rgbtGreen + topLeft.rgbtGreen + topMid.rgbtGreen + topRight.rgbtGreen) / 6.0);
                temp[i][j].rgbtBlue = round((left.rgbtBlue + mid.rgbtBlue + right.rgbtBlue + topLeft.rgbtBlue + topMid.rgbtBlue + topRight.rgbtBlue) / 6.0);
            }

            // Calculate the rest of the pixels
            else
            {
                temp[i][j].rgbtRed = round((left.rgbtRed + mid.rgbtRed + right.rgbtRed + topLeft.rgbtRed + topMid.rgbtRed + topRight.rgbtRed + botLeft.rgbtRed + botMid.rgbtRed + botRight.rgbtRed) / 9.0);
                temp[i][j].rgbtGreen = round((left.rgbtGreen + mid.rgbtGreen + right.rgbtGreen + topLeft.rgbtGreen + topMid.rgbtGreen + topRight.rgbtGreen + botLeft.rgbtGreen + botMid.rgbtGreen + botRight.rgbtGreen) / 9.0);
                temp[i][j].rgbtBlue = round((left.rgbtBlue + mid.rgbtBlue + right.rgbtBlue + topLeft.rgbtBlue + topMid.rgbtBlue + topRight.rgbtBlue + botLeft.rgbtBlue + botMid.rgbtBlue + botRight.rgbtBlue) / 9.0);
            }
        }
    }
    // Reiterate through the loop and replace the image with temp values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Declare temporary variable
    RGBTRIPLE temp[height][width];

    // Copy original image into temp
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    // Create Gx matrix
    int GxKernal[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    // Create Gy matrix
    int GyKernal[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    // Loop through each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate Gx, Gy sums, and then the final value for the top-left pixel
            if (i == 0 && j == 0)
            {
                // Create matrix with RGB values in respect to Sobel matrices (w/black border)
                RGBTRIPLE topLeftMatrix[3][3] =
                {
                    {{0}, {0}, {0}},
                    {{0}, mid, right},
                    {{0}, botMid, botRight}
                };

                // Declare Gx and Gy variables for each color
                int GxRed = 0;
                int GyRed = 0;

                int GxBlue = 0;
                int GyBlue = 0;

                int GxGreen = 0;
                int GyGreen = 0;

                // Create another loop to multiply kernals with 3x3 RBG matrix
                for (int k = 0; k < 3; k++)
                {
                     // Create sum of Gx and Gy values by multiplying the kernal with the matrix for each color
                    for (int z = 0; z < 3; z++)
                    {
                        GxRed = GxRed + (GxKernal[k][z] * topLeftMatrix[k][z].rgbtRed);
                        GyRed = GyRed + (GyKernal[k][z] * topLeftMatrix[k][z].rgbtRed);

                        GxBlue = GxBlue + (GxKernal[k][z] * topLeftMatrix[k][z].rgbtBlue);
                        GyBlue = GyBlue + (GyKernal[k][z] * topLeftMatrix[k][z].rgbtBlue);

                        GxGreen = GxGreen + (GxKernal[k][z] * topLeftMatrix[k][z].rgbtGreen);
                        GyGreen = GyGreen + (GyKernal[k][z] * topLeftMatrix[k][z].rgbtGreen);
                    }
                }

                // Calculate final value (G) for each color
                float GRed = round(sqrt((GxRed * GxRed) + (GyRed * GyRed)));
                float GBlue = round(sqrt((GxBlue * GxBlue) + (GyBlue * GyBlue)));
                float GGreen = round(sqrt((GxGreen * GxGreen) + (GyGreen * GyGreen)));

                // Cap any values above 255
                if (GRed > 255) { GRed = 255; }
                if (GBlue > 255) { GBlue = 255; }
                if (GGreen > 255) { GGreen = 255; }

                // Place the new values into temp
                temp[i][j].rgbtRed = GRed;
                temp[i][j].rgbtBlue = GBlue;
                temp[i][j].rgbtGreen = GGreen;
            }

            // Calculate for the top-right pixel
            else if (i == 0 && j == width - 1)
            {
                // Create matrix with RGB values in respect to Sobel matrices (w/black border)
                RGBTRIPLE topRightMatrix[3][3] =
                {
                    {{0}, {0}, {0}},
                    {left, mid, {0}},
                    {botLeft, botMid, {0}}
                };

                // Declare Gx and Gy variables for each color
                int GxRed = 0;
                int GyRed = 0;

                int GxBlue = 0;
                int GyBlue = 0;

                int GxGreen = 0;
                int GyGreen = 0;

                // Create another loop to multiply kernals with 3x3 RBG matrix
                for (int k = 0; k < 3; k++)
                {
                     // Create sum of Gx and Gy values by multiplying the kernal with the matrix for each color
                    for (int z = 0; z < 3; z++)
                    {
                        GxRed = GxRed + (GxKernal[k][z] * topRightMatrix[k][z].rgbtRed);
                        GyRed = GyRed + (GyKernal[k][z] * topRightMatrix[k][z].rgbtRed);

                        GxBlue = GxBlue + (GxKernal[k][z] * topRightMatrix[k][z].rgbtBlue);
                        GyBlue = GyBlue + (GyKernal[k][z] * topRightMatrix[k][z].rgbtBlue);

                        GxGreen = GxGreen + (GxKernal[k][z] * topRightMatrix[k][z].rgbtGreen);
                        GyGreen = GyGreen + (GyKernal[k][z] * topRightMatrix[k][z].rgbtGreen);
                    }
                }

                // Calculate final value (G) for each color
                float GRed = round(sqrt((GxRed * GxRed) + (GyRed * GyRed)));
                float GBlue = round(sqrt((GxBlue * GxBlue) + (GyBlue * GyBlue)));
                float GGreen = round(sqrt((GxGreen * GxGreen) + (GyGreen * GyGreen)));

                // Cap any values above 255
                if (GRed > 255) { GRed = 255; }
                if (GBlue > 255) { GBlue = 255; }
                if (GGreen > 255) { GGreen = 255; }

                // Place the new values into temp
                temp[i][j].rgbtRed = GRed;
                temp[i][j].rgbtBlue = GBlue;
                temp[i][j].rgbtGreen = GGreen;
            }

            // Calculate for the bottom-left pixel
            else if (i == height - 1 && j == 0)
            {
                // Create matrix with RGB values in respect to Sobel matrices (w/black border)
                RGBTRIPLE botLeftMatrix[3][3] =
                {
                    {{0}, topMid, topRight},
                    {{0}, mid, right},
                    {{0}, {0}, {0}}
                };

                // Declare Gx and Gy variables for each color
                int GxRed = 0;
                int GyRed = 0;

                int GxBlue = 0;
                int GyBlue = 0;

                int GxGreen = 0;
                int GyGreen = 0;

                // Create another loop to multiply kernals with 3x3 RBG matrix
                for (int k = 0; k < 3; k++)
                {
                     // Create sum of Gx and Gy values by multiplying the kernal with the matrix for each color
                    for (int z = 0; z < 3; z++)
                    {
                        GxRed = GxRed + (GxKernal[k][z] * botLeftMatrix[k][z].rgbtRed);
                        GyRed = GyRed + (GyKernal[k][z] * botLeftMatrix[k][z].rgbtRed);

                        GxBlue = GxBlue + (GxKernal[k][z] * botLeftMatrix[k][z].rgbtBlue);
                        GyBlue = GyBlue + (GyKernal[k][z] * botLeftMatrix[k][z].rgbtBlue);

                        GxGreen = GxGreen + (GxKernal[k][z] * botLeftMatrix[k][z].rgbtGreen);
                        GyGreen = GyGreen + (GyKernal[k][z] * botLeftMatrix[k][z].rgbtGreen);
                    }
                }

                // Calculate final value (G) for each color
                float GRed = round(sqrt((GxRed * GxRed) + (GyRed * GyRed)));
                float GBlue = round(sqrt((GxBlue * GxBlue) + (GyBlue * GyBlue)));
                float GGreen = round(sqrt((GxGreen * GxGreen) + (GyGreen * GyGreen)));

                // Cap any values above 255
                if (GRed > 255) { GRed = 255; }
                if (GBlue > 255) { GBlue = 255; }
                if (GGreen > 255) { GGreen = 255; }

                // Place the new values into temp
                temp[i][j].rgbtRed = GRed;
                temp[i][j].rgbtBlue = GBlue;
                temp[i][j].rgbtGreen = GGreen;
            }

            // Calculate for bottom-right pixel
            else if (i == height - 1 && j == width - 1)
            {
                // Create matrix with RGB values in respect to Sobel matrices (w/black border)
                RGBTRIPLE botRightMatrix[3][3] =
                {
                    {topLeft, topMid, {0}},
                    {left, mid, {0}},
                    {{0}, {0}, {0}}
                };

                // Declare Gx and Gy variables for each color
                int GxRed = 0;
                int GyRed = 0;

                int GxBlue = 0;
                int GyBlue = 0;

                int GxGreen = 0;
                int GyGreen = 0;

                // Create another loop to multiply kernals with 3x3 RBG matrix
                for (int k = 0; k < 3; k++)
                {
                     // Create sum of Gx and Gy values by multiplying the kernal with the matrix for each color
                    for (int z = 0; z < 3; z++)
                    {
                        GxRed = GxRed + (GxKernal[k][z] * botRightMatrix[k][z].rgbtRed);
                        GyRed = GyRed + (GyKernal[k][z] * botRightMatrix[k][z].rgbtRed);

                        GxBlue = GxBlue + (GxKernal[k][z] * botRightMatrix[k][z].rgbtBlue);
                        GyBlue = GyBlue + (GyKernal[k][z] * botRightMatrix[k][z].rgbtBlue);

                        GxGreen = GxGreen + (GxKernal[k][z] * botRightMatrix[k][z].rgbtGreen);
                        GyGreen = GyGreen + (GyKernal[k][z] * botRightMatrix[k][z].rgbtGreen);
                    }
                }

                // Calculate final value (G) for each color
                float GRed = round(sqrt((GxRed * GxRed) + (GyRed * GyRed)));
                float GBlue = round(sqrt((GxBlue * GxBlue) + (GyBlue * GyBlue)));
                float GGreen = round(sqrt((GxGreen * GxGreen) + (GyGreen * GyGreen)));

                // Cap any values above 255
                if (GRed > 255) { GRed = 255; }
                if (GBlue > 255) { GBlue = 255; }
                if (GGreen > 255) { GGreen = 255; }

                // Place the new values into temp
                temp[i][j].rgbtRed = GRed;
                temp[i][j].rgbtBlue = GBlue;
                temp[i][j].rgbtGreen = GGreen;
            }

            // Calculate for left-edge pixels
            else if ((i != 0 || i != height - 1) && j == 0)
            {
                // Create matrix with RGB values in respect to Sobel matrices (w/black border)
                RGBTRIPLE leftEdgeMatrix[3][3] =
                {
                    {{0}, topMid, topRight},
                    {{0}, mid, right},
                    {{0}, botMid, botRight}
                };

                // Declare Gx and Gy variables for each color
                int GxRed = 0;
                int GyRed = 0;

                int GxBlue = 0;
                int GyBlue = 0;

                int GxGreen = 0;
                int GyGreen = 0;

                // Create another loop to multiply kernals with 3x3 RBG matrix
                for (int k = 0; k < 3; k++)
                {
                     // Create sum of Gx and Gy values by multiplying the kernal with the matrix for each color
                    for (int z = 0; z < 3; z++)
                    {
                        GxRed = GxRed + (GxKernal[k][z] * leftEdgeMatrix[k][z].rgbtRed);
                        GyRed = GyRed + (GyKernal[k][z] * leftEdgeMatrix[k][z].rgbtRed);

                        GxBlue = GxBlue + (GxKernal[k][z] * leftEdgeMatrix[k][z].rgbtBlue);
                        GyBlue = GyBlue + (GyKernal[k][z] * leftEdgeMatrix[k][z].rgbtBlue);

                        GxGreen = GxGreen + (GxKernal[k][z] * leftEdgeMatrix[k][z].rgbtGreen);
                        GyGreen = GyGreen + (GyKernal[k][z] * leftEdgeMatrix[k][z].rgbtGreen);
                    }
                }

                // Calculate final value (G) for each color
                float GRed = round(sqrt((GxRed * GxRed) + (GyRed * GyRed)));
                float GBlue = round(sqrt((GxBlue * GxBlue) + (GyBlue * GyBlue)));
                float GGreen = round(sqrt((GxGreen * GxGreen) + (GyGreen * GyGreen)));

                // Cap any values above 255
                if (GRed > 255) { GRed = 255; }
                if (GBlue > 255) { GBlue = 255; }
                if (GGreen > 255) { GGreen = 255; }

                // Place the new values into temp
                temp[i][j].rgbtRed = GRed;
                temp[i][j].rgbtBlue = GBlue;
                temp[i][j].rgbtGreen = GGreen;
            }

            // Calculate for right-edge pixels
            else if ((i != 0 || i != height - 1) && j == width - 1)
            {
                // Create matrix with RGB values in respect to Sobel matrices (w/black border)
                RGBTRIPLE rightEdgeMatrix[3][3] =
                {
                    {topLeft, topMid, {0}},
                    {left, mid, {0}},
                    {botLeft, botMid, {0}}
                };

                // Declare Gx and Gy variables for each color
                int GxRed = 0;
                int GyRed = 0;

                int GxBlue = 0;
                int GyBlue = 0;

                int GxGreen = 0;
                int GyGreen = 0;

                // Create another loop to multiply kernals with 3x3 RBG matrix
                for (int k = 0; k < 3; k++)
                {
                     // Create sum of Gx and Gy values by multiplying the kernal with the matrix for each color
                    for (int z = 0; z < 3; z++)
                    {
                        GxRed = GxRed + (GxKernal[k][z] * rightEdgeMatrix[k][z].rgbtRed);
                        GyRed = GyRed + (GyKernal[k][z] * rightEdgeMatrix[k][z].rgbtRed);

                        GxBlue = GxBlue + (GxKernal[k][z] * rightEdgeMatrix[k][z].rgbtBlue);
                        GyBlue = GyBlue + (GyKernal[k][z] * rightEdgeMatrix[k][z].rgbtBlue);

                        GxGreen = GxGreen + (GxKernal[k][z] * rightEdgeMatrix[k][z].rgbtGreen);
                        GyGreen = GyGreen + (GyKernal[k][z] * rightEdgeMatrix[k][z].rgbtGreen);
                    }
                }

                // Calculate final value (G) for each color
                float GRed = round(sqrt((GxRed * GxRed) + (GyRed * GyRed)));
                float GBlue = round(sqrt((GxBlue * GxBlue) + (GyBlue * GyBlue)));
                float GGreen = round(sqrt((GxGreen * GxGreen) + (GyGreen * GyGreen)));

                // Cap any values above 255
                if (GRed > 255) { GRed = 255; }
                if (GBlue > 255) { GBlue = 255; }
                if (GGreen > 255) { GGreen = 255; }

                // Place the new values into temp
                temp[i][j].rgbtRed = GRed;
                temp[i][j].rgbtBlue = GBlue;
                temp[i][j].rgbtGreen = GGreen;
            }

            // Calculate for top-edge pixels
            else if (i == 0 && (j != 0 || j != width - 1))
            {
                // Create matrix with RGB values in respect to Sobel matrices (w/black border)
                RGBTRIPLE topEdgeMatrix[3][3] =
                {
                    {{0}, {0}, {0}},
                    {left, mid, right},
                    {botLeft, botMid, botRight}
                };

                // Declare Gx and Gy variables for each color
                int GxRed = 0;
                int GyRed = 0;

                int GxBlue = 0;
                int GyBlue = 0;

                int GxGreen = 0;
                int GyGreen = 0;

                // Create another loop to multiply kernals with 3x3 RBG matrix
                for (int k = 0; k < 3; k++)
                {
                     // Create sum of Gx and Gy values by multiplying the kernal with the matrix for each color
                    for (int z = 0; z < 3; z++)
                    {
                        GxRed = GxRed + (GxKernal[k][z] * topEdgeMatrix[k][z].rgbtRed);
                        GyRed = GyRed + (GyKernal[k][z] * topEdgeMatrix[k][z].rgbtRed);

                        GxBlue = GxBlue + (GxKernal[k][z] * topEdgeMatrix[k][z].rgbtBlue);
                        GyBlue = GyBlue + (GyKernal[k][z] * topEdgeMatrix[k][z].rgbtBlue);

                        GxGreen = GxGreen + (GxKernal[k][z] * topEdgeMatrix[k][z].rgbtGreen);
                        GyGreen = GyGreen + (GyKernal[k][z] * topEdgeMatrix[k][z].rgbtGreen);
                    }
                }

                // Calculate final value (G) for each color
                float GRed = round(sqrt((GxRed * GxRed) + (GyRed * GyRed)));
                float GBlue = round(sqrt((GxBlue * GxBlue) + (GyBlue * GyBlue)));
                float GGreen = round(sqrt((GxGreen * GxGreen) + (GyGreen * GyGreen)));

                // Cap any values above 255
                if (GRed > 255) { GRed = 255; }
                if (GBlue > 255) { GBlue = 255; }
                if (GGreen > 255) { GGreen = 255; }

                // Place the new values into temp
                temp[i][j].rgbtRed = GRed;
                temp[i][j].rgbtBlue = GBlue;
                temp[i][j].rgbtGreen = GGreen;
            }

            // Calculate for bottom-edge pixels
            else if (i == height - 1 && (j != 0 || j != width - 1))
            {
                // Create matrix with RGB values in respect to Sobel matrices (w/black border)
                RGBTRIPLE bottomEdgeMatrix[3][3] =
                {
                    {topLeft, topMid, topRight},
                    {left, mid, right},
                    {{0}, {0}, {0}}
                };

                // Declare Gx and Gy variables for each color
                int GxRed = 0;
                int GyRed = 0;

                int GxBlue = 0;
                int GyBlue = 0;

                int GxGreen = 0;
                int GyGreen = 0;

                // Create another loop to multiply kernals with 3x3 RBG matrix
                for (int k = 0; k < 3; k++)
                {
                     // Create sum of Gx and Gy values by multiplying the kernal with the matrix for each color
                    for (int z = 0; z < 3; z++)
                    {
                        GxRed = GxRed + (GxKernal[k][z] * bottomEdgeMatrix[k][z].rgbtRed);
                        GyRed = GyRed + (GyKernal[k][z] * bottomEdgeMatrix[k][z].rgbtRed);

                        GxBlue = GxBlue + (GxKernal[k][z] * bottomEdgeMatrix[k][z].rgbtBlue);
                        GyBlue = GyBlue + (GyKernal[k][z] * bottomEdgeMatrix[k][z].rgbtBlue);

                        GxGreen = GxGreen + (GxKernal[k][z] * bottomEdgeMatrix[k][z].rgbtGreen);
                        GyGreen = GyGreen + (GyKernal[k][z] * bottomEdgeMatrix[k][z].rgbtGreen);
                    }
                }

                // Calculate final value (G) for each color
                float GRed = round(sqrt((GxRed * GxRed) + (GyRed * GyRed)));
                float GBlue = round(sqrt((GxBlue * GxBlue) + (GyBlue * GyBlue)));
                float GGreen = round(sqrt((GxGreen * GxGreen) + (GyGreen * GyGreen)));

                // Cap any values above 255
                if (GRed > 255) { GRed = 255; }
                if (GBlue > 255) { GBlue = 255; }
                if (GGreen > 255) { GGreen = 255; }

                // Place the new values into temp
                temp[i][j].rgbtRed = GRed;
                temp[i][j].rgbtBlue = GBlue;
                temp[i][j].rgbtGreen = GGreen;
            }

            // Calculate for the rest of the pixels
            else
            {
                // Create matrix with RGB values in respect to Sobel matrices (w/black border)
                RGBTRIPLE pixelMatrix[3][3] =
                {
                    {topLeft, topMid, topRight},
                    {left, mid, right},
                    {botLeft, botMid, botRight}
                };

                // Declare Gx and Gy variables for each color
                int GxRed = 0;
                int GyRed = 0;

                int GxBlue = 0;
                int GyBlue = 0;

                int GxGreen = 0;
                int GyGreen = 0;

                // Create another loop to multiply kernals with 3x3 RBG matrix
                for (int k = 0; k < 3; k++)
                {
                     // Create sum of Gx and Gy values by multiplying the kernal with the matrix for each color
                    for (int z = 0; z < 3; z++)
                    {
                        GxRed = GxRed + (GxKernal[k][z] * pixelMatrix[k][z].rgbtRed);
                        GyRed = GyRed + (GyKernal[k][z] * pixelMatrix[k][z].rgbtRed);

                        GxBlue = GxBlue + (GxKernal[k][z] * pixelMatrix[k][z].rgbtBlue);
                        GyBlue = GyBlue + (GyKernal[k][z] * pixelMatrix[k][z].rgbtBlue);

                        GxGreen = GxGreen + (GxKernal[k][z] * pixelMatrix[k][z].rgbtGreen);
                        GyGreen = GyGreen + (GyKernal[k][z] * pixelMatrix[k][z].rgbtGreen);
                    }
                }

                // Calculate final value (G) for each color
                float GRed = round(sqrt((GxRed * GxRed) + (GyRed * GyRed)));
                float GBlue = round(sqrt((GxBlue * GxBlue) + (GyBlue * GyBlue)));
                float GGreen = round(sqrt((GxGreen * GxGreen) + (GyGreen * GyGreen)));

                // Cap any values above 255
                if (GRed > 255) { GRed = 255; }
                if (GBlue > 255) { GBlue = 255; }
                if (GGreen > 255) { GGreen = 255; }

                // Place the new values into temp
                temp[i][j].rgbtRed = GRed;
                temp[i][j].rgbtBlue = GBlue;
                temp[i][j].rgbtGreen = GGreen;
            }
        }
    }

    // Reiterate through the loop and replace the image with temp values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}
