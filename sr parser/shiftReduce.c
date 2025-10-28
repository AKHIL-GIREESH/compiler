#include <stdio.h>
#include <string.h>

#define MAX 100

char input[MAX], stack[MAX];
int top = -1;

// Function to push symbol to stack
void push(char c)
{
    stack[++top] = c;
    stack[top + 1] = '\0';
}

// Function to pop (reduce)
void popN(int n)
{
    top -= n;
    stack[top + 1] = '\0';
}

// Try to reduce the stack based on grammar rules
int reduce()
{
    // F → id
    if (top >= 1 && stack[top - 1] == 'i' && stack[top] == 'd')
    {
        popN(2);
        push('F');
        printf("Reduce: F -> id\t\tStack: %s\n", stack);
        return 1;
    }

    // F → (E)
    if (top >= 2 && stack[top - 2] == '(' && stack[top - 1] == 'E' && stack[top] == ')')
    {
        popN(3);
        push('F');
        printf("Reduce: F -> (E)\tStack: %s\n", stack);
        return 1;
    }

    // T → T * F
    if (top >= 2 && stack[top - 2] == 'T' && stack[top - 1] == '*' && stack[top] == 'F')
    {
        popN(3);
        push('T');
        printf("Reduce: T -> T*F\tStack: %s\n", stack);
        return 1;
    }

    // T → F
    if (stack[top] == 'F')
    {
        popN(1);
        push('T');
        printf("Reduce: T -> F\t\tStack: %s\n", stack);
        return 1;
    }

    // E → E + T
    if (top >= 2 && stack[top - 2] == 'E' && stack[top - 1] == '+' && stack[top] == 'T')
    {
        popN(3);
        push('E');
        printf("Reduce: E -> E+T\tStack: %s\n", stack);
        return 1;
    }

    // E → T
    if (stack[top] == 'T')
    {
        popN(1);
        push('E');
        printf("Reduce: E -> T\t\tStack: %s\n", stack);
        return 1;
    }

    return 0;
}

int main()
{
    FILE *fp = fopen("input.txt", "r");
    if (!fp)
    {
        printf("Error: could not open input.txt\n");
        return 1;
    }

    fscanf(fp, "%s", input);
    fclose(fp);

    printf("Input: %s\n\n", input);
    printf("SHIFT-REDUCE PARSER TRACE\n");
    printf("-------------------------\n");

    int i = 0;
    while (1)
    {
        if (i < strlen(input))
        {
            push(input[i++]);
            printf("Shift\t\t\tStack: %s\n", stack);
        }

        while (reduce())
            ; // keep reducing whenever possible

        if (i == strlen(input))
        {
            // end of input and final reduction check
            if (strcmp(stack, "E") == 0)
            {
                printf("\n✅ Input accepted. Reduced to E.\n");
                break;
            }
            else if (i >= strlen(input))
            {
                printf("\n❌ Input rejected. Final stack: %s\n", stack);
                break;
            }
        }
    }

    return 0;
}
