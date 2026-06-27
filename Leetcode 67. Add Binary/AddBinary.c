#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* addBinary(char* a, char* b);
void reverseString(char *str);

int main(void) {
    char *a = "1010";
    char *b = "1101";

    char* binary_sum = addBinary(a,b);

    printf("The binary sum of %s and %s is: %s", a, b, binary_sum);
    free(binary_sum);
}

char* addBinary(char* a, char* b) {
    int carry = 0;

    int lenA = strlen(a);   
    int lenB = strlen(b);
    int maxSize = (lenA > lenB ? lenA : lenB) + 2; 

    int i = lenA - 1;
    int j = lenB - 1;

    //+1 for the potential carry and +1 for the null-terminator.
    char *result = (char *)malloc(maxSize * sizeof(char));
    int k = 0;//for result "indexer"

    while(carry == 1 || i >= 0 || j >= 0) {
        if (i >= 0) carry += a[i--] - '0';
        if (j >= 0) carry += b[j--] - '0';

        result[k++] = (carry%2) + '0';
        carry /= 2;
    }
    result[k] = '\0';

    reverseString(result);
    return result;
}

void reverseString(char *str) {
    int start = 0;
    int end = strlen(str) - 1; // Last character before '\0'
    
    while (start < end) {
        // Swap the characters
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        
        // Move the pointers closer together
        start++;
        end--;
    }
}