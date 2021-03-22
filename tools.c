/*
 *  charsets.c
 *  Typing
 *
 *  Created by Michael Dickens on 8/7/09.
 *
 */

#include "tools.h"


void copyArray(int dest[], int src[], int length)
{
	memcpy(dest, src, length * sizeof(int));
}

void printTime(time_t start)
{
    time_t finish = time(NULL);
    printf("Time elapsed: %ld hours, %ld minutes, %ld seconds\n",
           (finish-start) / 3600, ((finish - start) % 3600) / 60,
           (finish-start) % 60);
}

int initData()
{
	initValues();
	
	int i, j;
	
	srand(time(0));
	
	for (i = 0; i <= ksize; ++i)
		nilKeyboard.layout[i] = nilKeyboard.shiftedLayout[i] = '\0';
	nilKeyboard.fitness = FITNESS_MAX;
	nilKeyboard.distance = 0;
	nilKeyboard.inRoll = 0;
	nilKeyboard.outRoll = 0;
	nilKeyboard.sameHand = 0;
	nilKeyboard.sameFinger = 0;
	nilKeyboard.rowChange = 0;
	nilKeyboard.homeJump = 0;
	nilKeyboard.toCenter = 0;
	nilKeyboard.toOutside = 0;
    
    strncpy(qwerty, "qwertyuiopasdfghjkl;zxcvbnm,./\0", 31);
	
	for (i = 0; i < 5; ++i)
		for (j = 0; j < 5; ++j) {
			rowChangeTableDown[i][j] = rowChangeDown;
			rowChangeTableUp[i][j] = rowChangeUp;
			if (i != THUMB && j != THUMB) {
				if (i == MIDDLE && j == INDEX) rowChangeTableDown[i][j] += handSmooth;
				else if (abs(i - j) == 1)      rowChangeTableDown[i][j] += handWarp;
				
				if (i == INDEX && j == MIDDLE) rowChangeTableUp[i][j] += handSmooth;
				else if (abs(i - j) == 1)      rowChangeTableUp[i][j] += handWarp;
			}
		}

	if (fullKeyboard == K_NO) strcpy(keysToInclude, DEFAULT_KEYBOARD_30);
	else if (fullKeyboard == K_STANDARD) strcpy(keysToInclude, DEFAULT_KEYBOARD_STANDARD);
	else if (fullKeyboard == K_KINESIS) strcpy(keysToInclude, DEFAULT_KEYBOARD_KINESIS);
	else if (fullKeyboard == K_NOKI) strcpy(keysToInclude, DEFAULT_KEYBOARD_NOKI);
	else if (fullKeyboard == K_NOT) strcpy(keysToInclude, DEFAULT_KEYBOARD_NOT);
	else if (fullKeyboard == K_TRIM) strcpy(keysToInclude, DEFAULT_KEYBOARD_TRIM);
	else if (fullKeyboard == K_GIGI) strcpy(keysToInclude, DEFAULT_KEYBOARD_GIGI);
	else if (fullKeyboard == K_MINI) strcpy(keysToInclude, DEFAULT_KEYBOARD_MINI);
	else if (fullKeyboard == K_ADD) strcpy(keysToInclude, DEFAULT_KEYBOARD_ADD);
	else if (fullKeyboard == K_BADHD) strcpy(keysToInclude, DEFAULT_KEYBOARD_BADHD);
	else if (fullKeyboard == K_GIBO) strcpy(keysToInclude, DEFAULT_KEYBOARD_GIBO);
	else if (fullKeyboard == K_HOCUS) strcpy(keysToInclude, DEFAULT_KEYBOARD_HOCUS);
	else if (fullKeyboard == K_HOMU) strcpy(keysToInclude, DEFAULT_KEYBOARD_HOMU);
	else if (fullKeyboard == K_GODOT) strcpy(keysToInclude, DEFAULT_KEYBOARD_GODOT);
	else if (fullKeyboard == K_GEORGI) strcpy(keysToInclude, DEFAULT_KEYBOARD_GEORGI);
	else if (fullKeyboard == K_SNOTDOG) strcpy(keysToInclude, DEFAULT_KEYBOARD_SNOTDOG);
	else if (fullKeyboard == K_RUNNER) strcpy(keysToInclude, DEFAULT_KEYBOARD_RUNNER);
	else if (fullKeyboard == K_LAPTOP) strcpy(keysToInclude, DEFAULT_KEYBOARD_LAPTOP);
	else if (fullKeyboard == K_TWENTYSEVEN) strcpy(keysToInclude, DEFAULT_KEYBOARD_TWENTYSEVEN);
	else if (fullKeyboard == K_ELEVEN) strcpy(keysToInclude, DEFAULT_KEYBOARD_ELEVEN);
	else if (fullKeyboard == K_EIGHTEEN) strcpy(keysToInclude, DEFAULT_KEYBOARD_EIGHTEEN);
	else if (fullKeyboard == K_NINETEEN) strcpy(keysToInclude, DEFAULT_KEYBOARD_NINETEEN);
	initKeyboardData();
	initTypingData();
	
	return 0;
} // int initData();

