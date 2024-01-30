/*
  Operating Systems
  Semester 1 5784
  Kinneret College on the Sea of Galilee
  Michael J. May
  
  Assignment 2:
  Find lines with uniform word length.

*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include "uniform_length_lines.h"

/* The maximum length of each word in a file */
#define MAX_LINE_LEN 2000

/*
 * TODO: Fill in the documentation header.
 */
/*
int word_length(char* word) {
    int length = 0;
    
    // Iterate through each character in the word
    for (int i = 0; word[i] != '\0'; i++) {
        // Check if the character is alphabetic
        if (isalpha(word[i])) {
            length++;
        }
    }

    return length;
}
*/

/*
 * TODO: Fill in the documentation header.
 */
/*
int print_uniform_length_words(FILE* inFile, char* fileName) {
    int lineCount = 0;

    // Read the file in line by line
    char line[MAX_LINE_LEN];
    while (fgets(line, sizeof(line), inFile) != NULL) {
        // Tokenize the line into words using strtok
        char* word = strtok(line, " ");

        // Variables to track uniform word length
        int prevLength = -1; // To store the length of the previous word
        bool uniformLength = true; // Flag to track if all words have the same length on a line

        // Process each word in the line
        while (word != NULL) {
            // Count the length of the current word
            int currentLength = word_length(word);

            // Check if the word consists solely of non-alphabetic characters
            if (currentLength > 0) {
                // Check if this is the first word or if its length matches the previous word
                if (prevLength != -1 && currentLength != prevLength) {
                    uniformLength = false;
                    break; // No need to continue checking if lengths are not uniform
                }

                // Update the previous word length
                prevLength = currentLength;
            }

            // Get the next word
            word = strtok(NULL, " ");
        }

        // Check if the line has uniform word length and has at least 2 words
        if (uniformLength && prevLength != -1) {
            printf("%s: %d: %d: %s", fileName, lineCount + 1, prevLength, line);
            lineCount++;
        }
    }

    return lineCount;
}
*/

/*
 * TODO: Fill in the documentation header.
 */

int print_uniform_length_words(FILE* inFile, char* fileName) {
    int lineCount = 0;

    // Read the file in line by line
    char line[MAX_LINE_LEN];
    while (fgets(line, sizeof(line), inFile) != NULL) {
        // Tokenize the line into words using strtok
        char* word = strtok(line, " ");

        // Variables to track uniform word length
        int prevLength = -1; // To store the length of the previous word
        bool uniformLength = true; // Flag to track if all words have the same length on a line

        // Process each word in the line
        while (word != NULL) {
            // Count the length of the current word
            int currentLength = word_length(word);

            // Check if the word consists solely of non-alphabetic characters
            if (currentLength > 0) {
                // Check if this is the first word or if its length matches the previous word
                if (prevLength != -1 && currentLength != prevLength) {
                    uniformLength = false;
                    break; // No need to continue checking if lengths are not uniform
                }

                // Update the previous word length
                prevLength = currentLength;
            }

            // Get the next word
            word = strtok(NULL, " ");
        }

        // Check if the line has uniform word length and has at least 2 words
        if (uniformLength && prevLength != -1) {
            // Print the output in the desired format
            printf("%s:%6d: length %2d: %s", fileName, lineCount + 1, prevLength, line);
            lineCount++;
        }
    }

    return lineCount;
}

int main(int argc, char *argv[]) {
    // TODO: Read the file or STDIN
    // TODO: Process each file or STDIN in a separate process (use fork!)
    // TODO: Output the final message with total children and how many total lines there were. (use wait!)

    int totalLinesFound = 0;
    int totalChildren = 0;

    // Loop through each file provided in the command line arguments
    for (int i = 1; i < argc; i++) {
        FILE* inFile = fopen(argv[i], "r");

        if (inFile == NULL) {
            perror("Error opening file");
            continue;
        }

        // Fork a new process
        pid_t childPid = fork();

        if (childPid == -1) {
            perror("Error forking process");
            exit(EXIT_FAILURE);
        } else if (childPid == 0) {
            // Child process
            int linesFound = print_uniform_length_words(inFile, argv[i]);
            fclose(inFile);
            exit(linesFound);
        } else {
            // Parent process
            totalChildren++;
            fclose(inFile);
        }
    }

    // Wait for all child processes to finish
    int status;
    pid_t terminatedChild;
    while ((terminatedChild = wait(&status)) != -1) {
        if (WIFEXITED(status)) {
            // Get the exit status of the child process
            int linesFoundByChild = WEXITSTATUS(status);
            totalLinesFound += linesFoundByChild;
        } else {
            // Handle errors if any
            perror("Child process terminated abnormally");
        }
    }

    // Output the completion message
    printf("%d children finished. Total %d lines found.\n", totalChildren, totalLinesFound);

    return 0;
}

int word_length(char* word) {
    int length = 0;
    
    // Iterate through each character in the word
    for (int i = 0; word[i] != '\0'; i++) {
        // Check if the character is alphabetic
        if (isalpha(word[i])) {
            length++;
        }
    }

    return length;
}
