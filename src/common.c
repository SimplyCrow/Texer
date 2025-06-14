#include <stdio.h>

void todo(const char* message)
{
        printf("ERROR: Function not yet implemented (%s)", message);
}

void *todo_ptr(const char* message)
{
        todo(message);
        return NULL;
}