void initKeyboardData()
{
	int i;
	
	if (fullKeyboard == K_NO) {
		static int fingerCopy[KSIZE_MAX] = {
			PINKY, RING, MIDDLE, INDEX, INDEX, INDEX, INDEX, MIDDLE, RING, PINKY, 
			PINKY, RING, MIDDLE, INDEX, INDEX, INDEX, INDEX, MIDDLE, RING, PINKY, 
			PINKY, RING, MIDDLE, INDEX, INDEX, INDEX, INDEX, MIDDLE, RING, PINKY, 
		};
		copyArray(finger, fingerCopy, ksize);
		
		static int columnCopy[KSIZE_MAX] = {
			0, 1, 2, 3, 4, 4, 3, 2, 1, 0, 
			0, 1, 2, 3, 4, 4, 3, 2, 1, 0, 
			0, 1, 2, 3, 4, 4, 3, 2, 1, 0, 
		};
		copyArray(column, columnCopy, ksize);
		
		static int rowCopy[] = {
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
			2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 
		};
		copyArray(row, rowCopy, ksize);
		
		homeRow = 1;
		
		static int handCopy[KSIZE_MAX] = {
			LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
		};
		copyArray(hand, handCopy, ksize);
		
		static int isCenterCopy[KSIZE_MAX] = {
			FALSE, FALSE, FALSE,  FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, 
			FALSE, FALSE, FALSE,  FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, 
			FALSE, FALSE, FALSE,  FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, 
		};
		copyArray(isCenter, isCenterCopy, ksize);
		
		for (i = 0; i < KSIZE_MAX; ++i)
			isOutside[i] = FALSE;
		
		static int printableCopy[KSIZE_MAX] = {
			TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, 
			TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, 
			TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, 
		};
		copyArray(printable, printableCopy, ksize);
    }	else if (fullKeyboard == K_NOT) {
		static int fingerCopy[KSIZE_MAX] = {
			PINKY, RING, MIDDLE, INDEX, INDEX, THUMB, THUMB, INDEX, INDEX, MIDDLE, RING, PINKY, 
			PINKY, RING, MIDDLE, INDEX, INDEX, THUMB, THUMB, INDEX, INDEX, MIDDLE, RING, PINKY, 
			PINKY, RING, MIDDLE, INDEX, INDEX, THUMB, THUMB, INDEX, INDEX, MIDDLE, RING, PINKY, 
		};
		copyArray(finger, fingerCopy, ksize);
		
		static int columnCopy[KSIZE_MAX] = {
			0, 1, 2, 3, 4, 5, 5, 4, 3, 2, 1, 0, 
			0, 1, 2, 3, 4, 5, 5, 4, 3, 2, 1, 0, 
			0, 1, 2, 3, 4, 5, 5, 4, 3, 2, 1, 0, 
		};
		copyArray(column, columnCopy, ksize);
		
		static int rowCopy[] = {
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
			2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 
		};
		copyArray(row, rowCopy, ksize);
		
		homeRow = 1;
		
		static int alphaCopy[] = {
			0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0,
			0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0,
			0, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0,
//			1, 1, 1, 1, 2, 0, 1, 2, 1, 1, 1, 1,
//			0, 0, 0, 0, 2, 1, 1, 2, 0, 0, 0, 0,
		};
		copyArray(isAlpha, alphaCopy, ksize);

		static int handCopy[KSIZE_MAX] = {
			 LEFT,  LEFT,  LEFT,  LEFT,  LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			 LEFT,  LEFT,  LEFT,  LEFT,  LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			 LEFT,  LEFT,  LEFT,  LEFT,  LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
		};
		copyArray(hand, handCopy, ksize);
		
		
		for (i = 0; i < KSIZE_MAX; ++i) {
  			isOutside[i] = FALSE;
	  		isCenter[i] = (i % 12 == 4 || i % 12 == 7)?TRUE:FALSE;
//		  	isAlpha[i] = (i>9)?(i>19)?2:1:1;
        		  printable[i] = ((i % 12 == 5 || i % 12 == 6) && (i < 18))?FALSE:TRUE;
			}
		
    } else if (fullKeyboard == K_LAPTOP) {
		static int fingerCopy[KSIZE_MAX] = {
     PINKY,  PINKY,   RING, MIDDLE,  INDEX,  INDEX,  INDEX,  INDEX,  INDEX, MIDDLE,   RING,  PINKY,  PINKY,  PINKY,
	 PINKY,    PINKY,   RING, MIDDLE,  INDEX,  INDEX,  INDEX,  INDEX,  INDEX, MIDDLE,   RING,  PINKY,        PINKY,        
	 PINKY,       RING, MIDDLE,  INDEX,  INDEX,  INDEX,  INDEX,  INDEX,  INDEX, MIDDLE,   RING,              PINKY,             
};
		copyArray(finger, fingerCopy, ksize);
		
		static int columnCopy[KSIZE_MAX] = {
	     -1, 0, 1, 2, 3, 4, 5, 4, 3, 2, 1, 0, -1, -2, 
	 	 -1,  0, 1, 2, 3, 4, 5, 4, 3, 2, 1, 0,    -1,    
	      0,    1, 2, 3, 4, 5, 5, 4, 3, 2, 1,      0,     
		};
		copyArray(column, columnCopy, ksize);
		
		static int rowCopy[] = {
		 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 		 1,  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,   1,
	     2,    2, 2, 2, 2, 2, 2, 2, 2, 2, 2,    2, 
		};
		copyArray(row, rowCopy, ksize);
		
		homeRow = 1;
		
		static int handCopy[KSIZE_MAX] = {
      LEFT,  LEFT,  LEFT,  LEFT,  LEFT,  LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT,  
      LEFT,    LEFT,  LEFT,  LEFT,  LEFT,  LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT,      RIGHT,
      LEFT,      LEFT,  LEFT,  LEFT,  LEFT,  LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT,           RIGHT,
		};
		copyArray(hand, handCopy, ksize);
		
		static int isCenterCopy[KSIZE_MAX] = {
	 FALSE, FALSE, FALSE, FALSE, FALSE,  TRUE,  TRUE,  TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, 
	 FALSE,   FALSE, FALSE, FALSE, FALSE,  TRUE,  TRUE,  TRUE, FALSE, FALSE, FALSE, FALSE,      FALSE, 
	 FALSE,     FALSE, FALSE, FALSE,  TRUE,  TRUE,  TRUE,  TRUE, FALSE, FALSE, FALSE,           FALSE, 
		};
		copyArray(isCenter, isCenterCopy, ksize);
		
		static int isOutsideCopy[KSIZE_MAX] = {
	  TRUE, FALSE, FALSE, FALSE,  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE,  TRUE,
	  TRUE,   FALSE, FALSE, FALSE,  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,      TRUE,
     FALSE,     FALSE, FALSE,  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,           FALSE,
		};
		copyArray(isOutside, isOutsideCopy, ksize);
		
		static int printableCopy[KSIZE_MAX] = {
	  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,
	  TRUE,    TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,       TRUE,
	  TRUE,      TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,            TRUE, 
		};
		copyArray(printable, printableCopy, ksize);
		
				
		for (i = 0; i < KSIZE_MAX; ++i) {
			isAlpha[i] = TRUE;
		}

	} else if (fullKeyboard == K_STANDARD) {
		static int fingerCopy[KSIZE_MAX] = {
			PINKY, PINKY, RING,  MIDDLE, INDEX, INDEX, INDEX, INDEX, MIDDLE, RING,  PINKY, PINKY, PINKY, PINKY, 
			PINKY, PINKY, RING,  MIDDLE, INDEX, INDEX, INDEX, INDEX, MIDDLE, RING,  PINKY, PINKY, PINKY, PINKY, 
			PINKY, PINKY, RING,  MIDDLE, INDEX, INDEX, INDEX, INDEX, MIDDLE, RING,  PINKY, PINKY, PINKY, PINKY, 
			PINKY, PINKY, RING,  MIDDLE, INDEX, INDEX, INDEX, INDEX, MIDDLE, RING,  PINKY, PINKY, PINKY, PINKY, 
			THUMB, THUMB, THUMB, THUMB,  THUMB, THUMB, THUMB, THUMB, THUMB,  THUMB, THUMB, THUMB, THUMB, THUMB, 
		};
		copyArray(finger, fingerCopy, ksize);
		
		static int columnCopy[KSIZE_MAX] = {
			-1, 0, 1, 2, 3, 4, 4, 3, 2, 1, 0, -1, -2, -3, 
			-1, 0, 1, 2, 3, 4, 4, 3, 2, 1, 0, -1, -2, -3, 
			-1, 0, 1, 2, 3, 4, 4, 3, 2, 1, 0, -1, -2, -3, 
			-1, 0, 1, 2, 3, 4, 4, 3, 2, 1, 0, -1, -2, -3, 
			-1, 0, 1, 2, 3, 4, 4, 3, 2, 1, 0, -1, -2, -3, 
		};
		copyArray(column, columnCopy, ksize);
		
		static int rowCopy[] = {
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
			2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 
			3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
			4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, /* thumb row */
		};
		copyArray(row, rowCopy, ksize);
		
		homeRow = 2;
		
		static int handCopy[KSIZE_MAX] = {
			LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
		};
		copyArray(hand, handCopy, ksize);
		
		static int isCenterCopy[KSIZE_MAX] = {
			FALSE, FALSE, FALSE, FALSE,  FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, 
			FALSE, FALSE, FALSE, FALSE,  FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, 
			FALSE, FALSE, FALSE, FALSE,  FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, 
			FALSE, FALSE, FALSE, FALSE,  FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, 
			FALSE, FALSE, FALSE, FALSE,  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, 
		};
		copyArray(isCenter, isCenterCopy, ksize);
		
		static int isOutsideCopy[KSIZE_MAX] = {
			TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE, 
			TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE, 
			TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE, 
			TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE, 
			FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, 
		};
		copyArray(isOutside, isOutsideCopy, ksize);
		
		static int printableCopy[KSIZE_MAX] = {
			TRUE,  TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE,  TRUE, FALSE, 
			FALSE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE,  TRUE, TRUE,  
			FALSE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE,  FALSE, FALSE, 
			FALSE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, FALSE, FALSE, FALSE, 
			TRUE,  FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE,FALSE, FALSE, FALSE,
		};
		copyArray(printable, printableCopy, ksize);
		
	} else if (fullKeyboard == K_NOKI) {
		static int fingerCopy[KSIZE_MAX] = {
			PINKY, PINKY, RING, MIDDLE, INDEX, INDEX, INDEX, INDEX, MIDDLE, RING, PINKY, PINKY, 
			PINKY, PINKY, RING, MIDDLE, INDEX, INDEX, INDEX, INDEX, MIDDLE, RING, PINKY, PINKY, 
			PINKY, PINKY, RING, MIDDLE, INDEX, INDEX, INDEX, INDEX, MIDDLE, RING, PINKY, PINKY, 
			PINKY, PINKY, RING, MIDDLE, INDEX, INDEX, INDEX, INDEX, MIDDLE, RING, PINKY, PINKY, 
			THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, 
		};
		copyArray(finger, fingerCopy, ksize);
		
		static int columnCopy[KSIZE_MAX] = {
			-1, 0, 1, 2, 3, 4, 4, 3, 2, 1, 0, -1,
			-1, 0, 1, 2, 3, 4, 4, 3, 2, 1, 0, -1,
			-1, 0, 1, 2, 3, 4, 4, 3, 2, 1, 0, -1,
			-1, 0, 1, 2, 3, 4, 4, 3, 2, 1, 0, -1,
			-1, 0, 1, 2, 3, 4, 4, 3, 2, 1, 0, -1,
		};
		copyArray(column, columnCopy, ksize);
		
		static int rowCopy[KSIZE_MAX] = {
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
			2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 
			3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
			4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
			5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, /* thumb row */
		};
		copyArray(row, rowCopy, ksize);
		
		homeRow = 2;
		
		static int handCopy[KSIZE_MAX] = {
			LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
		};
		copyArray(hand, handCopy, ksize);	
		
		static int isCenterCopy[KSIZE_MAX] = {
			FALSE, FALSE, FALSE, FALSE, FALSE,  TRUE,  TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, 
			FALSE, FALSE, FALSE, FALSE, FALSE,  TRUE,  TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, 
			FALSE, FALSE, FALSE, FALSE, FALSE,  TRUE,  TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, 
			FALSE, FALSE, FALSE, FALSE, FALSE,  TRUE,  TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, 
			FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, 
		};
		copyArray(isCenter, isCenterCopy, ksize);
		
		static int isOutsideCopy[KSIZE_MAX] = {
			TRUE,  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, 
			TRUE,  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, 
			TRUE,  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, 
			TRUE,  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, 
			FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, 
		};
		copyArray(isOutside, isOutsideCopy, ksize);

		static int printableCopy[KSIZE_MAX] = {
		 FALSE,  TRUE,  TRUE,  TRUE,  TRUE, FALSE, FALSE,  TRUE,  TRUE,  TRUE,  TRUE,  FALSE,  
		 FALSE,  TRUE,  TRUE,  TRUE,  TRUE, FALSE, FALSE,  TRUE,  TRUE,  TRUE,  TRUE,  FALSE,  
		 FALSE, FALSE,  TRUE,  TRUE,  TRUE, FALSE, FALSE,  TRUE,  TRUE,  TRUE, FALSE,  FALSE,  
		 FALSE, FALSE, FALSE,  TRUE, FALSE, FALSE, FALSE, FALSE, FALSE,  TRUE, FALSE,  FALSE,
		 FALSE, FALSE, FALSE, FALSE,  TRUE,  TRUE,  TRUE,  TRUE, FALSE, FALSE, FALSE,  FALSE,
		};
		copyArray(printable, printableCopy, ksize);		
	} else if (fullKeyboard == K_KINESIS) {
		static int fingerCopy[KSIZE_MAX] = {
			PINKY, PINKY, RING, MIDDLE, INDEX, INDEX, INDEX, INDEX, MIDDLE, RING, PINKY, PINKY, 
			PINKY, PINKY, RING, MIDDLE, INDEX, INDEX, INDEX, INDEX, MIDDLE, RING, PINKY, PINKY, 
			PINKY, PINKY, RING, MIDDLE, INDEX, INDEX, INDEX, INDEX, MIDDLE, RING, PINKY, PINKY, 
			PINKY, PINKY, RING, MIDDLE, INDEX, INDEX, INDEX, INDEX, MIDDLE, RING, PINKY, PINKY, 
			PINKY, PINKY, RING, MIDDLE, INDEX, INDEX, INDEX, INDEX, MIDDLE, RING, PINKY, PINKY, 
			THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, 
		};
		copyArray(finger, fingerCopy, ksize);
		
		static int columnCopy[KSIZE_MAX] = {
			-1, 0, 1, 2, 3, 4, 4, 3, 2, 1, 0, -1,
			-1, 0, 1, 2, 3, 4, 4, 3, 2, 1, 0, -1,
			-1, 0, 1, 2, 3, 4, 4, 3, 2, 1, 0, -1,
			-1, 0, 1, 2, 3, 4, 4, 3, 2, 1, 0, -1,
			-1, 0, 1, 2, 3, 4, 4, 3, 2, 1, 0, -1,
			-1, 0, 1, 2, 3, 4, 4, 3, 2, 1, 0, -1,
		};
		copyArray(column, columnCopy, ksize);
		
		static int rowCopy[KSIZE_MAX] = {
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
			2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 
			3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
			4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
			5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, /* thumb row */
		};
		copyArray(row, rowCopy, ksize);
		
		homeRow = 2;
		
		static int handCopy[KSIZE_MAX] = {
			LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
		};
		copyArray(hand, handCopy, ksize);	
		
		static int isCenterCopy[KSIZE_MAX] = {
			FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, 
			FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, 
			FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, 
			FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, 
			FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, 
			FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, 
		};
		copyArray(isCenter, isCenterCopy, ksize);
		
		static int isOutsideCopy[KSIZE_MAX] = {
			TRUE,  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, 
			TRUE,  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, 
			TRUE,  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, 
			TRUE,  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, 
			TRUE,  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, 
			FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, 
		};
		copyArray(isOutside, isOutsideCopy, ksize);

		static int printableCopy[KSIZE_MAX] = {
			FALSE, TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  
			TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  
			FALSE, TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  
			FALSE, TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  FALSE, 
			FALSE, TRUE,  TRUE,  FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE,  TRUE,  FALSE, 
			FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE,  TRUE,  
		};
		copyArray(printable, printableCopy, ksize);		

	} else if (fullKeyboard == K_IPHONE) {
		static int fingerCopy[KSIZE_MAX] = {
			THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, 
			THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, 
			THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, THUMB, 
		};
		copyArray(finger, fingerCopy, ksize);
		
		static int rowCopy[] = {
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		};
		copyArray(row, rowCopy, ksize);
		
		homeRow = 1;
		
		static int handCopy[KSIZE_MAX] = {
			LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
		};
		copyArray(hand, handCopy, ksize);
		
		static int isCenterCopy[KSIZE_MAX] = {
			FALSE, FALSE, FALSE,  FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, 
			FALSE, FALSE, FALSE,  FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, 
			FALSE, FALSE, FALSE,  FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, 
		};
		copyArray(isCenter, isCenterCopy, ksize);
		
		for (i = 0; i < KSIZE_MAX; ++i)
			isOutside[i] = FALSE;
		
		static int printableCopy[KSIZE_MAX] = {
			TRUE,  TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE,  TRUE,  
			TRUE,  TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE,  FALSE, 
			FALSE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, FALSE, FALSE, 
		};
		copyArray(printable, printableCopy, ksize);
	} else if (fullKeyboard == K_TRIM) {
		static int fingerCopy[KSIZE_MAX] = {
			PINKY, RING, MIDDLE, INDEX,        INDEX, INDEX, MIDDLE, RING, PINKY, PINKY, 
			PINKY, RING, MIDDLE, INDEX, INDEX, INDEX, INDEX, MIDDLE, RING, PINKY, PINKY,
			                                   INDEX, INDEX, MIDDLE, RING, PINKY
		};
		copyArray(finger, fingerCopy, ksize);
		
		static int columnCopy[KSIZE_MAX] = {
			0, 1, 2, 3,    4, 3, 2, 1, 0, -1,
			0, 1, 2, 3, 4, 4, 3, 2, 1, 0, -1,
			               4, 3, 2, 1, 0
		};
		copyArray(column, columnCopy, ksize);
		
		static int rowCopy[] = {
			0, 0, 0, 0,    0, 0, 0, 0, 0, 0, 
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
			               2, 2, 2, 2, 2 
		};
		copyArray(row, rowCopy, ksize);
		
		homeRow = 1;
		
		static int handCopy[KSIZE_MAX] = {
			LEFT, LEFT, LEFT, LEFT,       RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT,
			                              RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
		};
		copyArray(hand, handCopy, ksize);
		
		static int isCenterCopy[KSIZE_MAX] = {
			FALSE, FALSE, FALSE,  FALSE,       TRUE, FALSE, FALSE, FALSE, FALSE, FALSE,  
			FALSE, FALSE, FALSE,  FALSE, TRUE, TRUE, FALSE, FALSE, FALSE, FALSE, FALSE,
			                                   TRUE, FALSE, FALSE, FALSE, FALSE 
		};
		copyArray(isCenter, isCenterCopy, ksize);
		
		static int isOutsideCopy[KSIZE_MAX] = {
			FALSE, FALSE, FALSE, FALSE,        FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, 
			FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, 
			                                   FALSE, FALSE, FALSE, FALSE, FALSE 
		};
		copyArray(isOutside, isOutsideCopy, ksize);		

		static int printableCopy[KSIZE_MAX] = {
			TRUE, TRUE, TRUE, TRUE,       TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, 
			TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, 
			                              TRUE, TRUE, TRUE, TRUE, TRUE, 
		};
		copyArray(printable, printableCopy, ksize);
	} else if (fullKeyboard == K_GIGI) {
	
	
		static int fingerCopy[KSIZE_MAX] = {
			PINKY, RING, MIDDLE, INDEX, INDEX, THUMB,     THUMB, INDEX, INDEX, MIDDLE, RING, PINKY,
			PINKY, RING, MIDDLE, INDEX, INDEX, THUMB,     THUMB, INDEX, INDEX, MIDDLE, RING, PINKY,
		  PINKY, RING, MIDDLE, INDEX, INDEX, THUMB,     THUMB, INDEX, INDEX, MIDDLE, RING, PINKY,
					};
		copyArray(finger, fingerCopy, ksize);
		
		static int columnCopy[KSIZE_MAX] = {
			0, 1, 2, 3, 4, 5,  5, 4, 3, 2, 1, 0,
			0, 1, 2, 3, 4, 5,  5, 4, 3, 2, 1, 0,
			0, 1, 2, 3, 4, 5,  5, 4, 3, 2, 1, 0,
		};
		copyArray(column, columnCopy, ksize);
		 
		static int rowCopy[] = {
			0, 0, 0, 0, 0, 0,     0, 0, 0, 0, 0, 0,
			1, 1, 1, 1, 1, 1,     1, 1, 1, 1, 1, 1,
			2, 2, 2, 2, 2, 2,     2, 2, 2, 2, 2, 2,
		};
		copyArray(row, rowCopy, ksize);
		
		homeRow = 1;
		
		static int handCopy[KSIZE_MAX] = {
			LEFT, LEFT, LEFT, LEFT, LEFT, LEFT,     RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT, LEFT,     RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 			
			LEFT, LEFT, LEFT, LEFT, LEFT, LEFT,     RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 		};
		copyArray(hand, handCopy, ksize);
		
		static int isCenterCopy[KSIZE_MAX] = {
			FALSE, FALSE, FALSE, FALSE, TRUE, FALSE,     FALSE, TRUE, FALSE, FALSE, FALSE, FALSE,  
			FALSE, FALSE, FALSE, FALSE, TRUE, FALSE,     FALSE, TRUE, FALSE, FALSE, FALSE, FALSE,
			FALSE, FALSE, FALSE, FALSE, TRUE, FALSE,     FALSE, TRUE, FALSE, FALSE, FALSE, FALSE,
		};
		copyArray(isCenter, isCenterCopy, ksize);
		
		static int isOutsideCopy[KSIZE_MAX] = {
			FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
			FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
			FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,     FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
		};
		copyArray(isOutside, isOutsideCopy, ksize);		

		static int printableCopy[KSIZE_MAX] = {
		  TRUE,  TRUE,  TRUE,  TRUE,  TRUE, FALSE,    FALSE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE, 
		  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,     TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,
		 FALSE,  TRUE,  TRUE, FALSE, FALSE, FALSE,     TRUE, FALSE, FALSE,  TRUE,  TRUE, FALSE,
		};
		copyArray(printable, printableCopy, ksize);
	} else if (fullKeyboard == K_MINI) {
		static int fingerCopy[KSIZE_MAX] = {
			PINKY, RING, MIDDLE, INDEX, INDEX,          INDEX, INDEX, MIDDLE, RING, PINKY,
			PINKY, RING, MIDDLE, INDEX, INDEX,          INDEX, INDEX, MIDDLE, RING, PINKY,
			PINKY, RING, MIDDLE, INDEX, INDEX,          INDEX, INDEX, MIDDLE, RING, PINKY,
			              		THUMB, THUMB, THUMB, THUMB, THUMB,  THUMB,
		};
		copyArray(finger, fingerCopy, ksize);
		
		static int columnCopy[KSIZE_MAX] = {
			0, 1, 2, 3, 4,             		 4, 3, 2, 1, 0,
			0, 1, 2, 3, 4,             		 4, 3, 2, 1, 0,
			0, 1, 2, 3, 4,     		   	  	 4, 3, 2, 1, 0,
			               5, 6, 7, 7, 6, 5, 
		};
		copyArray(column, columnCopy, ksize);
		 
		static int rowCopy[] = {
			0, 0, 0, 0, 0,     0, 0, 0, 0, 0, 
			1, 1, 1, 1, 1,     1, 1, 1, 1, 1, 
			2, 2, 2, 2, 2,     2, 2, 2, 2, 2,
			 		    3, 3, 3, 3, 3, 3,
		};
		copyArray(row, rowCopy, ksize);
		
		homeRow = 1;
		
		static int isAlphaCopy[] = {
			0, 0, 0, 0, 1,     1, 0, 0, 0, 0, 
			0, 0, 0, 0, 1,     1, 0, 0, 0, 0, 
			0, 0, 0, 0, 1,     1, 0, 0, 0, 0,
			 	     	3, 3, 3, 3, 3, 0,
		};
		copyArray(isAlpha, isAlphaCopy, ksize);

		static int handCopy[KSIZE_MAX] = {
			LEFT, LEFT, LEFT, LEFT, LEFT,       RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT,       RIGHT, RIGHT, RIGHT, RIGHT, RIGHT,
			LEFT, LEFT, LEFT, LEFT, LEFT,       RIGHT, RIGHT, RIGHT, RIGHT, RIGHT,
			                LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT,              
		};
		copyArray(hand, handCopy, ksize);
		
		static int isCenterCopy[KSIZE_MAX] = {
			FALSE, FALSE, FALSE,  FALSE, TRUE,      TRUE, FALSE, FALSE, FALSE, FALSE,  
			FALSE, FALSE, FALSE,  FALSE, TRUE,      TRUE, FALSE, FALSE, FALSE, FALSE,  
			FALSE, FALSE, FALSE,  FALSE, TRUE,      TRUE, FALSE, FALSE, FALSE, FALSE,
			                 FALSE, FALSE, TRUE, TRUE, FALSE, FALSE, 
		};
		copyArray(isCenter, isCenterCopy, ksize);
		
		static int isOutsideCopy[KSIZE_MAX] = {
			FALSE, FALSE, FALSE, FALSE, FALSE,      FALSE, FALSE, FALSE, FALSE, FALSE,
			FALSE, FALSE, FALSE, FALSE, FALSE,      FALSE, FALSE, FALSE, FALSE, FALSE,
			FALSE, FALSE, FALSE, FALSE, FALSE,      FALSE, FALSE, FALSE, FALSE, FALSE,
			                 FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
		};
		copyArray(isOutside, isOutsideCopy, ksize);		

		static int printableCopy[KSIZE_MAX] = {
			TRUE, TRUE, TRUE, TRUE, TRUE,         TRUE, TRUE, TRUE, TRUE, TRUE, 
			TRUE, TRUE, TRUE, TRUE, TRUE,         TRUE, TRUE, TRUE, TRUE, TRUE,
		 FALSE, TRUE, TRUE, TRUE, TRUE,         TRUE, TRUE, TRUE, TRUE, FALSE,
			                TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, 
		};
		copyArray(printable, printableCopy, ksize);
	} else if (fullKeyboard == K_ADD) {
		static int fingerCopy[KSIZE_MAX] = {
			PINKY, RING, MIDDLE, INDEX, INDEX, MIDDLE, RING, PINKY,
			PINKY, RING, MIDDLE, INDEX, INDEX, MIDDLE, RING, PINKY,
			PINKY, RING, MIDDLE, INDEX, INDEX, MIDDLE, RING, PINKY,
		};
		copyArray(finger, fingerCopy, ksize);
		
		static int columnCopy[KSIZE_MAX] = {
			0, 1, 2, 3,      3, 2, 1, 0,
			0, 1, 2, 3,      3, 2, 1, 0,
			0, 1, 2, 3,      3, 2, 1, 0,
		};
		copyArray(column, columnCopy, ksize);
		 
		static int rowCopy[] = {
			0, 0, 0, 0,     0, 0, 0, 0, 
			1, 1, 1, 1,     1, 1, 1, 1, 
			2, 2, 2, 2,     2, 2, 2, 2,
		};
		copyArray(row, rowCopy, ksize);
		
		homeRow = 1;
		
		static int isAlphaCopy[] = {
			1, 1, 1, 1,     1, 1, 1, 1, 
			0, 0, 0, 0,     0, 0, 0, 0, 
			1, 1, 1, 1,     1, 1, 1, 1, 
//			2, 2, 2, 2,     2, 2, 2, 2, 
		};
		copyArray(isAlpha, isAlphaCopy, ksize);
		
		static int handCopy[KSIZE_MAX] = {
			LEFT, LEFT, LEFT, LEFT,       RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT,       RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT,       RIGHT, RIGHT, RIGHT, RIGHT, 
		};
		copyArray(hand, handCopy, ksize);
		
	    	static int printableCopy[KSIZE_MAX] = {
	    		TRUE,  TRUE,  TRUE,  TRUE,         TRUE,  TRUE,  TRUE,  TRUE, 
	    		TRUE,  TRUE,  TRUE,  TRUE,         TRUE,  TRUE,  TRUE,  TRUE,
	    		TRUE,  TRUE,  TRUE,  TRUE,         TRUE,  TRUE,  TRUE,  TRUE, 
		};
		copyArray(printable, printableCopy, ksize);	

		for (i = 0; i < KSIZE_MAX; ++i) {
			isOutside[i] = FALSE;
			isCenter[i]  = FALSE;
			//printable[i] = TRUE;
        }

	} else if (fullKeyboard == K_BADHD) {
		static int fingerCopy[KSIZE_MAX] = {
			PINKY,  RING, MIDDLE, INDEX,       INDEX, MIDDLE,  RING, PINKY,
			PINKY,  RING, MIDDLE, INDEX,       INDEX, MIDDLE,  RING, PINKY,
			PINKY,  RING, MIDDLE, INDEX,       INDEX, MIDDLE,  RING, PINKY,
                       THUMB, THUMB,  THUMB, THUMB,       THUMB,  THUMB, THUMB, THUMB, 
		};
		copyArray(finger, fingerCopy, ksize);
		
		static int columnCopy[KSIZE_MAX] = {
			0, 1, 2, 3,     3, 2, 1, 0,
			0, 1, 2, 3,     3, 2, 1, 0,
			0, 1, 2, 3,     3, 2, 1, 0,
                       0, 1, 2, 3,     3, 2, 1, 0, 
		};
		copyArray(column, columnCopy, ksize);
		
		static int rowCopy[KSIZE_MAX] = {
			0, 0, 0, 0,     0, 0, 0, 0,
			1, 1, 1, 1,     1, 1, 1, 1,
			2, 2, 2, 2,     2, 2, 2, 2,
			3, 3, 3, 3,     3, 3, 3, 3,
		};
		copyArray(row, rowCopy, ksize);

		homeRow = 1;
		
		static int alphaCopy[KSIZE_MAX] = {
			0, 0, 0, 0,     0, 0, 0, 0,
			1, 1, 1, 1,     1, 1, 1, 1,
			2, 2, 2, 2,     2, 2, 2, 2,
			0, 0, 1, 1,     1, 1, 0, 0,
		};
		copyArray(isAlpha, alphaCopy, ksize);

		static int handCopy[KSIZE_MAX] = {
			LEFT, LEFT, LEFT, LEFT,       RIGHT, RIGHT, RIGHT, RIGHT,
			LEFT, LEFT, LEFT, LEFT,       RIGHT, RIGHT, RIGHT, RIGHT,
			LEFT, LEFT, LEFT, LEFT,       RIGHT, RIGHT, RIGHT, RIGHT,
			LEFT, LEFT, LEFT, LEFT,       RIGHT, RIGHT, RIGHT, RIGHT,
		};
		copyArray(hand, handCopy, ksize);
		
		static int printableCopy[KSIZE_MAX] = {
			1, 1, 1, 1,     1, 1, 1, 1,
			1, 1, 1, 1,     1, 1, 1, 1,
			1, 1, 1, 1,     1, 1, 1, 1,
			0, 0, 1, 1,     1, 1, 0, 0,
		};
		copyArray(printable, printableCopy, ksize);

		for (i = 0; i < KSIZE_MAX; ++i) {
			isOutside[i] = FALSE;
			isCenter[i]  = FALSE;
//			printable[i] = (i == 16 || i == 17 || i == 22 || i == 23)?FALSE:TRUE;
			}
	} else if (fullKeyboard == K_GIBO) {

		static int fingerCopy[KSIZE_MAX] = {
			PINKY, RING, MIDDLE, INDEX, THUMB, THUMB, INDEX, MIDDLE, RING, PINKY,
			PINKY, RING, MIDDLE, INDEX, THUMB, THUMB, INDEX, MIDDLE, RING, PINKY,
			PINKY, RING, MIDDLE, INDEX, THUMB, THUMB, INDEX, MIDDLE, RING, PINKY,
			PINKY, RING, MIDDLE, INDEX, THUMB, THUMB, INDEX, MIDDLE, RING, PINKY,
			PINKY, RING, MIDDLE, INDEX, THUMB, THUMB, INDEX, MIDDLE, RING, PINKY,
			PINKY, RING, MIDDLE, INDEX, THUMB, THUMB, INDEX, MIDDLE, RING, PINKY,
		};
		copyArray(finger, fingerCopy, ksize);
		
		static int columnCopy[KSIZE_MAX] = {
			0, 1, 2, 3, 4, 4, 3, 2, 1, 0,
			0, 1, 2, 3, 4, 4, 3, 2, 1, 0,
			0, 1, 2, 3, 4, 4, 3, 2, 1, 0,
			0, 1, 2, 3, 4, 4, 3, 2, 1, 0,
			0, 1, 2, 3, 4, 4, 3, 2, 1, 0,
			0, 1, 2, 3, 4, 4, 3, 2, 1, 0,
		};
		copyArray(column, columnCopy, ksize);
		 
		static int rowCopy[] = {
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
		};
		copyArray(row, rowCopy, ksize);
		
		homeRow = 1;
		
		static int handCopy[KSIZE_MAX] = {
			LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
		};
		copyArray(hand, handCopy, ksize);
		
		static int isAlphaCopy[KSIZE_MAX] = {
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
			2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 
			2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 
			3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
			3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 

//			4, 4, 4, 4, 4, 1, 1, 1, 1, 1, 
//			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
//			2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 
//			2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 
//			3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
		};
		copyArray(isAlpha, isAlphaCopy, ksize);
           
		for (i = 0; i < KSIZE_MAX; ++i) {
			isOutside[i] = FALSE;
			isCenter[i]  = FALSE;
			printable[i] = (i < 20 || (i < 40 && i % 10 > 5)) ?TRUE:FALSE;
        }
        
/*    static int printableCopy[KSIZE_MAX] = {
		    TRUE,  TRUE,  TRUE,  TRUE, 			TRUE, TRUE,  TRUE,  TRUE, 
 			  TRUE,  TRUE,  TRUE,  TRUE, 			TRUE, TRUE,  TRUE,  TRUE, 
		    TRUE,  TRUE, FALSE,  TRUE, 			TRUE, TRUE,  TRUE,  TRUE, 
 			  TRUE,  TRUE, FALSE,  TRUE, 			TRUE, TRUE,  TRUE,  TRUE, 
		   FALSE, FALSE,  TRUE, FALSE, 		  TRUE, TRUE, FALSE, FALSE, 
		};
		copyArray(printable, printableCopy, ksize);
*/
	} else if (fullKeyboard == K_HOCUS) {
		static int fingerCopy[KSIZE_MAX] = {
			PINKY, RING, MIDDLE, INDEX, INDEX,  INDEX, INDEX, MIDDLE, RING, PINKY,
			PINKY, RING, MIDDLE, INDEX, INDEX,  INDEX, INDEX, MIDDLE, RING, PINKY,
			PINKY, RING, MIDDLE, INDEX, INDEX,  INDEX, INDEX, MIDDLE, RING, PINKY,
			PINKY, RING, MIDDLE, INDEX, INDEX,  INDEX, INDEX, MIDDLE, RING, PINKY,
			THUMB, THUMB, THUMB, THUMB, THUMB,  THUMB, THUMB, THUMB, THUMB, THUMB, 
		};
		copyArray(finger, fingerCopy, ksize);
		
		static int columnCopy[KSIZE_MAX] = {
			0, 1, 2, 3, 4, 4, 3, 2, 1, 0,
			0, 1, 2, 3, 4, 4, 3, 2, 1, 0,
			0, 1, 2, 3, 4, 4, 3, 2, 1, 0,
			0, 1, 2, 3, 4, 4, 3, 2, 1, 0,
			0, 1, 2, 3, 4, 4, 3, 2, 1, 0,
		};
		copyArray(column, columnCopy, ksize);
		 
		static int rowCopy[] = {
      2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
      2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
		};
		copyArray(row, rowCopy, ksize);
		
		homeRow = 1;
		
		static int handCopy[KSIZE_MAX] = {
			LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
		};
		copyArray(hand, handCopy, ksize);
		
		static int isAlphaCopy[KSIZE_MAX] = {
//			1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
      2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 
      2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 
      2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 
      2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 
// 			0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 
//			0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 
      2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 
		};
		copyArray(isAlpha, isAlphaCopy, ksize);
           

		static int printableCopy[KSIZE_MAX] = {
             TRUE,  TRUE,  TRUE,  TRUE, FALSE, FALSE,  TRUE,  TRUE,  TRUE,  TRUE,
             TRUE,  TRUE,  TRUE,  TRUE, FALSE, FALSE,  TRUE,  TRUE,  TRUE,  TRUE,
            FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,  TRUE,  TRUE,  TRUE,  TRUE,
            FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,  TRUE,  TRUE,  TRUE,  TRUE,
            FALSE, FALSE, FALSE,  TRUE,  TRUE,  TRUE,  TRUE, FALSE, FALSE, FALSE,
		};
		copyArray(printable, printableCopy, ksize);

		for (i = 0; i < KSIZE_MAX; ++i) {
			isOutside[i] = FALSE;
			isCenter[i]  = FALSE;
//			printable[i] = TRUE;
        }
	} else if (fullKeyboard == K_HOMU) {
		static int fingerCopy[KSIZE_MAX] = {
			PINKY,  RING, MIDDLE, INDEX, INDEX, THUMB, THUMB, INDEX, INDEX, MIDDLE, RING, PINKY,
			PINKY,  RING, MIDDLE, INDEX, INDEX, THUMB, THUMB, INDEX, INDEX, MIDDLE, RING, PINKY,
			PINKY,  RING, MIDDLE, INDEX, INDEX, THUMB, THUMB, INDEX, INDEX, MIDDLE, RING, PINKY,
		};
		copyArray(finger, fingerCopy, ksize);
		
/*		static int columnCopy[KSIZE_MAX] = {
			0, 1, 2, 3, 4, 5, 6, 6, 5, 4, 3, 2, 1, 0, ,
			0, 1, 2, 3, 4, 4, 3, 2, 1, 0,
		  1, 2, 3,       3, 2, 1,
			0, 1, 2, 3,       3, 2, 1, 0,
		};*/
		copyArray(column, fingerCopy, ksize);
		 
		static int rowCopy[] = {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 
      2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 
		};
		copyArray(row, rowCopy, ksize);
		
		homeRow = 1;
		
		static int handCopy[KSIZE_MAX] = {
			LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT,
			LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT,
			LEFT, LEFT, LEFT, LEFT, LEFT, LEFT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT,
		};
		copyArray(hand, handCopy, ksize);
		
		static int isAlphaCopy[KSIZE_MAX] = {
      0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
      1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
      2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 
		};
		copyArray(isAlpha, isAlphaCopy, ksize);
		
		static int printableCopy[KSIZE_MAX] = {
		FALSE,  TRUE,  TRUE,  TRUE,  TRUE, FALSE,     FALSE,  TRUE,  TRUE,  TRUE,  TRUE, FALSE,
		 TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,      TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE, 
         	FALSE, FALSE,  TRUE,  TRUE,  TRUE, FALSE,      TRUE,  TRUE,  TRUE,  TRUE, FALSE, FALSE,
		};
		copyArray(printable, printableCopy, ksize);

           
		for (i = 0; i < KSIZE_MAX; ++i) {
			isOutside[i] = FALSE;
			isCenter[i]  = FALSE;
//			printable[i] = TRUE;
        }
	} else if (fullKeyboard == K_GEORGI) {
		static int fingerCopy[KSIZE_MAX] = {
			PINKY, PINKY,  RING, MIDDLE, INDEX, INDEX,      INDEX, INDEX, MIDDLE,  RING, PINKY, PINKY, 
			PINKY, PINKY,  RING, MIDDLE, INDEX, INDEX,      INDEX, INDEX, MIDDLE,  RING, PINKY, PINKY, 
			THUMB, THUMB, THUMB,  THUMB, THUMB, THUMB,      THUMB, THUMB,  THUMB, THUMB, THUMB, THUMB, 
		};
		copyArray(finger, fingerCopy, ksize);
		
		static int columnCopy[KSIZE_MAX] = {
		  -1, 0, 1, 2, 3, 4,    4, 3, 2, 1, 0, -1,
			-1, 0, 1, 2, 3, 4,    4, 3, 2, 1, 0, -1,
			-1, 0, 1, 2, 3, 4,    4, 3, 2, 1, 0, -1,
		};
		copyArray(column, columnCopy, ksize);
		 
		static int rowCopy[] = {
			0, 0, 0, 0, 0, 0,    0, 0, 0, 0, 0, 0,
 			1, 1, 1, 1, 1, 1,    1, 1, 1, 1, 1, 1,
      2, 2, 2, 2, 2, 2,    2, 2, 2, 2, 2, 2,
		};
		copyArray(row, rowCopy, ksize);
		
		homeRow = 1;
		
		static int isAlphaCopy[] = {
			0, 0, 0, 0, 0, 0,    0, 0, 0, 0, 0, 0,
			0, 1, 1, 1, 1, 0,    0, 1, 1, 1, 1, 0,
			0, 0, 0, 0, 1, 0,    0, 1, 0, 0, 0, 0,
		};
		copyArray(isAlpha, isAlphaCopy, ksize);

		static int handCopy[KSIZE_MAX] = {
			LEFT, LEFT, LEFT, LEFT, LEFT, LEFT,       RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT, LEFT,       RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT,
			LEFT, LEFT, LEFT, LEFT, LEFT, LEFT,       RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT,
		};
		copyArray(hand, handCopy, ksize);
		
		static int isCenterCopy[KSIZE_MAX] = {
			FALSE, FALSE, FALSE, FALSE, FALSE, TRUE,      TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, 
			FALSE, FALSE, FALSE, FALSE, FALSE, TRUE,      TRUE, FALSE, FALSE, FALSE, FALSE, FALSE,
			FALSE, FALSE, FALSE, FALSE, FALSE, TRUE,      TRUE, FALSE, FALSE, FALSE, FALSE, FALSE,
		};
		copyArray(isCenter, isCenterCopy, ksize);

		static int isOutsideCopy[KSIZE_MAX] = {
			TRUE, FALSE, FALSE, FALSE, FALSE, FALSE,      FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, 
			TRUE, FALSE, FALSE, FALSE, FALSE, FALSE,      FALSE, FALSE, FALSE, FALSE, FALSE, TRUE,
			TRUE, FALSE, FALSE, FALSE, FALSE, FALSE,      FALSE, FALSE, FALSE, FALSE, FALSE, TRUE,
		};
		copyArray(isOutside, isOutsideCopy, ksize);

		static int printableCopy[KSIZE_MAX] = {
			TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,      TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,
			TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE,      TRUE,  TRUE,  TRUE,  TRUE,  TRUE,  TRUE, 
	   		FALSE, FALSE, FALSE, FALSE, TRUE, FALSE,      TRUE,  TRUE, FALSE, FALSE, FALSE, FALSE,
		};
		copyArray(printable, printableCopy, ksize);

	} else if (fullKeyboard == K_RUNNER) {
		static int fingerCopy[KSIZE_MAX] = {
			PINKY, RING, MIDDLE, INDEX, INDEX,      INDEX, INDEX, MIDDLE, RING, PINKY,
			PINKY, RING, MIDDLE, INDEX, INDEX,      INDEX, INDEX, MIDDLE, RING, PINKY,
			PINKY, RING, MIDDLE, INDEX, INDEX,      INDEX, INDEX, MIDDLE, RING, PINKY, 
	 PINKY, PINKY, RING, MIDDLE, INDEX, INDEX,      INDEX, INDEX, MIDDLE, RING, PINKY, PINKY, PINKY, PINKY, PINKY, 
		};
		copyArray(finger, fingerCopy, ksize);
		
		static int columnCopy[KSIZE_MAX] = {
		        0, 1, 2, 3, 4,    4, 3, 2, 1, 0,
			    0, 1, 2, 3, 4,    4, 3, 2, 1, 0,
		        0, 1, 2, 3, 4,    4, 3, 2, 1, 0,
			-1, 0, 1, 2, 3, 4,    4, 3, 2, 1, 0, -1, -2, -3, -4
		};
		copyArray(column, columnCopy, ksize);
		 
		static int rowCopy[] = {
			   0, 0, 0, 0, 0,    0, 0, 0, 0, 0,
			   1, 1, 1, 1, 1,    1, 1, 1, 1, 1,
			   2, 2, 2, 2, 2,    2, 2, 2, 2, 2,
			3, 3, 3, 3, 3, 3,    3, 3, 3, 3, 3, 3, 3, 3, 3, 
		};
		copyArray(row, rowCopy, ksize);
		
		
		homeRow = 1;
		
		static int handCopy[KSIZE_MAX] = {
			LEFT, LEFT, LEFT, LEFT, LEFT,             RIGHT, RIGHT, RIGHT, RIGHT, RIGHT,
			LEFT, LEFT, LEFT, LEFT, LEFT,             RIGHT, RIGHT, RIGHT, RIGHT, RIGHT,
			LEFT, LEFT, LEFT, LEFT, LEFT,             RIGHT, RIGHT, RIGHT, RIGHT, RIGHT,
			LEFT, LEFT, LEFT, LEFT, LEFT, LEFT,       RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, RIGHT,
		};
		copyArray(hand, handCopy, ksize);
		
		static int isCenterCopy[KSIZE_MAX] = {
			FALSE, FALSE, FALSE, FALSE, TRUE,      TRUE, FALSE, FALSE, FALSE, FALSE,
			FALSE, FALSE, FALSE, FALSE, TRUE,      TRUE, FALSE, FALSE, FALSE, FALSE,
			FALSE, FALSE, FALSE, FALSE, TRUE,      TRUE, FALSE, FALSE, FALSE, FALSE,
	 FALSE, FALSE, FALSE, FALSE, FALSE, TRUE,      TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,
		};
		copyArray(isCenter, isCenterCopy, ksize);

		static int isOutsideCopy[KSIZE_MAX] = {
			FALSE, FALSE, FALSE, FALSE, FALSE,      FALSE, FALSE, FALSE, FALSE, FALSE, 
			FALSE, FALSE, FALSE, FALSE, FALSE,      FALSE, FALSE, FALSE, FALSE, FALSE, 
			FALSE, FALSE, FALSE, FALSE, FALSE,      FALSE, FALSE, FALSE, FALSE, FALSE, 
	  TRUE, FALSE, FALSE, FALSE, FALSE, FALSE,      FALSE, FALSE, FALSE, FALSE, FALSE, TRUE, TRUE, TRUE, TRUE,
		};
		copyArray(isOutside, isOutsideCopy, ksize);

		static int isAlphaCopy[KSIZE_MAX] = {
			FALSE, FALSE, FALSE, FALSE, FALSE,      FALSE, FALSE, FALSE, FALSE, FALSE, 
			FALSE, FALSE, FALSE, FALSE, FALSE,      FALSE, FALSE, FALSE, FALSE, FALSE, 
			FALSE, FALSE, FALSE, FALSE, FALSE,      FALSE, FALSE, FALSE, FALSE, FALSE, 
	   TRUE, TRUE,  TRUE,  TRUE,  TRUE,  TRUE,       TRUE,  TRUE,  TRUE,  TRUE,  TRUE, TRUE, TRUE, TRUE, TRUE,
		};
		copyArray(isAlpha, isAlphaCopy, ksize);

		for (i = 0; i < KSIZE_MAX; ++i) {
			//isOutside[i] = FALSE;
			//isCenter[i]  = FALSE;
			printable[i] = TRUE;
        }
	} else if (fullKeyboard == K_GODOT) {
		static int fingerCopy[KSIZE_MAX] = {
			PINKY, RING, MIDDLE, INDEX, THUMB,       THUMB, INDEX, MIDDLE, RING, PINKY,
			PINKY, RING, MIDDLE, INDEX, THUMB,       THUMB, INDEX, MIDDLE, RING, PINKY,
			PINKY, RING, MIDDLE, INDEX, THUMB,       THUMB, INDEX, MIDDLE, RING, PINKY,
			PINKY, RING, MIDDLE, INDEX, THUMB,       THUMB, INDEX, MIDDLE, RING, PINKY,
			PINKY, RING, MIDDLE, INDEX, THUMB,       THUMB, INDEX, MIDDLE, RING, PINKY,
			PINKY, RING, MIDDLE, INDEX, THUMB,       THUMB, INDEX, MIDDLE, RING, PINKY,
		};
		copyArray(finger, fingerCopy, ksize);
		
		static int columnCopy[KSIZE_MAX] = {
			0, 1, 2, 3, 4,     4, 3, 2, 1, 0,
			0, 1, 2, 3, 4,     4, 3, 2, 1, 0,
			0, 1, 2, 3, 4,     4, 3, 2, 1, 0,
			0, 1, 2, 3, 4,     4, 3, 2, 1, 0,
			0, 1, 2, 3, 4,     4, 3, 2, 1, 0,
			0, 1, 2, 3, 4,     4, 3, 2, 1, 0,
		};
		copyArray(column, columnCopy, ksize);
		 
		static int rowCopy[] = {
			0, 0, 0, 0, 0,     0, 0, 0, 0, 0, 
			1, 1, 1, 1, 1,     1, 1, 1, 1, 1,
      2, 2, 2, 2, 2,     2, 2, 2, 2, 2,
			0, 0, 0, 0, 0,     0, 0, 0, 0, 0, 
			1, 1, 1, 1, 1,     1, 1, 1, 1, 1,
      2, 2, 2, 2, 2,     2, 2, 2, 2, 2,
		};
		copyArray(row, rowCopy, ksize);
		
		homeRow = 1;
		
		static int handCopy[KSIZE_MAX] = {
			LEFT, LEFT, LEFT, LEFT, LEFT,       RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT,       RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT,       RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT,       RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT,       RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT,       RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
		};
		copyArray(hand, handCopy, ksize);
		
		static int isAlphaCopy[KSIZE_MAX] = {
			1, 1, 1, 1, 1,     1, 1, 1, 1, 1, 
			0, 0, 0, 0, 0,     0, 0, 0, 0, 0, 
			1, 1, 1, 1, 1,     1, 1, 1, 1, 1, 
//			2, 2, 2, 2, 2,		 2, 2, 2, 2, 2, 
//			2, 2, 2, 2, 2,     1, 1, 1, 1, 1, 
			3, 3, 3, 3, 3,		 3, 3, 3, 3, 3, 
			3, 3, 3, 3, 3,		 3, 3, 3, 3, 3, 
			3, 3, 3, 3, 3,		 3, 3, 3, 3, 3, 
 		};
		copyArray(isAlpha, isAlphaCopy, ksize);
		
		static int printableCopy[KSIZE_MAX] = {
			1, 1, 1, 1, 1,     1, 1, 1, 1, 1, 
			1, 1, 1, 1, 1,     1, 1, 1, 1, 1, 
			1, 1, 1, 1, 1,     1, 1, 1, 1, 1, 
      0, 0, 0, 0, 0,     0, 0, 0, 0, 0,
      0, 0, 0, 0, 0,     0, 0, 0, 0, 0,
      0, 0, 0, 0, 0,     0, 0, 0, 0, 0,
		};
		copyArray(printable, printableCopy, ksize);

		for (i = 0; i < KSIZE_MAX; ++i) {
			isOutside[i] = FALSE;
			isCenter[i]  = FALSE;
//			printable[i] = (i%30 == 20 || i%30 == 29 || (i%10==5 && (i != 5 && i != 15)))?FALSE:TRUE;
        }
	} else if (fullKeyboard == K_SNOTDOG) {
		static int fingerCopy[KSIZE_MAX] = {
			PINKY, RING, MIDDLE, INDEX,      INDEX, MIDDLE, RING, PINKY,
			PINKY, RING, MIDDLE, INDEX,      INDEX, MIDDLE, RING, PINKY,
          9,    9,  THUMB, THUMB,      THUMB,  THUMB,    9,     9,
          9,    9,      9,     9,          9,      9,    9,     9,
		};
		copyArray(finger, fingerCopy, ksize);
		
		static int columnCopy[KSIZE_MAX] = {
			0, 1, 2, 3,      3, 2, 1, 0,
			0, 1, 2, 3,      3, 2, 1, 0,
			9, 9, 2, 3,      3, 2, 9, 9,
			9, 9, 9, 9,      9, 9, 9, 9,
		};
		copyArray(column, columnCopy, ksize);
		 
		static int rowCopy[] = {
			0, 0, 0, 0,     0, 0, 0, 0, 
			1, 1, 1, 1,     1, 1, 1, 1, 
			9, 9, 2, 2,     2, 2, 9, 9,
			9, 9, 9, 9,     9, 9, 9, 9, 
		};
		copyArray(row, rowCopy, ksize);
		
		homeRow = 1;
		
		static int handCopy[KSIZE_MAX] = {
			LEFT, LEFT, LEFT, LEFT,       RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT,       RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT,       RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT,       RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT,       RIGHT, RIGHT, RIGHT, RIGHT, 
		};
		copyArray(hand, handCopy, ksize);
		
		for (i = 0; i < KSIZE_MAX; ++i) {
			isOutside[i] = FALSE;
			isCenter[i]  = FALSE;
			printable[i] = TRUE;
			isAlpha[i] = 1;
        }
	} else if (fullKeyboard == K_TWENTYSEVEN) {
		static int fingerCopy[KSIZE_MAX] = {
			PINKY, RING, MIDDLE, INDEX, THUMB,     THUMB, INDEX, MIDDLE, RING, PINKY,
			PINKY, RING, MIDDLE, INDEX, THUMB,     THUMB, INDEX, MIDDLE, RING, PINKY,
			PINKY, RING, MIDDLE, INDEX, THUMB,     THUMB, INDEX, MIDDLE, RING, PINKY,
		};
		copyArray(finger, fingerCopy, ksize);
		
		static int columnCopy[KSIZE_MAX] = {
			0, 1, 2, 3, 4,   4, 3, 2, 1, 0,
			0, 1, 2, 3, 4,   4, 3, 2, 1, 0,
			0, 1, 2, 3, 4,   4, 3, 2, 1, 0,
			};
		copyArray(column, columnCopy, ksize);
		 
		static int rowCopy[] = {
			0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 
			1, 1, 1, 1, 1,   1, 1, 1, 1, 1, 
			2, 2, 2, 2, 2,   2, 2, 2, 2, 2,
		};
		copyArray(row, rowCopy, ksize);
		
		homeRow = 1;
		
		static int handCopy[KSIZE_MAX] = {
			LEFT, LEFT, LEFT, LEFT, LEFT,      RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT,      RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT,      RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
		};
		copyArray(hand, handCopy, ksize);
		
		static int printableCopy[] = {
			1, 1, 1, 1, 0,   0, 1, 1, 1, 1, 
			1, 1, 1, 1, 1,   1, 1, 1, 1, 1, 
			1, 1, 1, 1, 0,   1, 1, 1, 1, 1, 
		};
		copyArray(printable, printableCopy, ksize);

		static int alphaCopy[] = {
			0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 
			1, 1, 1, 1, 1,   1, 1, 1, 1, 1, 
			0, 0, 0, 0, 0,   1, 0, 0, 0, 0, 
		};
		copyArray(isAlpha, alphaCopy, ksize);

		for (i = 0; i < KSIZE_MAX; ++i) {
			isOutside[i] = FALSE;
			isCenter[i]  = FALSE;
        }
	} else if (fullKeyboard == K_ELEVEN) {
		static int fingerCopy[KSIZE_MAX] = {
			PINKY, RING, MIDDLE, INDEX, THUMB,     THUMB, INDEX, MIDDLE, RING, PINKY,
			PINKY, RING, MIDDLE, INDEX, THUMB,     THUMB, INDEX, MIDDLE, RING, PINKY,
			PINKY, RING, MIDDLE, INDEX, THUMB,     THUMB, INDEX, MIDDLE, RING, PINKY,
		};
		copyArray(finger, fingerCopy, ksize);
		
		static int columnCopy[KSIZE_MAX] = {
			0, 1, 2, 3, 4,   4, 3, 2, 1, 0,
			0, 1, 2, 3, 4,   4, 3, 2, 1, 0,
			};
		copyArray(column, columnCopy, ksize);
		 
		static int rowCopy[] = {
			0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 
			1, 1, 1, 1, 1,   1, 1, 1, 1, 1, 
		};
		copyArray(row, rowCopy, ksize);
		
		homeRow = 1;
		
		static int handCopy[KSIZE_MAX] = {
			LEFT, LEFT, LEFT, LEFT, LEFT,      RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT,      RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
		};
		copyArray(hand, handCopy, ksize);
		
		static int printableCopy[] = {
			0, 0, 0, 0, 0,   1, 0, 0, 0, 0, 
			1, 1, 1, 1, 1,   1, 1, 1, 1, 1, 
		};
		copyArray(printable, printableCopy, ksize);

		for (i = 0; i < KSIZE_MAX; ++i) {
			isOutside[i] = FALSE;
			isCenter[i]  = FALSE;
			isAlpha[i] = 1;
        }
        	} else if (fullKeyboard == K_EIGHTEEN) {
		static int fingerCopy[KSIZE_MAX] = {
			PINKY, RING, MIDDLE, INDEX, THUMB,     THUMB, INDEX, MIDDLE, RING, PINKY,
			PINKY, RING, MIDDLE, INDEX, THUMB,     THUMB, INDEX, MIDDLE, RING, PINKY,
			PINKY, RING, MIDDLE, INDEX, THUMB,     THUMB, INDEX, MIDDLE, RING, PINKY,
		};
		copyArray(finger, fingerCopy, ksize);
		
		static int columnCopy[KSIZE_MAX] = {
			0, 1, 2, 3, 4,   4, 3, 2, 1, 0,
			0, 1, 2, 3, 4,   4, 3, 2, 1, 0,
			};
		copyArray(column, columnCopy, ksize);
		 
		static int rowCopy[] = {
			0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 
			1, 1, 1, 1, 1,   1, 1, 1, 1, 1, 
		};
		copyArray(row, rowCopy, ksize);
		
		homeRow = 1;
		
		static int handCopy[KSIZE_MAX] = {
			LEFT, LEFT, LEFT, LEFT, LEFT,      RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT,      RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
		};
		copyArray(hand, handCopy, ksize);
		
		static int printableCopy[] = {
			1, 1, 1, 1, 0,   0, 1, 1, 1, 1, 
			1, 1, 1, 1, 1,   1, 1, 1, 1, 1, 
		};
		copyArray(printable, printableCopy, ksize);

		for (i = 0; i < KSIZE_MAX; ++i) {
			isOutside[i] = FALSE;
			isCenter[i]  = FALSE;
			isAlpha[i] = 1;
        }
        	} else if (fullKeyboard == K_NINETEEN) {
		static int fingerCopy[KSIZE_MAX] = {
			PINKY, RING, MIDDLE, INDEX, THUMB,     THUMB, INDEX, MIDDLE, RING, PINKY,
			PINKY, RING, MIDDLE, INDEX, THUMB,     THUMB, INDEX, MIDDLE, RING, PINKY,
			PINKY, RING, MIDDLE, INDEX, THUMB,     THUMB, INDEX, MIDDLE, RING, PINKY,
		};
		copyArray(finger, fingerCopy, ksize);
		
		static int columnCopy[KSIZE_MAX] = {
			0, 1, 2, 3, 4,   4, 3, 2, 1, 0,
			0, 1, 2, 3, 4,   4, 3, 2, 1, 0,
			};
		copyArray(column, columnCopy, ksize);
		 
		static int rowCopy[] = {
			0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 
			1, 1, 1, 1, 1,   1, 1, 1, 1, 1, 
		};
		copyArray(row, rowCopy, ksize);
		
		homeRow = 1;
		
		static int handCopy[KSIZE_MAX] = {
			LEFT, LEFT, LEFT, LEFT, LEFT,      RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
			LEFT, LEFT, LEFT, LEFT, LEFT,      RIGHT, RIGHT, RIGHT, RIGHT, RIGHT, 
		};
		copyArray(hand, handCopy, ksize);
		
		static int printableCopy[] = {
			1, 1, 1, 1, 0,   1, 1, 1, 1, 1, 
			1, 1, 1, 1, 1,   1, 1, 1, 1, 1, 
		};
		copyArray(printable, printableCopy, ksize);

		static int alphaCopy[] = {
			0, 0, 0, 0, 1,   1, 0, 0, 0, 0, 
			1, 1, 1, 1, 1,   1, 1, 1, 1, 1, 
		};
		copyArray(isAlpha, alphaCopy, ksize);

		for (i = 0; i < KSIZE_MAX; ++i) {
			isOutside[i] = FALSE;
			isCenter[i]  = FALSE;
        }
};	

	
	for (i = 0; i < ksize; ++i)
		isCenterOrOutside[i] = isCenter[i] || isOutside[i];
    
    /* Find firstNumberIndex. */
    char *ptrToOne = strchr(keysToInclude, '1');
	if (ptrToOne) firstNumberIndex = (int) (ptrToOne - keysToInclude);
	else firstNumberIndex = -1;
    
    /* Adjust firstNumberIndex to fix for non-printable indices. */
    if (firstNumberIndex >= 0) {
        int saved = firstNumberIndex;
        int i;
        for (i = 0; i <= saved; ++i) {
            if (!printable[i]) ++firstNumberIndex;
        }
    }

}

