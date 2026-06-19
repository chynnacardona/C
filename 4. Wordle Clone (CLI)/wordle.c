#include <stdio.h>
#include <string.h> //string.h contains functions designed to manipulate and handle strings
#include <ctype.h> //ctype.h stands for character type, a library w tools to test and manipulate chars

#define WORD_LEN 7
#define MAX_TRIES 5

#define COLOR_GREEN  "\x1b[32m" //ANSI Escape Sequences. They are universal, hidden command codes that tell your terminal emulator to change its text brush color.
#define COLOR_YELLOW "\x1b[33m" 
#define COLOR_RESET  "\x1b[0m" //Reset back to default

int main() {
    char word[] = "program";
    char guess[WORD_LEN + 1];
    int tries = 0;
    int won = 0; //acts like a boolean

    printf("CLI - WORDLE\n");
    printf("Guess the %d-letter word. You have %d tries.\n\n", WORD_LEN, MAX_TRIES);

    while (tries < MAX_TRIES && !won) {
        printf("Try %d/%d. Enter your guess!: ", tries + 1, MAX_TRIES);
        fflush(stdout); // Flash the buffer to show the prompt immediately!
        /*
        - stdout -- meand 'standard output' like a shipping container has a specific rule for when it empties itself onto your screen: It waits until it sees a newline character (\n)
        and this container sits in our RAM. This is where everything in printf() lives
        - fflush() -- force flush, manual override, so that whatever is in prntf() even if theres no \n, it prints on screen

        Notice that we didn't put '\n' in the end so that the user input stays within that line. 
        Because there is no \n, the operating system might look at the stdout shipping container and say,
        "Well, the line isn't finished yet, and the container isn't full, so I'm just going to hold onto this text in RAM for a bit." = game freezes
        thats why we use fflush.

        visualization on whats happening: 
        printf() --> stdout (container of whats in printf()) --> resides in a specific RAM slot --> waits for \n or force flush --> print whats in stdout to the screen, emptying the RAM slot
        */
        scanf("%s", guess);

        /*
        The for loop below is to convert the user input to lowercase entirely (each char since we dont have built-in string data type in  -- strings are arrays in C)

        notice below that the 2nd statement 'guess[i]' is unlike the ones we see in Java.
        in Java, we may use: 

        char[] newArr = new char[guess.length()]; -- we use .length() since it will be a String input for Java. guess is the string input
        String lowerGuess = guess.toLowerCase();

        for (int i = 0; i < lowerGuess.length(); i++) {
            newArr[i] = lowerGuess.charAt(i); 
        }
        
        in C, the guess[i] part acts like a boolean rule. How?
        lets say we have the string "hi" - the characters are converted into ASCII value (integer)
        so if we iterate the that word, h = 104, i = 105, then NULL TERMINATOR which is 0 (written as \0) since theres no more charater to read
        so when guess[i] == 0 then it esentially means "false" and the loop stops

        */
        for (int i = 0; guess[i]; i++) {
            guess[i] = tolower(guess[i]); //as we can se, we can modify the array ITSELF since we can access the RAM slot where the chars reside DIRECTLY
            //Java is more secure in this sense because JVM is the one that holds the key to that slot, while C directly has it -- making it easier to access but prone to security issues
        }

        if (strlen(guess) != WORD_LEN) {
            printf("Error: Guess must be %d letters long. \n", WORD_LEN);
            continue; // Skip the rest of the loop and ask for input again
        }

        tries++;

        printf("Feedback: ");
        for (int i  = 0; i < WORD_LEN; i++) {
            if (guess[i] == word[i]) { //is char matched at exact same spot
                printf("%s%c%s", COLOR_GREEN, toupper(guess[i]), COLOR_RESET);
            } 
            //if char is in the string
            else if (strchr(word, guess[i]) != NULL) { //strchr finds a character inside a string -- like a pointer pointing to every char in word[] comparing it to guess[]
                printf("%s%c%s", COLOR_YELLOW, toupper(guess[i]), COLOR_RESET);
            }
            else { 
                printf("%c", toupper(guess[i]));
            }
        }
        printf("\n\n");

        //strcmp() -- String compare character by character
        if (strcmp(guess, word) == 0) {
            won = 1;
        }
    }

    if (won) {
        printf("Congratulations! You guessed the word in %d tries!\n", tries);
    }
    else {
        printf("Game over. The secret word was: %s\n", word);
    }

    return 0;
}