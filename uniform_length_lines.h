/*
  Operating Systems
  Semester 1 5784
  Kinneret College on the Sea of Galilee
  Michael J. May
  
  Assignment 2:
  Find lines with uniform word length.

*/

#ifndef UNIFORM_LENGTH_LINES
#define UNIFORM_LENGTH_LINES

int word_length(char* word);
int line_uniform_length (char* line);
int print_uniform_length_words(FILE* inFile, char* fileName);
#endif