/* Reads typing data from allChars.txt and allDigraphs.txt.
 * 
 * Produces monographs and digraphs involving backspace by assuming that all 
 * characters are equally mistyped.
 */
int initTypingData()
{
	int i;	
	FILE *file = fopen(DIGRAPH_FILE, "r");
	CHECK_FILE_FOR_NULL(file, DIGRAPH_FILE);
	
	int c = '\0';
	i = 0;
	totalDi = 0;
	diLen = 0;
	while (TRUE) {
		/* Skip any extra newlines. */
		while ((c = getc(file)) == '\n')
			;
		if (c == EOF) break;

		if (c == '\\') c = convertEscapeChar(getc(file));
		if (c == 0) {
			fprintf(stderr, "Error: In file %s, unknown escape character \\%c.\n",
                    DIGRAPH_FILE, c);
			fclose(file);
			return 1;
		}
		digraphs[i].key[0] = c;

		c = getc(file);
		if (c == '\\') c = convertEscapeChar(getc(file));
		if (c == 0) {
			fprintf(stderr, "Error: In file %s, unknown escape character \\%c.\n",
                    DIGRAPH_FILE, c);
			fclose(file);
			return 1;
		}
		digraphs[i].key[1] = c;
		
		c = getc(file); /* Skip the space between the digraph and the value. */
		
		if (strchr(keysToInclude, digraphs[i].key[0]) &&
				strchr(keysToInclude, digraphs[i].key[1])) {
			digraphs[i].value = 0;
			while ((c = getc(file)) != EOF && c >= '0' && c <= '9') {
				digraphs[i].value *= 10;
				digraphs[i].value += c - '0';
			}
			
			digraphs[i].value /= DIVISOR;
			totalDi += digraphs[i++].value;
			
			if (i >= DI_LEN_MAX)
				break;
		}

		/* Skip all extra characters. */
		while (c != EOF && c != '\n')
			c = getc(file);
	}
	
	diLen = i;
	fclose(file);
    
    if (diLen == 0) {
        fprintf(stderr, "Warning: In file %s, no digraphs found.\n",
                DIGRAPH_FILE);
        }
	

	file = fopen(MONOGRAPHFILE, "r");
	CHECK_FILE_FOR_NULL(file, MONOGRAPHFILE);
    
    initVariables();
	
	c = '\0';
	totalMon = 0;
	monLen = 0;
	for (i = 0; i < MON_LEN_MAX; ) {
		/* Skip any extra newlines. */
		while ((c = getc(file)) == '\n')
			;
		if (c == EOF) break;
		
		if (c == '\\') c = convertEscapeChar(getc(file));
		if (c == 0) {
			fprintf(stderr, "Error: In file %s, unknown escape character \\%c.\n",
                    MONOGRAPHFILE, c);
			fclose(file);
			return 1;
		}
		monographs[i].key = (char) c;
		
		c = getc(file); /* Skip the space between the char and the value. */
		
		if (strchr(keysToInclude, monographs[i].key)) {
			monographs[i].value = 0;
			while ((c = getc(file)) != EOF && c >= '0' && c <= '9') {
				monographs[i].value *= 10;
				monographs[i].value += c - '0';
			}
			
			monographs[i].value /= DIVISOR;
			totalMon += monographs[i].value;

			++i;
		}
		
		/* Skip all extra characters. */
		while (c != EOF && c != '\n')
			c = getc(file);
	}
	
	monLen = i;
	fclose(file);
    
    if (monLen == 0) {
        fprintf(stderr, "Warning: In file %s, no monographs found.\n",
                MONOGRAPHFILE);
    }
	
	/* If necessary, add the stats for backspace. */
	if (strchr(keysToInclude, '\b')) {
		/* Add backpace to the digraph list. */
		for (i = 0; i < monLen; ++i) {
		if (!isspace(monographs[i].key)) {
			int64_t errorRate = monographs[i].value * ERROR_RATE_PERCENT / 100;
			digraphs[diLen].key[0] = '\b';
			digraphs[diLen].key[1] = monographs[i].key;
			digraphs[diLen].value = errorRate;
			++diLen;
			
			digraphs[diLen].key[0] = monographs[i].key;
			digraphs[diLen].key[1] = '\b';
			digraphs[diLen].value = errorRate;
			++diLen;
		}
		}
	 
		/* Add backspace to the monograph list. */
		monographs[monLen].key = '\b';
		monographs[monLen].value = totalMon * ERROR_RATE_PERCENT / 100;
		++monLen;
	}

    qsort(monographs, monLen, sizeof(struct Monograph), &cmpMonographsByValue);
    qsort(digraphs, diLen, sizeof(struct Digraph), &cmpDigraphsByValue);
	int p = 0; 
  for (int i = 0; i < monLen;i++) {
  printf("%i : %c-%li\n", i, monographs[i].key, monographs[i].value);
  }
	while(p < 50) {
	if (digraphs[p].key[0] != ' ' && digraphs[p].key[1] != ' ') {
	printf("%i : %s-%li\n", p, digraphs[p].key, digraphs[p].value);
	}
  p++;

	}
	return 0;
}

