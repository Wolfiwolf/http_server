#include "HelperFunctions.h"


unsigned int index_of_string_first(const char* str, const char* pattern)
{
    int size_of_str = strlen(str);
    int size_of_pattern = strlen(pattern);

    for(int i = 0; i < size_of_str; ++i)
    {
        if(str[i] == pattern[0])
        {
            bool is_matching = true;

            int z = i;
            for(int p = 0; p < size_of_pattern && z < size_of_str; ++p)
            {
                if(str[z] != pattern[p])
                {
                    is_matching = false;
                    break;
                }
                ++z;
            }
            if(is_matching)
            {
                return i;
            }
        }
    }

    return 0;
}

unsigned int index_of_string_last(const char* str, const char* pattern)
{


    int size_of_str = strlen(str);
    int size_of_pattern = strlen(pattern);

    for(int i = 0; i < size_of_str; ++i)
    {
        if(str[i] == pattern[0])
        {
            bool is_matching = true;

            int z = i;
            for(int p = 0; p < size_of_pattern && z < size_of_str; ++p)
            {
                if(str[z] != pattern[p])
                {
                    is_matching = false;
                    break;
                }
                ++z;
            }
            if(is_matching)
            {
                return i + size_of_pattern;
            }
        }
    }

    return 0;
}


char* join_strings(const char* str1, const char* str2)
{
    int size_of_str1 = strlen(str1);
    int size_of_str2 = strlen(str2);

    char* joined_str = (char*)malloc(size_of_str1 + size_of_str2);

    memcpy((void*)joined_str, str1, size_of_str1);
    memcpy((void*)&joined_str[size_of_str1], str2, size_of_str2);

    return joined_str;
}
