#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 100

/**
 * Struct that stores the interval.
 * Brackets are stored as as a value 1 [<;>] or 0 [(;)] in variables IncludeFrom and IncluedTo.
 */
struct interval
{
    int from;
    int includeFrom;
    int to;
    int includeTo;
};

/**
 * Counts how many how many students fall into the specified point evaluation interval.
 * Prints the counted number.
 * Number is printed to standard output behind the arrow facing towards it. Newline is printed after the number.
 *
 * @param[in] pointsSize size of array
 * @param[in] i1 interval
 * @param[in] points array of numbers
 */
void numOfStudents(struct interval *i1, int points[], int pointsSize)
{
    int sum = 0;

    for (int i = 0; i <= pointsSize; i++)
    {
        if ((i1->from - i1->includeFrom) < points[i] && points[i] < (i1->to + i1->includeTo))
        {
            sum++;
        }
    }

    printf(" -> %d\n", sum);
}

/**
 * Reads the set of numbers from the standard input and validates it. The numbers represents students assesments.
 *  Reading is not successful:
 * - if set not begins and ends with brackets {}
 * - if numbers are not divided with comma
 * - if a number is not form the interval <0;1000000000>
 * - if there is no number to read
 *
 * @param[out] pointsSize size of array
 * @return points[] if input is valid, otherwise exit(1) the program.
 */
int *scanPoints(int *pointsSize)
{
    printf("Pocty bodu:\n");
    char trash, trash1;
    int capacity = MAX;

    int *points = (int *)calloc(capacity, sizeof(int));
    int size = 0;
    for (size = 0; size <= capacity; size++)
    {

        if (size >= capacity)
        {
            capacity = 2 * size;
            points = (int *)realloc(points, capacity * sizeof(int));
        }
        if (size == 0)
        {
            int scanfResult = scanf(" %c", &trash);

            if (scanfResult == 1)
            {
                if (trash != '{')
                {
                    printf("Nespravny vstup.\n");
                    exit(1);
                }
            }
            else
            {
                printf("Nespravny vstup.\n");
                exit(1);
            }
        }

        int scanfResult = scanf(" %d %c", &points[size], &trash1);

        if (scanfResult == 2)
        {
            if (trash1 == '}')
            {
                while ((getchar()) != '\n')
                    ;
                *pointsSize = size;
                return points;
            }
            if (trash1 != ',')
            {
                printf("Nespravny vstup.\n");
                exit(1);
            }
            if (points[size] > 1000000000 || points[size] < 0)
            {
                printf("Nespravny vstup.\n");
                exit(1);
            }
        }
        if (scanfResult != 2)
        {
            printf("Nespravny vstup.\n");
            exit(1);
        }
    }

    while ((getchar()) != '\n')
        ;
    *pointsSize = size;
    return points;
}

/**
 * Validates the brackes of the interval.
 * Brackets are stored as as a value 1 [<;>] or 0 [(;)] in variables IncludeFrom and IncluedTo to the interval i1.
 *  Reading is not successful:
 * - if interval not begins and ends with brackets <> or ()
 *
 * @param[in] frontBracket char that stores the first bracket
 * @param[in] endBracket char that stores the second bracket
 * @param[in] i1 interval
 */
void validateInterval(struct interval *i1, char frontBracket, char endBracket)
{

    if (frontBracket == '<')
    {
        i1->includeFrom = 1;
    }
    else if (frontBracket == '(')
    {
        i1->includeFrom = 0;
    }
    else
    {
        printf("Nespravny vstup.\n");
        exit(1);
    }
    if (endBracket == '>')
    {
        i1->includeTo = 1;
    }
    else if (endBracket == ')')
    {
        i1->includeTo = 0;
    }
    else
    {
        printf("Nespravny vstup.\n");
        exit(1);
    }
}

/**
 * Reads the interval from the standard input and validates it.
 *  Reading is not successful:
 * - if interval not begins and ends with brackets <> or ()
 * - if numbers are not intigers
 * - if numbers are not divided with semicolon
 *
 * @param[in] points array of numbers
 * @param[in] i1 interval
 * @param[in] pointsSize size of an array
 * @return 1 if interval is valid, otherwise 0
 */
int scanInterval(struct interval *i1, int points[], int pointsSize)
{
    printf("Intervaly:\n");
    int scanResult = 0;
    int x = 0;
    while (scanResult != 4)
    {
        char frontBracket, endBracket, newline;

        scanResult = scanf("%c%d;%d%c%c", &frontBracket, &i1->from, &i1->to, &endBracket, &newline);

        if (scanResult == EOF)
        {
            if (x > 0)
            {
                return 1;
            }
            else
            {
                printf("Nespravny vstup.\n");
                return 0;
            }
        }
        if (scanResult != 5 && scanResult != 4)
        {
            printf("Nespravny vstup.\n");

            return 0;
        }

        else
        {
            validateInterval(i1, frontBracket, endBracket);

            if (newline == '\n')
            {
                numOfStudents(i1, points, pointsSize);
                x++;
                continue;
            }
        }
    }
    return 1;
}

int main(void)
{
    struct interval i1;
    i1.from = 0;
    i1.to = 0;
    i1.includeFrom = 0;
    i1.includeTo = 0;
    int pointsSize = 0;

    int *points = scanPoints(&pointsSize);

    scanInterval(&i1, points, pointsSize);
    free(points);
    return 0;
}