/* 
 * Compile the typing data from each of the given files into a single file.
 * 
 * outfileName: The file to which the new typing data will be writtwentyseven.
 * filenames: The names of each file to be read.
 * multipliers: The multipliers corresponding with the filenames.
 * length: Length of filenames and multipliers.
 * unit: The unit size of the strings to be read (characters=1, digraphs=2, etc).
 * max: The maximum number of strings that can be put into the file.
 * 
 * Return Codes
 * 1: Null file.
 * 2: Allocation failure.
 * 
 * TODO: Refactor this to use monograph and digraph structs instead of two 
 *   parallel arrays of keys and values.
 */       
int compileTypingData(char *outfileName, const char *filenames[], 
		int multipliers[], int length, int unit, int max)
{
	size_t size = 5000;
	/* Number of elements in keys and values. */
	int dataLen = 0;

	const int lineLen = 100;
	char line[lineLen];
	
	FILE *outfile = fopen(outfileName, "w");
	CHECK_FILE_FOR_NULL(outfile, outfileName);
	if (outfile == NULL) {
		fprintf(stderr, "Error: null file %s.\n", outfileName);
		return 1;
	}
	
	struct NGraph *ngraphs = malloc(sizeof(struct NGraph) * size);
	if (ngraphs == NULL) {
		fprintf(stderr, "Error: In compileTypingData(), ngraphs is null (malloc failure).\n");
		return 2;
	}
    memset(ngraphs, 0, sizeof(struct NGraph) * size);

	int i, k;
	for (i = 0; i < length; ++i) {
		printf("file %s,  multiplier %d\n", filenames[i], multipliers[i]);
		
		if (multipliers[i] == 0)
			continue;
		
		FILE *file = fopen(filenames[i], "r");
		if (file == NULL) {
			fprintf(stderr, "Error: In compileTypingData(), null file %s.\n", filenames[i]);
			fclose(outfile);
			free(ngraphs);
			return 1;
		}
		
		while (fgets(line, lineLen-1, file)) {
			if (dataLen >= size) {
				size *= 2;
				ngraphs = realloc(ngraphs, sizeof(struct NGraph) * size);
				
				if (ngraphs == NULL) {
					fprintf(stderr, "Error: In compileTypingData(), ngraphs is null (realloc failure).\n");
					return 2;
				}
			}
			
			/* If the n-graph already exists, add to its value. */
			int found = FALSE;
			for (k = 0; k < dataLen; ++k) {
				if (streqn(ngraphs[k].key, line, unit)) {
					found = TRUE;
					ngraphs[k].value += atoi(line + unit + 1) * multipliers[i];
				}
			}
			
			/* If the n-graph does not already exist, add it. */
			if (found == FALSE) {
				ngraphs[dataLen].key = malloc(sizeof(char) * (unit + 1));
				if (ngraphs[dataLen].key == NULL) {
                    /* TODO: free all allocated memory */
					fprintf(stderr, "Error: In compileTypingData(), ngraphs[%d].key is null (malloc failure).\n", dataLen);
					return 2;
				}
				
				strncpy(ngraphs[dataLen].key, line, unit);
				ngraphs[dataLen].key[unit] = '\0';
				ngraphs[k].value = atoi(line + unit + 1) * multipliers[i];
				++dataLen;
			}
			
		}
		
		fclose(file);
	}
	
    qsort(ngraphs, dataLen, sizeof(struct NGraph), cmpNGraphsByValue);
	
	
	for (i = 0; i < dataLen && i < max; ++i) {
		strncpy(line, ngraphs[i].key, unit);
		sprintf(line + unit, " %ld\n", ngraphs[i].value);
		
		fputs(line, outfile);
		free(ngraphs[i].key);
	}
	
	fclose(outfile);
	free(ngraphs);
	
	return 0;
}

