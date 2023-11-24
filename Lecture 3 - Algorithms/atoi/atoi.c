#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    if (input[0] == '\0') 
    {
        return 0;
    }
    int m=strlen(input)-1; //get index of last char 
    int last = input[m]-'0'; //convert last char into an integer value
    input[m] = '\0'; //shorten the string, removing the last char
    return (convert(input)*10) + last; //recursively call convert using the shortened string as input, where the next char will be processed.
} 