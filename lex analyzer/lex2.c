#include <stdio.h>
#include <string.h>
#include <ctype.h>
void main()
{
    FILE *input;
    char ch;
    input = fopen("text.txt", "r");
    ch = fgetc(input);
    while (ch != EOF)
    {
        char token[20];
        int i = 0;
        switch (ch)
        {
        case '/':
            ch = fgetc(input);
            if (ch == '/')
                while (ch != '\n')
                    ch = fgetc(input);
            else if (ch == '*')
            {
                while (ch != '*')
                    ch = fgetc(input);
                ch = fgetc(input);
            }
            else
                printf("%c is a operator\n", ch);
            break;
        case '+':
        case '*':
        case '-':
            printf("%c is a operator\n", ch);
            break;
        case ' ':
        case '\t':
        case '\n':
            break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            token[i++] = ch;
            ch = fgetc(input);
            while (isdigit(ch))
            {
                token[i++] = ch;
                ch = fgetc(input);
            }
            token[i] = '\0';
            ungetc(ch, input);
            printf("%s is a number\n", token);
            break;
        case '>':
        case '<':
        case '=':
            token[i++] = ch;
            ch = fgetc(input);
            if (ch == '=')
            {
                token[i++] = ch;
            }
            else
                ungetc(ch, input);
            printf("%s is a relational operator\n", token);
            break;
        default:
            if (isalpha(ch))
            {
                token[i++] = ch;
                ch = fgetc(input);
                while (isalpha(ch))
                {
                    token[i++] = ch;
                    ch = fgetc(input);
                }
                token[i] = '\0';
                ungetc(ch, input);
                if (strcmp(token, "if") == 0 || strcmp(token, "else") == 0 || strcmp(token, "main") == 0 || strcmp(token, "void") == 0 || strcmp(token, "printf") == 0)
                    printf("%s is a keyword\n", token);
                else
                    printf("%s is a identifier\n", token);
            }
            else
                printf("%c is a Special character\n", ch);
            break;
        }
        ch = fgetc(input);
    }
    fclose(input);
}