/* 
 * Accepts the following escape sequences: 
 * \n (newline)
 * \t (tab)
 * \s (shift)
 * \\ (backslash)
 * \b (backspace)
 * 
 * return 0: Unknown escape character.
 */
int convertEscapeChar(int c)
{
	if (c == 'n') {
		return '\n';
	} else if (c == 't') {
		return '\t';
	} else if (c == 's') {
		return ASCII_SHIFT;
	} else if (c == '\\') {
		return '\\';
	} else if (c == 'b') {
		return '\b'; /* backspace */
	} else return 0;
}

void initVariables()
{
    variablesLength = 0;
    
#define ADD_VAR(varName, desc) \
    variables[variablesLength].name = #varName; \
    variables[variablesLength].addr = &varName; \
    variables[variablesLength].description = desc; \
    ++variablesLength;
    
    ADD_VAR(detailedOutput, "(bool) provide additional information while running the algorithm");
    ADD_VAR(keepZXCV, "(bool) keep keys Z, X, C, and V in place");
    ADD_VAR(keepQWERTY, "(bool) try to keep keys in their QWERTY positions");
    ADD_VAR(keepNumbers, "(bool) keep numbers in place");
    ADD_VAR(keepBrackets, "(bool) keep brackets symmetrical");
    ADD_VAR(keepShiftPairs, "(bool) shifted/unshifted pairs of non-alphabetic characters stay together");
    ADD_VAR(keepAlphaPairs, "(bool) shifted/unshifted pairs of alphabetic characters stay together");
    ADD_VAR(keepTab, "(bool) keep Tab in place");
    ADD_VAR(keepNumbersShifted, "(bool) numbers do not move between shifted and unshifted");
    ADD_VAR(numThreads, "number of threads to create\n");
    ADD_VAR(distance, NULL);
    ADD_VAR(inRoll, NULL);
    ADD_VAR(outRoll, NULL);
    ADD_VAR(sameHand, NULL);
    ADD_VAR(sameFingerP, NULL);
    ADD_VAR(sameFingerR, NULL);
    ADD_VAR(sameFingerM, NULL);
    ADD_VAR(sameFingerI, NULL);
    ADD_VAR(rowChangeUp, NULL);
    ADD_VAR(rowChangeDown, NULL);
    ADD_VAR(handWarp, NULL);
    ADD_VAR(handSmooth, NULL);
    ADD_VAR(homeJump, NULL);
    ADD_VAR(homeJumpIndex, NULL);
    ADD_VAR(doubleJump, NULL);
    ADD_VAR(toCenter, NULL);
    ADD_VAR(toOutside, NULL);
    
#undef ADD_VAR
}

