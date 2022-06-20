// Questions
// #0 What part of the code can be used to identify that this is C code (not C++)
// #1 Where is "Welcome!\n" allocated?
// #2 Where is data allocated?
// #3 Where is my_string allocated?
// #4 What issues do you see with the code?
// #5 What will be the output of the code?

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
    fprint(stdout, "Welcome!\n");

    void* ptr[1000000];
    for (int i = 0; i < 1000000; i++)
    {
        char* data = malloc(50);
        strcpy(data, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
        ptr[i] = data;
    }
    for (int i = 0; i < 1000000; i++)
    {
        free(ptr[i]);
        ptr[i] = NULL;
    }

    char* my_string = malloc(25);
    strncpy(my_string, "hello world!", 5);
    fprintf(stderr, "output: %s\n", my_string);
    
    return 1;
}