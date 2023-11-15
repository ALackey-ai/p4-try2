/*
*TODO: You must replace this header file with what is posted on the class website!
*/
#ifndef LAB_H
#define LAB_H
#include <stdlib.h>
#include <stdbool.h>
#include <lab_export.h>

#define MAX_VERSION_STRING 10

#ifdef __cplusplus
extern "C"
{
#endif

  /**
   * @brief Entry point for the main function. If your project requires a main
   * then you will write your code in the myMain function. If your project
   * does NOT require a main (i.e. you are writing a library) then this
   * function will be empty.
   *
   * @param argc The argument count
   * @param argv The argument array
   * @return The exit code
   */
  LAB_EXPORT int myMain(int argc, char **argv);

  /**
   * @brief Returns a string containing the version of the library. This string
   * has been allocated using malloc and must be freed by the caller. The
   * version of the library is generated using the cmake version.
   *
   * @return char* The version string
   */
  LAB_EXPORT char *fooVersion(void);

  /**
   * @brief Example function that adds two numbers together.
   *
   * @param a The first number
   * @param b The second number
   * @return The sum of the two numbers
   */
  LAB_EXPORT int add(int a, int b);

  /**
   * @brief Function that leaks some data!
   *
   * @param a some number
   * @return a pointer to some memory
   */
  LAB_EXPORT int *leak(int a);

  /**
   * @brief This function causes a segfault
   *
   */
  LAB_EXPORT int segfault(void);

  /**
   * @brief This function causes an array out of bounds error
   *
   */
  LAB_EXPORT void outOfBounds(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif
