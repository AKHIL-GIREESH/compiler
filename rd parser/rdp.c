#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char inp[100];
int inplen, offset = 0;

void E();

void F()
{
    if (inp[offset] == '(')
    {
        offset++;
        E();
        if (inp[offset] == ')')
        {
            offset++;
        }
        else
        {
            printf("INVALID");
            exit(1);
        }
    }
    else if (inp[offset] == 'I')
    {
        offset++;
    }
    else
    {
        printf("INVALID");
        exit(1);
    }
}

void Tprime()
{
    if (inp[offset] == '*')
    {
        offset++;
        F();
        Tprime();
    }
}

void T()
{
    F();
    Tprime();
}

void Eprime()
{
    if (inp[offset] == '+')
    {
        offset++;
        T();
        Eprime();
    }
}

void E()
{
    T();
    Eprime();
}

int main()
{
    printf("Input the string : ");
    scanf("%s", inp);
    inplen = strlen(inp);
    E();

    if (offset == inplen)
    {
        printf("VALID");
    }
    else
    {
        printf("INVALID");
    }
    return 0;
}