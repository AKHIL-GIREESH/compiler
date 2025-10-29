#include <stdio.h>
#include <string.h>
#include <ctype.h>

char stack[50], buffer[50], ans[50];
int top = -1, counter = 0;

int ICP(char op)
{
    if (op == '+' || op == '-')
    {
        return 1;
    }
    else if (op == '*' || op == '/')
    {
        return 3;
    }
    else if (op == '^')
    {
        return 6;
    }

    return -1;
}

int ISP(char op)
{
    if (op == '+' || op == '-')
    {
        return 2;
    }
    else if (op == '*' || op == '/')
    {
        return 4;
    }
    else if (op == '^')
    {
        return 5;
    }
    return -1;
}

void push(char op)
{
    stack[++top] = op;
}

char pop()
{
    char ch = stack[top--];
    return ch;
}

int main()
{
    printf("Input the infix Expression : ");
    scanf("%s", buffer);
    buffer[strlen(buffer)] = '\0';

    printf("\n%s\n", buffer);

    for (int i = 0; i < strlen(buffer); i++)
    {
        if (isalpha(buffer[i]))
        {
            ans[counter++] = buffer[i];
        }
        else if (buffer[i] == '(')
        {
            push(buffer[i]);
        }
        else if (ICP(buffer[i]) > ISP(stack[top]))
        {
            push(buffer[i]);
        }
        else if (buffer[i] == ')')
        {
            while (stack[top] != '(')
            {
                char ch = pop();
                ans[counter++] = ch;
            }
            pop();
        }
        else if (ICP(buffer[i]) < ISP(stack[top]))
        {
            while (ICP(buffer[i]) < ISP(stack[top]))
            {
                char ch = pop();
                ans[counter++] = ch;
            }
            push(buffer[i]);
        }
        else
        {
            printf("check");
            continue;
        }
    }

    while (top != -1)
    {
        char ch = pop();
        ans[counter++] = ch;
    }

    ans[counter] = '\0';
    printf("Postfix : %s\n", ans);

    return 0;
}