int getValue(const char *name)
{
    /* This is O(n), but it's a smallish n and speed is not essential. */
    int i;
    for (i = 0; i < variablesLength; ++i) {
        if (streq(name, variables[i].name)) {
            printf("%s = %d\n\n", variables[i].name, *variables[i].addr);
            return 0;
        }
    }
    
    printf("Unknown variable \"%s\". Type \"variables\" for a complete listing of possible variables.\n\n", name);
    return 1;
}

/*
 * Takes a string containing a name and a value. Sets the variable with the 
 * given name to the given value.
 * 
 * If the variable is successfully changed, returns 0. Otherwise, returns 
 * nonzero.
 */
int setValue(char *str)
{
	size_t len = strlen(str);
	
	char *name = str;
	char *valstr = strchr(str, ' ');
    
	if (len == 0 || valstr == NULL) {
		printf("No variable specified. Type \"variables\" for a complete listing of possible variables.\n\n");
		return 2;
	}
    
	*valstr = '\0'; ++valstr;
	
	int value = atoi(valstr);
    
    /* This is O(n), but it's a smallish n and speed is not essential. */
    int i;
    for (i = 0; i < variablesLength; ++i) {
        if (streq(name, variables[i].name)) {
            *variables[i].addr = value;
            /* If the user changes a cost, it is necessary to redo
             * preCalculateFitness().
             */
            if (USE_COST_ARRAY)
                preCalculateFitness();
            
            printf("%s set to %d.\n\n", name, value);
            return 0;
        }
    }
	
    printf("Unknown variable \"%s\". Type \"variables\" for a complete listing of possible variables.\n\n", name);
    return 1;
}

