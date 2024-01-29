/*
  Operating Systems
  Semester 1 5784
  Kinneret College on the Sea of Galilee
  Michael J. May
  
  Assignment 2:
  Find lines with uniform word length.

*/

// test commit

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "uniform_length_lines.h"

int main(int argc, char *argv[]) {
    int totalLinesFound = 0;
    int totalChildren = 0;

    // Check if command line arguments are provided
    if (argc > 1) {
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
    } else {
        // No command line arguments, read from STDIN
        totalChildren++;

        // Fork a new process for STDIN
        pid_t childPid = fork();

        if (childPid == -1) {
            perror("Error forking process");
            exit(EXIT_FAILURE);
        } else if (childPid == 0) {
            // Child process for STDIN
            int linesFound = print_uniform_length_words(stdin, "STDIN");
            exit(linesFound);
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

