#include <stdio.h>
#include <stdlib.h>

int ReadMatrix(int matrix[100][100], int *rows, int *columns)
{
    int y = 0, x = 0, scanfResult = 0;
    char trash;
    int maxColumns = 99;

    for (x = 0; x < 101; x++)
    {

        for (y = 0; y < 100; y++)
        {
            scanfResult = scanf("%d%c", &matrix[x][y], &trash);

            if (scanfResult == EOF)
            {
                if (scanf("%c", &trash) >= 1)
                {

                    printf("Nespravny vstup.\n");
                    return 0;
                }
                if (y != 0)
                {

                    printf("Nespravny vstup.\n");
                    return 0;
                }
                if (x >= 1)
                {
                    //*rows = x + 1;
                    return 1;
                }

                printf("Nespravny vstup.\n");
                return 0;
            }
            if (scanfResult == 1)
            {

                if (y != maxColumns)
                {
                    printf("Nespravny vstup.\n");
                    return 0;
                }
                //*rows = x + 1;
                return 1;
            }
            if (scanfResult != 2)
            {

                printf("Nespravny vstup.\n");
                return 0;
            }

            if (scanfResult == 2)
            {

                if (trash != ' ' && trash != '\n' && trash != '\t')
                {

                    printf("Nespravny vstup.\n");
                    return 0;
                }
                if (y > 99)
                {

                    printf("Nespravny vstup.\n");
                    return 0;
                }
                if (trash == '\n')
                {
                    if (x != 0)
                    {
                        if (y != maxColumns)
                        {

                            printf("Nespravny vstup.\n");
                            return 0;
                        }
                    }

               

                    break;
                }
            }
        }
        if (x == 0)
        {

            *columns = y + 1;

            maxColumns = y;
        }
        if (x>99)
        {
         printf("Nespravny vstup.\n");
                            return 0;
        }
        
        *rows = x + 1;
    }
    return 1;
}

void HorizontalSymmetry(int matrix[100][100], int rows, int columns)
{
    int tempRows = rows;

    for (int x = 0; x < rows; x++)
    {
        for (int y = 0; y < columns; y++)
        {

            if (matrix[tempRows - x - 1][y] != matrix[x][y])
            {

                printf("Symetrie podle horizontalni osy: ne\n");
                return;
            }
        }
    }

    printf("Symetrie podle horizontalni osy: ano\n");
}
void CentralSymmetry(int matrix[100][100], int rows, int columns)
{
    int tempRows = rows;

    for (int x = 0; x < rows; x++)
    {
        for (int y = 0; y < columns; y++)
        {

            if (matrix[tempRows - x - 1][y] != matrix[x][columns - y - 1])
            {

                printf("Symetrie podle stredu: ne\n");
                return;
            }
        }
    }
    printf("Symetrie podle stredu: ano\n");
}

void VerticalSymmetry(int matrix[100][100], int rows, int columns)
{

    for (int x = 0; x < rows; x++)
    {
        for (int y = 0; y < columns; y++)
        {

            if (matrix[x][y] != matrix[x][columns - y - 1])
            {

                printf("Symetrie podle vertikalni osy: ne\n");
                return;
            }
        }
    }
    printf("Symetrie podle vertikalni osy: ano\n");
}

int main(void)
{
    int columns = 100;
    int rows = 100;
    int matrix[100][100];
    printf("Matice:\n");
    if (ReadMatrix(matrix, &rows, &columns) == 0)
    {
        return 1;
    }

    HorizontalSymmetry(matrix, rows, columns);
    VerticalSymmetry(matrix, rows, columns);
    CentralSymmetry(matrix, rows, columns);
    return 0;
}
