// the "imports"
#include <stdio.h>
#include <stdlib.h> //Standard Library: for random number functions
#include <time.h> //Time library: get current system time

/*
The program will generate a random number between 1 and N
and checks if the user's input is correct.
*/

void guess(int N) {
    int num, guess, numberOfGuesses = 0;
    
    /*Seeds the random number generator using the current time. 
    Without this, rand() would generate the exact same "random" number 
    every time you run the program.*/
    srand(time(NULL));
    /*rand() generates a random number. The + 1 slides the entire number window
    to the right/by 1. Without +1, it will be 0-99, instead of 1-100 (if N = 100)*/
    num = rand() % N + 1; 

    printf("Guess a number between 1 and %d: ", N);

    do {
        if (numberOfGuesses > 6) { //5 tries
            printf("You loose! The number was %d.\n", num); //%d is for integers
            break;
        }
        scanf("%d", &guess);

        if (guess > num) {
            printf("Lower number, please: \n");
            numberOfGuesses++;
        }
        else if (guess < num) {
            printf("Higher number, please: \n");
            numberOfGuesses++;
        }

        else {
            printf("Congratulations! You guessed the number in %d tries.\n", numberOfGuesses);
            break;
        }
    } while (guess != num);
}

int main() {
    int N = 100;
    guess(N);

    return 0;
}