#include <stdio.h>
#include <stdlib.h>
/*
We use the standard library for 2 functions:
1. calloc() (COntiguous Allocation) - if you want to create an array with unknown
size, this method dynamically allocates a chunk of memory, initializing all values to 0.
2. free() - since we requested memory from OS using calloc(), we must return it back to the 
Operating System. Basically we wipe the memory chunk we used then return it to OS
to make it available again.
*/

// Helper macro to find the maximum of two values
#define MAX(a, b) ((a) > (b) ? (a) : (b)) 
/*
#define is a preprocessor (a program that runs before compilation) directive that creates a macro.
a macro is a rule that tells computer to replace a specific "word" (inputs) with a block of text
or code before compilaton. 

the code above is a function-like macro that finds the larger of two numbers (like Math.max() in Java).
- the equivalent of "word" in the code is MAX(a, b)
- then the formula that replaces the "word" is ((a) > (b) ? (a) : (b))

If we compare it to Java, when we use Math.max(), Java basically calls a method, then 
jumps over to the mAth class (teh behind the scenes) then returns back the answer.

In C, its literally like manual formatting. 
Basically: the code above --> becomes text --> C finds what should be replaced 
--> replaces it with the formula --> then compiles the code.

How does C convert it to something like a text?
- C has a cpp program (C preprocessor) and when #define (specifically the #) 
is used, it calls cpp, the reads it

Lastly, the "MAX" isnt read by C, it actually ignores it/doesnt know what it is.
So why do we have it? For people to understand what the formula for/is doing, basically
just a label. If we were to drop it, the code works perfectly fine.
*/

int maxDamage(int W, int staminaCost[], int damage[], int n) {
    // Dynamic array allocation based on W + 1 (using calloc to initialize all values to 0)
    int *dp = (int *)calloc(W + 1, sizeof(int)); 
    
    for (int i = 0; i < n; i++) {
        // Loop backwards from W down to the current attack's stamina cost
        for (int w = W; w >= staminaCost[i]; w--) {
            dp[w] = MAX(dp[w], dp[w - staminaCost[i]] + damage[i]);
        }
    }
    
    int result = dp[W];
    
    // Always free dynamically allocated memory in C
    free(dp); 
    
    return result;
}

int main() {
    // Tiny stamina pool for an effortless live trace
    int W = 10; 

    int staminaCost[] = {3,  6,  4,  7,  2};
    int damage[]      = {30, 70, 45, 90, 15};
    
    // Calculate the length of the arrays in C
    int n = sizeof(damage) / sizeof(damage[0]);

    int result = maxDamage(W, staminaCost, damage, n);

    printf("⚔️RESULT (W = 10) ⚔️\n");
    printf("Maximum Damage Output: %d HP\n", result); 
    // Output: 120 (Index 3 + Index 0)

    return 0;
}