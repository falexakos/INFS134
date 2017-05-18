#include <stdio.h>
#include <stdlib.h>

#define VERSION 0.1

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Syntax: %s <filename>\n", argv[0]);
        exit(1);
    }
    return 0;
}