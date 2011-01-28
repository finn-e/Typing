/*
 *  charsets.h
 *  Typing
 *
 *  Created by Michael Dickens on 8/7/09.
 *
 */
 
#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "values.h"

#define streq(str1, str2) (strcmp(str1, str2) == 0)
#define streqn(str1, str2, n) (strncmp(str1, str2, n) == 0)
 
#define MAX_TRI_LEN 5000
#define MAX_DI_LEN 5000
#define MAX_MON_LEN 100

long long totalMon;
long long totalDi;
int monLen, diLen, triLen;

/* Constant definitions */

#define LEFT 0
#define RIGHT 1

#define PINKY 0
#define RING 1
#define MIDDLE 2
#define INDEX 3

/* Reduces monValues and diValues so as to prevent integer overflow. */
#define DIVISOR 100

typedef struct {
	char layout[KSIZE_MAX + 1]; /* The one extra character is set to '\0' so 
								(layout) can be treated as a string. */
	long long fingerUsage[8];
	long long shortcut;
	long long fitness;
	long long distance;
	long long inRoll;
	long long outRoll;
	long long sameHand;
	long long sameFinger;
	long long rowChange;
	long long homeJump;
	long long toCenter;
	long long toOutside;
} Keyboard;



Keyboard nilKeyboard;

/* These are declared here because C's file hierarchy is stupid.
 */
Keyboard atleMutate(Keyboard k);
Keyboard simpleMutate(Keyboard k);
Keyboard mutate(Keyboard k);

int rand30();
int mod30(int x);
void copyArray(int out[], int in[], int length);
int strNumsToArr(int arr[], char *str, int length);
char layoutFromFile(FILE *fp, Keyboard *k);
int initData();
void initKeyboardData();
void initTypingData();
int compileTypingData(char *outfileName, char *filenames[], int multipliers[], int length, int unit, char *legalKeys, int max);
int sortTypingData(char **keys, int *values, int left, int right);

int setValue(char *str);
int getValue(char *name);

int qwerty[30];

int randomizer;
struct timeval tv;

/* For each key, indicates which hand (LEFT or RIGHT) is responsible for typing that key.
 */
int hand[KSIZE_MAX];

/* For each key, indicates which finger (PINKY, RING, MIDDLE or INDEX) is responsible for 
 * typing that key.
 */
int finger[KSIZE_MAX];

/* For each key, indicates which row that key lies on. The top row is 0, the row below it 
 * is 1, the row below that is 2, etc.
 */
int row[KSIZE_MAX];

/* Indicates which row is the home row.
 */
int homeRow;

/* For each key, indicates whether that key requires a reach to the center.
 */
int isCenter[KSIZE_MAX];

/* For each key, indicates whether that key requires a reach to the outside.
 */
int isOutside[KSIZE_MAX];

/* For each key, indicates whether that key requires a reach to the center OR a reach to 
 * the outside. This one is produced automatically from isCenter[] and isOutside[].
 */
int isCenterOrOutside[KSIZE_MAX];

/* For each key, indicates whether that key should be printed. Any place-holder key that 
 * does not actually exist on the keyboard should not be printed.
 */
int printIt[KSIZE_MAX];

int costs[900];

char triKeys[MAX_TRI_LEN][3];
long long triValues[MAX_TRI_LEN];

char diKeys[MAX_DI_LEN][2];
long long diValues[MAX_DI_LEN];

char monKeys[MAX_MON_LEN];
long long monValues[MAX_MON_LEN];

/* Used in cjalgorithm.c. */
int indices[KSIZE_MAX];
