#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20

char production[MAX][MAX];
char nonTerminals[MAX];
char first[MAX][MAX];
char follow[MAX][MAX];
int numProductions = 0;
int numNonTerminals = 0;

int isNonTerminal(char c)
{
    return (c >= 'A' && c <= 'Z');
}

void addToSet(char set[], char c)
{
    for (int i = 0; set[i] != '\0'; i++)
        if (set[i] == c)
            return;
    int len = strlen(set);
    set[len] = c;
    set[len + 1] = '\0';
}

void findFirst(char *res, char c);
void findFollow(char *res, char c);

void findFirst(char *res, char c)
{
    char temp[MAX];
    if (!isNonTerminal(c))
    {
        addToSet(res, c);
        return;
    }

    for (int i = 0; i < numProductions; i++)
    {
        if (production[i][0] == c)
        {
            for (int j = 2; production[i][j] != '\0'; j++)
            {
                if (production[i][j] == '|')
                    continue;

                temp[0] = '\0';
                findFirst(temp, production[i][j]);
                for (int k = 0; temp[k] != '\0'; k++)
                    addToSet(res, temp[k]);

                break; // Only first symbol in each RHS for simplicity
            }
        }
    }
}

void findFollow(char *res, char c)
{
    if (production[0][0] == c)
        addToSet(res, '$'); // Start symbol

    for (int i = 0; i < numProductions; i++)
    {
        for (int j = 2; production[i][j] != '\0'; j++)
        {
            if (production[i][j] == c)
            {
                if (production[i][j + 1] != '\0' && production[i][j + 1] != '|')
                {
                    char temp[MAX] = "";
                    findFirst(temp, production[i][j + 1]);
                    for (int k = 0; temp[k] != '\0'; k++)
                    {
                        if (temp[k] != '#')
                            addToSet(res, temp[k]);
                    }
                }
                else if (production[i][0] != c)
                {
                    findFollow(res, production[i][0]);
                }
            }
        }
    }
}

int main()
{
    FILE *fp = fopen("grammar.txt", "r");
    if (!fp)
    {
        printf("Error: cannot open grammar.txt\n");
        return 1;
    }

    printf("Productions:\n");
    while (fscanf(fp, "%s", production[numProductions]) != EOF)
        numProductions++;
    fclose(fp);

    for (int i = 0; i < numProductions; i++)
    {
        printf("%s\n", production[i]);
        if (strchr(nonTerminals, production[i][0]) == NULL)
            nonTerminals[numNonTerminals++] = production[i][0];
    }

    printf("\nFIRST sets:\n");
    for (int i = 0; i < numNonTerminals; i++)
    {
        first[i][0] = '\0';
        findFirst(first[i], nonTerminals[i]);
        printf("FIRST(%c) = { ", nonTerminals[i]);
        for (int j = 0; first[i][j] != '\0'; j++)
            printf("%c ", first[i][j]);
        printf("}\n");
    }

    printf("\nFOLLOW sets:\n");
    for (int i = 0; i < numNonTerminals; i++)
    {
        follow[i][0] = '\0';
        findFollow(follow[i], nonTerminals[i]);
        printf("FOLLOW(%c) = { ", nonTerminals[i]);
        for (int j = 0; follow[i][j] != '\0'; j++)
            printf("%c ", follow[i][j]);
        printf("}\n");
    }

    return 0;
}