int cmpMonographsByValue(const void *one, const void *two)
{
    int64_t val1 = ((struct Monograph *) one)->value;
    int64_t val2 = ((struct Monograph *) two)->value;
    if (val1 > val2) return -1;
    else if (val1 < val2) return 1;
    return 0;
}

int cmpDigraphsByValue(const void *one, const void *two)
{
    int64_t val1 = ((struct Digraph *) one)->value;
    int64_t val2 = ((struct Digraph *) two)->value;
    if (val1 > val2) return -1;
    else if (val1 < val2) return 1;
    return 0;
}

int cmpNGraphsByValue(const void *one, const void *two)
{
    int64_t val1 = ((struct NGraph *) one)->value;
    int64_t val2 = ((struct NGraph *) two)->value;
    if (val1 > val2) return -1;
    else if (val1 < val2) return 1;
    return 0;
}

/* Returns the matching bracket for c. If c is not a bracket, returns 0.
 */
inline char getMatchingBracket(char c)
{
	switch (c) {
	case '(':
		return ')';
	case ')':
		return '(';
	case '[':
		return ']';
	case ']':
		return '[';
	case '{':
		return '}';
	case '}':
		return '{';
	case '<':
		return '>';
	case '>':
		return '<';
	default:
		return 0;
	}
}


