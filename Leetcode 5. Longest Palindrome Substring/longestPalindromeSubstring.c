#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

char* getSubstring(char *s, int start, int end);
char* longestPalindrome(char *s);

int main(void) {
    /*
    char pointers because String is not a data type in C, but an array of chars
    the string "babad" is stripped into individual chars, dumped side-by-side
    into a read-only section of RAM, followed by a \0 (null terminator)
    */
    char *s = "babad";
    char *longestP = longestPalindrome(s);

    printf("Longest Palindrome for %s is: %s", s, longestP);
    free(longestP);
    /*
    the free() is for the function call on char *result = getSubstring(s, start, end);
    -- malloc() is used inside the function, so we need to free that. malloc() or "memory allocation" 
        reserves a specific block of memory on the heap at runtime
    -- we cannot free() this inside the longestPalindrome() or getSubstring() because
        it holds the value "bab" so we can print it out. 
    -- free() destroys the memory box holding it, but we do need to free it becaus eits "borrowed"
    */

    return 0;
}

char* longestPalindrome(char *s) {
    int maxLen = 1;
    int len = strlen(s);
    int start = 0, end = 0;

    bool **dp = (bool **)calloc(len, sizeof(bool *)); //*dp -- 1D array, **dp -- 2D array
    for (int i = 0; i < len; i++) {
        dp[i] = (bool *)calloc(len, sizeof(bool)); 
    }

    for (int i = 0; i < len; i++) {
        dp[i][i] = true;
        for (int j = 0; j < i; j++) {
            if (s[j] == s[i] && (i - j <= 2 || dp[j + 1][i - 1])) {
                dp[j][i] = true;
                if (i - j + 1 > maxLen) {
                    maxLen = i - j + 1;
                    start = j;
                    end = i;
                }
            }
        }
    }
    char *result = getSubstring(s, start, end);

    for (int i = 0; i < len; i++) {
        free(dp[i]);
    }
    free(dp);
    /*
    we cannot just ise free(dp) like we did in StaminaOptimization.c -- this uses 1D array.
    In this code we are using a 2D array, so each row is allocated completely separately in 
    different parts of the RAM. So essentially, we have multiple calloc calls to build it, 
    thus, needing multiple free() calls to tear it down. (1D arrays only have 1 row)
    */

    return result;
}

char* getSubstring(char *s, int start, int end) {
    int sub_len = (end + 1) - start; //calculates exact number of letters for the new substring
    char *sub = (char *)malloc((sub_len +1) * sizeof(char));
    /*
    so malloc((sub_len +1) * sizeof(char)) basically means that we are allocating an array 
    with sub_len + 1 length, and each "block" inside that array holds a char with a size of sizeof(char)
    */
    if (sub == NULL) return NULL;

    strncpy(sub, s + start, sub_len);
    //This copies the specific letters from the old string into your new heap box. (sub is the heap box)
    sub[sub_len] = '\0';

    return sub;
}