#include <stdio.h>
#include <string.h>

#define MAX_INPUT 5 
/*
equivalent of data objects in Java:
public class Books {
    public String title;
    public String author;
    public int pubDate;
    public String origin;
}

Call the objects via (non static):
    Books book = new Books();
    book.title = "ble bla";
*/

struct Info {
    char title[100];
    char author[50];
    int pubDate;
    char origin[50];
};

/*
Function prototype/declaration - passing the array of structs, a heads-up notice to the C compiler.
the * is a pointer, a variable that stores a memory address
the "list" is like the name of the variable pointing to Info (and what will be inputted)
*/ 
void getEntries(struct Info *list, int max_entries);

/*doing int main(void) is better that int main() -- the (void) talks to the compiler to
block any random input in the terminal when we do 'clang -Wall..' or './filename'

Why is this important and secure?
1. int main() means unspecified arguments. The compiler assumes ypu know what your doing, lowering its defenses
and skipping the warnings. If a an accidental parameter/input (typing extra pieces of information right next 
to the command when launching it in the terminal.) is passed in the program, the compiler may stay silent and ignore -Wall.
2. Hidden memory stack risk: lets say you put extra parameters while running the file 
'./calculator 42 "garbageData" 999' the OS doesnt know that some of those characters are accidental/shouldnt be there
so it takes all those values and pushes it onto the program's Call Stack (Stack Frame - single plate within call stack) -- a temporary memory space where functions store their variables)
3. Exploits and code injections: without (void), we leave the door opwn. An attacker can intentionally feed malicious inputs into the terminal
when launchig the program. BUT that alone is not enough for them to pull off an exploit or code injection.
*/
int main(void) {
    struct Info library[MAX_INPUT];

    printf("----- REGISTRY SYSTEM -----\n");
    getEntries(library, MAX_INPUT);

    printf("\n----- BOOK LIST -----\n");
    for (int i = 0; i < MAX_INPUT; i++) {

    }

    FILE *filePointer = fopen("books.txt", "r");

    if (filePointer == NULL) {
        printf("Error: Could not open file.\n");
        return 1; 
    }

    //basically putting the data in the file in an array
    char fileData[100]; //every line we get 100 chars max

    while(fgets(fileData, sizeof(fileData), filePointer) != NULL) {
        printf("%s", fileData);
    }

    return 0;
}

void getEntries(struct Info *list, int max_entries) {
    int i = 0;

    FILE *filePointer = fopen("books.txt", "w");

    if (filePointer == NULL) {
        printf("Error opening file!\n");
        return;
    }

    while (i < max_entries) {
        printf("\n* Entry %d of %d:\n", i + 1, max_entries);

        printf("Title: ");
        // 1. The [^\n] lets you capture spaces in the title!
        scanf(" %99[^\n]", list[i].title);

        printf("Author: ");
        // 2. Added a leading space here to eat the leftover '\n' from the title entry
        scanf(" %49[^\n]", list[i].author);

        printf("Publication Year: ");
        // 3. Added a leading space here too
        scanf(" %d", &list[i].pubDate);

        printf("Country of Origin: ");
        // 4. Added a leading space here too
        scanf(" %49[^\n]", list[i].origin);

        // 5. Clean up the very last newline before the next loop iteration spins around
        while (getchar() != '\n');

        fprintf(filePointer, "%s\t%s\t%d\t%s\n", list[i].title, list[i].author, list[i].pubDate, list[i].origin);

        i++;
    }

    fclose(filePointer);   
}