/* 
 * If c should be kept in a pair with its shifted or unshifted character, 
 * returns true. Otherwise, returns false.
 * 
 * Alphabetical characters and whitespace are kept in shifted pairs. Other keys 
 * are not, unless the keepShiftPairs variable is set to TRUE.
 */
inline int keepShiftPair(char c)
{
    if ( keepShiftPairs || (isalpha(c) && keepAlphaPairs) || (keepSpacePairs && isspace(c))) {return TRUE;}
    else if (keepPairs) {
        for (int i = 0; i < strlen(pairList); i++) {
            if (c == pairList[i]) {return TRUE;}
        }
    } 
	return FALSE;
}
 
void setksize(int type)
{
	fullKeyboard = type; 
	
	switch (fullKeyboard) {
	case K_NO:
		ksize = 30;
		trueksize = 30;
		kbdFilename = "layoutStore.txt";
		break;
	case K_NOT:
		ksize = 36;
		trueksize = 33;
		kbdFilename = "layoutStore.txt";
		break;
	case K_STANDARD:
		ksize = 56;
		trueksize = 47;
		kbdFilename = "fullLayoutStore.txt";
		break;
	case K_KINESIS:
		ksize = 72;
		trueksize = 50;
		kbdFilename = "kinesisLayoutStore.txt";
		break;
	case K_NOKI:
		ksize = 60;
		trueksize = 26;
		kbdFilename = "nokiLayoutStore.txt";
		break;
	case K_IPHONE:
		ksize = 30;
		trueksize = 26;
		kbdFilename = NULL;
		break;
	case K_TRIM:
	    ksize = 26;
	    trueksize=26;  
	    kbdFilename = "trimLayoutStore.txt";
	    break;
	case K_GIGI:
	    ksize = 36;
	    trueksize=30;
	    kbdFilename = "gigiLayoutStore.txt";
	    break;    
	case K_MINI:
	    ksize = 36;
	    trueksize=36;
	    kbdFilename = "miniLayoutStore.txt";
	    break;    
	case K_ADD:
	    ksize = 24;
	    trueksize= 24; 
	    kbdFilename = "addLayoutStore.txt";
	    break;
	case K_BADHD:
	    ksize = 32;
	    trueksize= 28; 
	    kbdFilename = "badhdLayoutStore.txt";
	    break;
	case K_GIBO:
	    ksize = 60;
	    trueksize=28; 
	    kbdFilename = "giboLayoutStore.txt";
	    break;  
	case K_HOCUS:
	    ksize = 50;
	    trueksize=30;
	    kbdFilename = "hocusLayoutStore.txt";
	    break;
	case K_HOMU:
	    ksize = 36;
	    trueksize=27; 
	    kbdFilename = "homusLayoutStore.txt";
	    break;  
	case K_GODOT:
	    ksize = 60;
	    trueksize=26;
	    kbdFilename = "godotLayoutStore.txt";  
	    break;
	case K_GEORGI:
	    ksize = 36;
	    trueksize= 37; 
	    kbdFilename = "georgiLayoutStore.txt";
	    break;    
	case K_LAPTOP:
	    ksize = 39;
	    trueksize= 39; 
	    kbdFilename = "laptopLayoutStore.txt";
	    break;    
	case K_SNOTDOG:
	    ksize = 32;
	    trueksize= 32; 
	    kbdFilename = "snotdogLayoutStore.txt";
	    break;    
	case K_TWENTYSEVEN:
	    ksize = 30;
	    trueksize= 27; 
	    kbdFilename = "snotdogLayoutStore.txt";
	    break;    
	case K_ELEVEN:
	    ksize = 20;
	    trueksize= 11; 
	    kbdFilename = "snotdogLayoutStore.txt";
	    break;    
	case K_EIGHTEEN:
	    ksize = 20;
	    trueksize= 16; 
	    kbdFilename = "snotdogLayoutStore.txt";
	    break;    
	case K_NINETEEN:
	    ksize = 20;
	    trueksize= 17; 
	    kbdFilename = "snotdogLayoutStore.txt";
	    break;    
	case K_RUNNER:
	    ksize = 45;
	    trueksize = 45;
	} 
	initData();
	if (USE_COST_ARRAY)
		preCalculateFitness();
}
 
