#ifndef HANGMAN_H
#define HANGMAN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <stdbool.h>
#include <ctype.h>
#include "settings.h"

#define Wlength 50
#define Hlength 100

typedef struct{
	char word[Wlength];
	char hint[Hlength];
}Word;

//function declarations
int createWordFile();
void display();
bool game();
int getUpper();
int randInt();
Word setup(int upperLimit);
void startup(int * failCount, int * upperLimit);
bool storeUpper();

#endif
