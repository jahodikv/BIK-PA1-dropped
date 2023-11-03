#include <stdio.h>

int main(void)
{

    double x1=0, x2=0, x3=0, y1=0, y2=0, y3=0, a=0, b=0, c=0, ASum=0, BSum=0, CSum=0;
    char g;

    printf("Bod A:\n");
    if (scanf("%lf %lf", &x1, &y1) != 2)
    {

        printf("Nespravny vstup.\n");
        return 1;
    }
    g = getchar();

    if (g != EOF && g != '\n')
    {
        printf("Nespravny vstup.\n");
        return 1;
    }

    printf("Bod B:\n");
    if (scanf("%lf %lf", &x2, &y2) != 2)
    {

        printf("Nespravny vstup.\n");
        return 1;
    }
    g = getchar();

    if (g != EOF && g != '\n')
    {
        printf("Nespravny vstup.\n");
        return 1;
    }

    printf("Bod C:\n");
    if (scanf("%lf %lf", &x3, &y3) != 2)
    {

        printf("Nespravny vstup.\n");
        return 1;
    }
    g = getchar();

    if (g != EOF && g != '\n')
    {
        printf("Nespravny vstup.\n");
        return 1;
    }

    a = x1*1e5 - x2*1e5;
    b = y1*1e5 - y2*1e5;

    if (a != 0)
    {
        double i;
        a = -(a);
        i = b;
        b = a;
        a = i;
       
    }
    else
    {
        double i;
        b = -(b);
        i = b;
        b = a;
        a = i;
        
    }

    c = -(a * x1*1e5) - (b * y1*1e5);
    
    if ((x1*1e5 == x2*1e5 && y1*1e5 == y2*1e5) || (x1*1e5 == x3*1e5 && y1*1e5 == y3*1e5) || (x3*1e5 == x2*1e5 && y3*1e5 == y2*1e5))
    {
        printf("Nektere body splyvaji.\n");
        return 0;
    }
    else if (c == -(a * x3*1e5) - (b * y3*1e5))
    {

        printf("Body lezi na jedne primce.\n");
        ASum = x1 + y1;
        BSum = x2 + y2;
        CSum = x3 + y3;

        if (ASum < BSum)
        {
            if (BSum < CSum)
            {
                printf("Prostredni je bod B.\n");
                return 0;
            }
            else if (ASum < CSum)
            {
                printf("Prostredni je bod C.\n");
                return 0;
            }
            else
            {
                printf("Prostredni je bod A.\n");
                return 0;
            };
        }

        else
        {
            if (ASum < CSum)
            {
                printf("Prostredni je bod A.\n");
                return 0;
            }
            else if (BSum < CSum)
            {
                printf("Prostredni je bod C.\n");
                return 0;
            }
            else
            {
                printf("Prostredni je bod B.\n");
                return 0;
            };
        }
    }
    else
    {

        printf("Body nelezi na jedne primce.\n");
        return 0;
    }
}