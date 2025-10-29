#include <stdio.h>
#include <string.h>

int main()
{

    FILE *fp = fopen("/Users/akhilgireesh/Programming/compiler/code/input.txt", "r");
    char line[50], lhs[50], rhs[50];

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        // Parse the line (assuming simple format "lhs = rhs;")
        sscanf(line, "%s = %[^\n]", lhs, rhs); // Read lhs and rhs

        printf("%s = %s\n", lhs, rhs);
        // Process each line
        // processLine(lhs, rhs);
    }
    return 0;
}