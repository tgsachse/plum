#include <stdio.h>
#include "analyzer.h"

// Call printFile for a source file.
void printSource(char *filename) {
    printFile(filename, "Source Program:\n---------------\n");
}

// Call printFile for a lexeme file.
void printLexemeList(char *filename) {
    printFile(filename, "Lexeme List:\n------------\n");
}

// Print the contents of the file, as well as a header label.
void printFile(char *filename, char *header) {
    FILE *f;
    char buffer;

    if ((f = fopen(filename, "r")) == NULL) {
        return;
    }

    // Print every character in the file.
    printf("%s", header);
    while(fscanf(f, "%c", &buffer) != EOF) {
        printf("%c", buffer);
    }

    // Don't leave your files open like a monkey.
    fclose(f);
}

// Standardizing function to print line in lexeme table.
void printLexemeTableLine(const char *lexeme, int lexemeValue) {
    printf("%12s | %d\n", lexeme, lexemeValue);
}

// Print entire lexeme table from lexeme file.
void printLexemeTable(char *filename) {
    FILE *f;
    int buffer;
    char word[IDENTIFIER_LEN + 1];

    // These lexemes directly map to the LexemeValues enumeration
    // defined in the analyzer header (with an offset of four).
    const char *lexemes[] = {
        "+", "-", "*", "/", "odd", "==", "!=", "<",
        "<=", ">", ">=", "(", ")", ",", ";", ".", ":=",
        "begin", "end", "if", "then", "while", "do",
        "call", "const", "var", "procedure",
        "write", "read", "else",
    };

    if ((f = fopen(filename, "r")) == NULL) {
        return;
    }

    // Print some custom header stuff for the table.
    printf("     :Lexeme | Value:\n");
    printf("     ----------------\n");

    // For each integer in the file, print the relevant symbol and lexeme value.
    while(fscanf(f, " %d", &buffer) != EOF) {
        // If the buffer is for an identifier or number, read the next
        // string in the file and then print.
        if (buffer == IDENTIFIER || buffer == NUMBER) {
            fscanf(f, "%s", word);
            printLexemeTableLine(word, buffer);
        }
        // Else print the lexeme from the lexemes array, with an offset of
        // four to account for the first four values in the enumeration not
        // being included.
        else {
            printLexemeTableLine(lexemes[buffer - 4], buffer);
        }
    }

    fclose(f);
}
