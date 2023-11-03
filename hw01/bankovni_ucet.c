#include <stdio.h>
#include <math.h>
int main(void)
{

    double CreditInterest = 0, DebitInterest = 0, Interest = 0, Balance = 0, Amount = 1;
    int Days = 0, HelpDays = -1;
    char c;

    printf("Zadejte kreditni urok [%%]:\n");

    if (scanf("%lf", &CreditInterest) != 1)
    {
        printf("Nespravny vstup.\n");
        return 1;
    }
    c = getchar();
    if (c != EOF && c != '\n' && c != 'x' && c != 'e' && c != 'f')
    {
        printf("Nespravny vstup.\n");
        return 1;
    }

    printf("Zadejte debetni urok [%%]:\n");

    if (scanf("%lf", &DebitInterest) != 1)
    {

        printf("Nespravny vstup.\n");
        return 1;
    }
    c = getchar();
    if (c != EOF && c != '\n' && c != 'x' && c != 'e' && c != 'f')
    {
        printf("Nespravny vstup.\n");
        return 1;
    }

    printf("Zadejte transakce:\n");
    while (Amount != 0)
    {
        int i = 1;
        if (i == 1)
        {
            Amount = 0;
        }

        Amount = Amount * 100;
        Amount = trunc(Amount);
        Amount = Amount / 100;
        if (scanf("%d, %lf", &Days, &Amount) != 2)
        {

            printf("Nespravny vstup.\n");
            return 1;
        }
        if (c != EOF && c != '\n' && c != 'x' && c != 'e' && c != 'f')
        {
            printf("Nespravny vstup.\n");
            return 1;
        }
        if (Days > HelpDays)
        {

            if (Balance < 0)
            {
                for (int i = 0; i < (Days - HelpDays); i++)
                {
                    Interest = Balance * (DebitInterest / 100);
                    Interest = Interest * 100;
                    Interest = trunc(Interest);
                    Interest = Interest / 100;
                    Balance = Balance + Interest;
                }
            }
            else if (Balance > 0)
            {

                for (int i = 0; i < (Days - HelpDays); i++)
                {
                    Interest = Balance * (CreditInterest / 100);
                    Interest = Interest * 100;
                    Interest = trunc(Interest);
                    Interest = Interest / 100;
                    Balance = Balance + Interest;
                }
            }
            Balance = Balance + Amount;
            HelpDays = Days;
        }
        else
        {
            printf("Nespravny vstup.\n");
            return 1;
        }
        i++;
    }

    printf("Zustatek: %.2f\n", Balance);
    return 0;
}
