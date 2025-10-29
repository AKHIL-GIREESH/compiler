#include <stdio.h>
#include <string.h>

int top = -1;
char stack[50];

void push(char val)
{
    stack[++top] = val;
}

void pop(int val)
{
    top -= val;
}

int reduce()
{
    if (stack[top] == 'I')
    {
        pop(1);
        push('F');
        printf("I -> F\n");
        return 1;
    }
    else if (stack[top] == ')' && stack[top - 1] == 'E' && stack[top - 2] == '(')
    {
        pop(3);
        push('F');
        print("(E) -> F\n");
        return 1;
    }
}

int main()
{
    FILE *fp = fopen("input.txt", "r");

    if (!fp)
    {
        printf("Err");
        return 1;
    }

    char ch = fgetc(fp);

    while (ch != EOF)
    {
        push(ch);

        while (reduce())
            ;
    }

    return 0;
}
