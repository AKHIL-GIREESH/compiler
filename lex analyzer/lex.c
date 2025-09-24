#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    FILE *input;
    input = fopen("text.txt", "r");
    char ch = fgetc(input), keywords[4][10] = {"range", "for", "in", "print"};

    while (ch != EOF)
    {
        if (ch == ' ' || ch == '\n' || ch == '\t')
        {
            ch = fgetc(input);
            continue;
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%')
        {
            printf("%c : Arithmatic Operator\n", ch);
        }
        else if (ch == '<')
        {
            ch = fgetc(input);
            if (ch == '=')
            {
                printf("<= : Relop");
            }
        }
        else if (isalpha(ch))
        {
            char curr[50];
            int i = 0;
            curr[i++] = ch;
            ch = fgetc(input);
            while (isalpha(ch))
            {
                curr[i++] = ch;
                ch = fgetc(input);
            }

            curr[i] = '\0';
            int flag = 0;
            for (int j = 0; j < 4; j++)
            {
                if (!strcmp(curr, keywords[j]))
                {
                    printf("%s : Keyword\n", curr);
                    flag = 1;
                }
            }

            if (!flag)
            {
                printf("%s : Identifier\n", curr);
            }

            ungetc(ch, input);
        }
        else if (isdigit(ch))
        {
            char curr[50];
            int i = 0;
            curr[i++] = ch;
            ch = fgetc(input);
            while (isdigit(ch))
            {
                curr[i++] = ch;
                ch = fgetc(input);
            }

            curr[i] = '\0';

            printf("%s : Digit\n", curr);
            ungetc(ch, input);
        }

        ch = fgetc(input);
    }

    return 0;
}