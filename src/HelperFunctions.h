
#ifndef HELPER_FUNCTIONS
#define HELPER_FUNCTIONS

#include <stdio.h>
#include <unistd.h>
#include <memory.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

unsigned int index_of_string_first(const char* str, const char* pattern);

unsigned int index_of_string_last(const char* str, const char* pattern);


char* join_strings(const char* str1, const char* str2);



#endif
