#include <stdio.h> 
// Standard I/O library. Needed for printing to the screen and taking user input.

int main() {
    char operator;
    double num1, num2, res = 0.0;
    /*
    we initialize res to 0.0 to avoid garbage value in case of invalid operator
    because the cycle is WRITE → READ → BREAK.

    let's say we didn't initialize res, what we need to do is put the printf()
    immediately after the assignment of values. In this case, the printf() 
    statement is outside the switch-case statement, MEANING inside the case,
    we only have WRITE and BREAK.

    ALTHOUGH it will technically work even if we dont initialize it or follow 
    the cycle, but this has a catch. In C, this is called Undefined Behavior (UB). 
    It is one of the most famous and dangerous concepts in low-level programming, 
    and it behaves completely differently than what we do in Java.

    - In C: The compiler acts like an indifferent coworker. By default, clang 
    and gcc will only issue a Warning, not a hard error. C will happily finish 
    compiling your code, hand you an executable binary, and say, 
    "Good luck, hope you know what you're doing!"

    If you force-run the program without initializing res, the computer will 
    not crash immediately. Instead, it will read whatever random electronic noise
    is left over in that specific RAM slot. Because RAM is constantly recycled by
    your operating system, that memory slot might contain pieces of an old Zoom call, 
    data from a browser tab, or remnants of another program.

    BASICALLLY: Since C is a very low-language, close to machine language, it gives 
    you direct control of the hardware. This can cause Data Leaking and Memory Leaks.
    So with the statement above about memory slot containing remnants of another 
    program, it means that if we dont "listen" to the warnings the compiler gives,
    like the uninitialized variable, that variable will read a specific RAM spot that 
    may contain remnants. 

    Not conforming to warnings can also "eat" RAM storage. In this case, res wont really
    eat extra RAM space since res is already declared as double (8 bytes). HOWEVER,
    that "memory leak" can still happen in a different scenario.

    SUMMARY: even though the code will technically work, it is not a correct.
    */


    printf("SIMPLE CALCULATOR\n");
    printf("==================\n");
    printf("Choose operation):\n");
    printf("1. Addition (+)\n");
    printf("2. Subtraction (-)\n");
    printf("3. Multiplication (*)\n");
    printf("4. Division (/)\n");
    printf("==================\n");
    printf("Enter operator: ");
    scanf(" %c", &operator); // 'c' indicares a char will be read
    
    //In C we can input multiple values in one line with space
    //unlike in Java, if we were to do this, we need to input the values as a string and split it
    printf("Enter two numbers separated by a space: ");
    scanf("%lf %lf", &num1, &num2);

    switch (operator) {
        case '+':
            res = num1 + num2;
            break;
        case '-':
            res = num1 - num2;
            break;
        case '*':
            res = num1 * num2;
            break;
        case '/':
            if (num2 != 0) {
            } else {
                printf("Error: Division by zero is not allowed.\n");
                return 1;
            }
            break;
        default:
            printf("Error: Invalid operator.\n");
            return 1;
    }

    printf("Result: %.2lf\n", res);

    return 0; //0 means success
}

/*
When a program finishes running, it has to report its status back to the 
command line or Operating System that started it.

- If a program succeeds, it just needs to say: 
"Everything went perfectly." A single number (0) is perfect for this.

- If a program fails, the operating system and the developer need to know 
exactly why it failed.

By reserving 0 for success, C frees up all the other numbers (1 to 255 or more) 
to act as specific error codes.
*/