#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avarage;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            avarage = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = avarage;
            image[i][j].rgbtGreen = avarage;
            image[i][j].rgbtRed = avarage;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;


    for(int i = 0; i < height; i++)
    {
        int a = 0;
        int b = width - 1;

        if(width % 2 != 0)
        {
            while(a != b)
            {
                temp = image[i][a];
                image[i][a] = image[i][b];
                image[i][b] = temp;
                a++;
                b--;
            }
        }
        if(width % 2 == 0)
        {
            while(b > a)
            {
                temp = image[i][a];
                image[i][a] = image[i][b];
                image[i][b] = temp;
                a++;
                b--;
            }
        }
    }
    return;
}

  // Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // check for an edge
           if ((i == 0 && (j >= 0 && j <= width - 1))
                || ((i >= 0 && i <= height - 1) && j == 0)
                || (i == height - 1 && (j >= 0 && j <= width - 1))
                || ((i >= 0 && i <= height -1) && j == width - 1))
            {
                //check if it is a corner
                if ((i == 0 && j == 0)
                    || (i == 0 && j == width - 1)
                    || (i == height - 1 && j == 0)
                    || (i == height - 1 && j == width - 1))
                {
                    if (i == 0 && j == 0)
                    {
                        image[i][j].rgbtRed = (int) round((copy[i][j].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed + copy[i][j + 1].rgbtRed) / 4.0);
                        image[i][j].rgbtGreen = (int) round((copy[i][j].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen + copy[i][j + 1].rgbtGreen) / 4.0);
                        image[i][j].rgbtBlue = (int) round((copy[i][j].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue + copy[i][j + 1].rgbtBlue) / 4.0);
                    }

                    if (i == 0 && j == width - 1)
                    {
                        image[i][j].rgbtRed = (int) round((copy[i][j].rgbtRed + copy[i +1 ][j].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i][j - 1].rgbtRed) / 4.0);
                        image[i][j].rgbtGreen = (int) round((copy[i][j].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i][j - 1].rgbtGreen) / 4.0);
                        image[i][j].rgbtBlue = (int) round((copy[i][j].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i][j - 1].rgbtBlue) / 4.0);
                    }

                    if (i == height - 1 && j == 0)
                    {
                        image[i][j].rgbtRed = (int) round((copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i][j + 1].rgbtRed) / 4.0);
                        image[i][j].rgbtGreen = (int) round((copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i][j + 1].rgbtGreen) / 4.0);
                        image[i][j].rgbtBlue = (int) round((copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i][j + 1].rgbtBlue) / 4.0);
                    }

                    if (i == height - 1 && j == width - 1)
                    {
                        image[i][j].rgbtRed = (int) round((copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i][j - 1].rgbtRed) / 4.0);
                        image[i][j].rgbtGreen = (int) round((copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i][j - 1].rgbtGreen) / 4.0);
                        image[i][j].rgbtBlue = (int) round((copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i][j - 1].rgbtBlue) / 4.0);
                    }
                }
                // if not a corner index
                else
                {
                    if (i == 0 && (j >= 1 && j <= width - 2))
                    {
                        image[i][j].rgbtRed = (int) round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 6.0);
                        image[i][j].rgbtGreen = (int) round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 6.0);
                        image[i][j].rgbtBlue = (int) round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 6.0);
                    }

                    if ((i >= 1 && i <= height - 2) && j == 0)
                    {
                        image[i][j].rgbtRed = (int) round((copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i + 1][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 6.0);
                        image[i][j].rgbtGreen = (int) round((copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 6.0);
                        image[i][j].rgbtBlue = (int) round((copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 6.0);
                    }

                    if (i == height - 1 && (j >= 1 && j <= width - 2))
                    {
                        image[i][j].rgbtRed = (int) round((copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j + 1].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i - 1][j - 1].rgbtRed) / 6.0);
                        image[i][j].rgbtGreen = (int) round((copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i - 1][j - 1].rgbtGreen) / 6.0);
                        image[i][j].rgbtBlue = (int) round((copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i - 1][j - 1].rgbtBlue) / 6.0);
                    }

                    if ((i >= 1 && i <= height -2) && j == width - 1)
                    {
                        image[i][j].rgbtRed = (int) round((copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i + 1][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i + 1][j - 1].rgbtRed) / 6.0);
                        image[i][j].rgbtGreen = (int) round((copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen) / 6.0);
                        image[i][j].rgbtBlue = (int) round((copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue) / 6.0);
                    }
                }
            }
            // for normal pixel no edge at all
            else
            {
                image[i][j].rgbtRed = (int) round(((copy[i - 1][j - 1].rgbtRed) + (copy[i - 1][j].rgbtRed) + (copy[i - 1][j + 1].rgbtRed) + (copy[i][j - 1].rgbtRed) + (copy[i][j].rgbtRed) + (copy[i][j + 1].rgbtRed) + (copy[i + 1][j - 1].rgbtRed) + (copy[i + 1][j].rgbtRed) + (copy[i + 1][j + 1].rgbtRed)) / 9.0);
                image[i][j].rgbtGreen = (int) round(((copy[i - 1][j - 1].rgbtGreen) + (copy[i - 1][j].rgbtGreen) + (copy[i - 1][j + 1].rgbtGreen) + (copy[i][j - 1].rgbtGreen) + (copy[i][j].rgbtGreen) + (copy[i][j + 1].rgbtGreen) + (copy[i + 1][j - 1].rgbtGreen) + (copy[i + 1][j].rgbtGreen) + (copy[i + 1][j + 1].rgbtGreen)) / 9.0);
                image[i][j].rgbtBlue = (int) round(((copy[i - 1][j - 1].rgbtBlue) + (copy[i - 1][j].rgbtBlue) + (copy[i - 1][j + 1].rgbtBlue) + (copy[i][j - 1].rgbtBlue) + (copy[i][j].rgbtBlue) + (copy[i][j + 1].rgbtBlue) + (copy[i + 1][j - 1].rgbtBlue) + (copy[i + 1][j].rgbtBlue) + (copy[i + 1][j + 1].rgbtBlue)) / 9.0);
            }

        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = {
                   {-1, 0, 1},
                   {-2, 0, 2},
                   {-1, 0, 1}
                   };

    int Gy[3][3] = {
                   {-1, -2, -1},
                   {0, 0, 0},
                   {1, 2, 1}
                   };
    RGBTRIPLE temp[height][width];

    for(int row = 0; row < height; row++)
    {
        for(int col = 0; col < width; col++)
        {
            int roww[] = {row - 1, row, row + 1};
            int coll[] = {col - 1, col, col + 1};
            float Gx_Red = 0, Gx_Green = 0, Gx_Blue = 0;
            float Gy_Red = 0, Gy_Green = 0, Gy_Blue = 0;

            for(int r = 0; r < 3; r++)
            {
                for(int c = 0; c < 3; c++)
                {
                    int current_row = roww[r];
                    int current_col = coll[c];

                    if(current_row >= 0 && current_row < height && current_col >= 0 && current_col < width)
                    {
                         RGBTRIPLE pixel = image[current_row][current_col];
                          Gx_Red += Gx[r][c]   * pixel.rgbtRed;
                           Gx_Green += Gx[r][c] * pixel.rgbtGreen;
                            Gx_Blue += Gx[r][c]  * pixel.rgbtBlue;

                            Gy_Red += Gy[r][c]   * pixel.rgbtRed;
                           Gy_Green += Gy[r][c] * pixel.rgbtGreen;
                          Gy_Blue += Gy[r][c]  * pixel.rgbtBlue;
                    }
                }
            }

            // Sqrt equiation to Gx/Gy
            int finalRed = round(sqrt(Gx_Red * Gx_Red + (Gy_Red * Gy_Red)));
              int finalGreen = round(sqrt(Gx_Green * Gx_Green + (Gy_Green * Gy_Green)));
                int finalBlue = round(sqrt(Gx_Blue * Gx_Blue + (Gy_Blue * Gy_Blue)));

                    temp[row][col].rgbtRed = finalRed > 255 ? 255: finalRed;
                  temp[row][col].rgbtGreen = finalGreen > 255 ? 255: finalGreen;
                temp[row][col].rgbtBlue = finalBlue > 255 ? 255: finalBlue;
        }
    }





    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}