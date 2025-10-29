#include <stdio.h>
#include <string.h>
#include <ctype.h>

char terminals[50], nonTerminals[50], productions[50][50][50], first[50][50], follow[50][50];
int nonTiter = 0, Titer = 0;

void computeFirst()
{
}

void computeFollow()
{
}

int main()
{
    FILE *fp = fopen("/Users/akhilgireesh/Programming/compiler/firstNFollow/input.txt", "r");
    char line[50];

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        int currIter = 0, j = 0;
        int len = strlen(line);
        if (line[len - 1] == '\n')
            line[len - 1] = '\0';
        for (int i = 0; i < strlen(line); i++)
        {
            if (i == 0)
            {
                nonTerminals[nonTiter++] = line[i];
            }
            else if (line[i] == '|' || line[i] == '\0')
            {
                productions[nonTiter - 1][j][currIter] = '\0';
                currIter = 0;
                j++;
            }
            else if (line[i] == '-' || line[i] == '>' || line[i] == ' ')
            {
                continue;
            }
            else
            {
                productions[nonTiter - 1][j][currIter++] = line[i];

                if (!isupper(line[i]))
                {
                    int flag = 0;
                    for (int k = 0; k < Titer; k++)
                    {
                        if (terminals[k] == line[i])
                        {
                            flag = 1;
                            break;
                        }
                    }

                    if (!flag)
                    {
                        terminals[Titer++] = line[i];
                    }
                }
            }
        }
    }
    fclose(fp);

    printf("Non-terminals: ");
    for (int i = 0; i < nonTiter; i++)
        printf("%c ", nonTerminals[i]);
    printf("\n");

    // ===== Printing terminals =====
    printf("Terminals: ");
    for (int i = 0; i < Titer; i++)
        printf("%c ", terminals[i]);
    printf("\n");

    // ===== Printing productions =====
    printf("Productions:\n");
    for (int i = 0; i < nonTiter; i++)
    {
        printf("%c -> ", nonTerminals[i]);
        for (int j = 0; j < 50 && productions[i][j][0] != '\0'; j++)
        {
            if (j > 0)
                printf("|");
            printf("%s", productions[i][j]);
        }
        printf("\n");
    }

    computeFirst();
    computeFollow();

    return 0;
}