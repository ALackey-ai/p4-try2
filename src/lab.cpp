#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "lab.h"
#include <labconfig.h>

#define UNUSED(x) (void)(x)

/*Implementations for functions defined in lab.h*/

//Delete this sample function before submitting
int myMain(int argc, char **argv)
{
    using_history();
    char *line = (char *)NULL;
    line = readline("What is your name?");
    printf("Hello %s! This is the starter template version: %d.%d\n", line, lab_VERSION_MAJOR, lab_VERSION_MINOR);
    free(line);
    return 0;
}

//Delete this sample function before submitting
char *fooVersion(void)
{
    char *version = (char*) malloc(MAX_VERSION_STRING);
    snprintf(version,MAX_VERSION_STRING, "%d.%d", lab_VERSION_MAJOR, lab_VERSION_MINOR);
    return version;
}

//Delete this sample function before submitting
int add(int a, int b)
{
    return a + b;
}

//Delete this sample function before submitting
int* leak(int a)
{
  //add a leak1
  int* rval = (int*) malloc(sizeof(int));
  rval = (int*)malloc(sizeof(int));
  *rval = a;
  return rval;
}

//Delete this sample function before submitting
int segfault(void)
{
    //add volatile because clang will optimize out the segfault
    //gcc doesn't care and keeps it there LOL
    //msvc at least warns you in the VS IDE that you're dereferencing a null pointer
    volatile int* foo = nullptr;
    int bar = *foo;
    return bar;
}

//Delete this sample function before submitting
void outOfBounds(void)
{
    int arr[5] = {0,1,2,3,4};
    int i = 0;
    for(i = 0; i < 6; i++)
    {
        arr[i] = i;
    }
    UNUSED(arr);
}
