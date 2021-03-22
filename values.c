/*
 *  values.c
 *  Typing
 *
 *  Created by Michael Dickens on 8/23/09.
 *
 */

#include "values.h"

int initValues()
{
	int i;
	
	initCosts();
	
	if (fullKeyboard == K_NO) {
		// Set keyboard position costs. These costs were determined by looking 
		// at how the positions were valued on some of the best alternative 
		// layouts.
		static int64_t costsCopy[KSIZE_MAX] = {
			 40,  40,  30,  40,  70,  80,  40,  30,  40,  40, 
			  0,   0,   0,   0,  30,  30,   0,   0,   0,   0, 
			 70,  70,  70,  50,  95,  60,  40,  60,  70,  70, 
		};
	
		for (i = 0; i < ksize; ++i)
			distanceCosts[i] = costsCopy[i];
		
	} else if (fullKeyboard == K_STANDARD) {
		
		// These costs are optimized for a full standard layout. Any cost that 
		// is 999 is not supposed to contain any character.
		static int64_t costsCopy[KSIZE_MAX] = {
			110, 100,  90,  75, 100, 120, 160, 100,  75,  90, 100, 110, 120, 999,
			999,  40,  40,  30,  40,  70,  80,  40,  30,  40,  40,  60,  90, 140, 
			999,   0,   0,   0,   0,  30,  30,   0,   0,   0,   0,  50, 999, 999, 
			999,  70,  70,  70,  50,  95,  60,  40,  60,  70,  70, 999, 999, 999, 
		};
		for (i = 0; i < ksize; ++i)
			distanceCosts[i] = costsCopy[i];
			
	} else if (fullKeyboard == K_KINESIS) {
		
		// These costs are optimized for Kinesis. Any cost that is 999 is not 
		// supposed to contain any character.
		static int64_t costsCopy[KSIZE_MAX] = {
			120, 110, 100,  75, 100, 130, 130, 100,  75, 100, 110, 120, 
			 90,  40,  40,  30,  40,  70,  70,  40,  30,  40,  40,  90, 
			 60,   0,   0,   0,   0,  40,  40,   0,   0,   0,   0,  60, 
			999,  70,  70,  70,  50,  80,  80,  50,  70,  70,  70, 999, 
			999, 140, 140, 999, 999, 999, 999, 999, 999, 140, 140, 999, 	
			  0,  50, 999, 999, 999, 999, 999, 999, 999, 999,  50,   0, 
		};
		for (i = 0; i < ksize; ++i)
			distanceCosts[i] = costsCopy[i];
		
	} else if (fullKeyboard == K_IPHONE) {
		
		// Thumbs are centered over the QWERTY D and K keys.
		static int64_t costsCopy[KSIZE_MAX] = {
			  45,  30,  20,  10,  20,  20,  10,  20,  30,  40, 
			  20,  10,   0,   0,  10,  10,   0,   0,  10, 999,
			 999,  60,  50,  30,  20,  20,  50,  60, 999, 999, 
		};
		for (i = 0; i < ksize; ++i)
			distanceCosts[i] = costsCopy[i];
		
	} else if (fullKeyboard == K_LAPTOP) {
		
		// These costs are optimized for a full standard layout. Any cost that 
		// is 999 is not supposed to contain any character.
		static int64_t costsCopy[KSIZE_MAX] = {
			110, 100,  90,  75, 100, 120, 160, 100,  75,  90, 100, 110, 120, 999,
			999,  40,  40,  30,  40,  70,  80,  40,  30,  40,  40,  60,  90, 140, 
			999,   0,   0,   0,   0,  30,  30,   0,   0,   0,   0,  50, 999, 999, 
			999,  70,  70,  70,  50,  95,  60,  40,  60,  70,  70, 999, 999, 999, 
			999, 999, 999, 999,   0,  20,  20,   0, 999, 999, 999, 999, 999, 999, 
		};
		for (i = 0; i < ksize; ++i)
			distanceCosts[i] = costsCopy[i];
			
	} else if (fullKeyboard == K_CRKBD) {
		
		// These costs are optimized for Kinesis. Any cost that is 999 is not 
		// supposed to contain any character.
		static int64_t costsCopy[KSIZE_MAX] = {
			 40,  40,  30,  40,  80,  20,  20,  80,  40,  30,  40,  60, 
			  0,   0,   0,   0,  50,   0,   0,  50,   0,   0,   0,   0, 
			 90,  70,  40,  30,  90,  20,  20,  90,  30,  40,  70,  90, 
		};
		for (i = 0; i < ksize; ++i)
			distanceCosts[i] = costsCopy[i];
		
	} else if (fullKeyboard == K_NOT) {
		// Set keyboard position costs. These costs were determined by looking 
		// at how the positions were valued on some of the best alternative 
		// layouts.
		static int64_t costsCopy[KSIZE_MAX] = {
			 40,  40,  30,  40,  80, 999, 999,  80,  40,  30,  40,  60, 
			  0,   0,   0,   0,  50,   0,   0,  50,   0,   0,   0,   0, 
			 90,  70,  40,  30,  90, 999, 999,  90,  30,  40,  70,  90, 
		};
	
		for (i = 0; i < ksize; ++i)
			distanceCosts[i] = costsCopy[i];
    } else if (fullKeyboard == K_NOTT) {
		// Set keyboard position costs. These costs were determined by looking 
		// at how the positions were valued on some of the best alternative 
		// layouts.
		static int64_t costsCopy[KSIZE_MAX] = {
			 40,  40,  30,  40,  80,  20,  20,  80,  40,  30,  40,  60, 
			  0,   0,   0,   0,  50,   0,   0,  50,   0,   0,   0,   0, 
			 90,  70,  40,  30,  60, 999, 999,  60,  30,  40,  70,  90, 
		};
	
		for (i = 0; i < ksize; ++i)
			distanceCosts[i] = costsCopy[i];
    } else if (fullKeyboard == K_ADHD) {
		// Set keyboard position costs. These costs were determined by looking 
		// at how the positions were valued on some of the best alternative 
		// layouts.
		static int64_t costsCopy[KSIZE_MAX] = {
			 40,  40,  30,  40,  20,  20,  40,  30,  40,  60, 
			  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 
			 90,  70,  40,  30, 999, 999,  30,  40,  70,  90, 
        };
	
		for (i = 0; i < ksize; ++i)
			distanceCosts[i] = costsCopy[i];
        
    } else if (fullKeyboard == K_TRAN) {
		// Set keyboard position costs. These costs were determined by looking 
		// at how the positions were valued on some of the best alternative 
		// layouts.
		static int64_t costsCopy[KSIZE_MAX] = {
			 40,  40,  30,  40,  20,  20,  90,  40,  30,  40,  60, 110,
			  0,   0,   0,   0,   0,   0,  70,   0,   0,   0,   0, 90,
			 90,  70,  40,  30, 999, 999,  30,  40,  70,  90, 
		};
	
		for (i = 0; i < ksize; ++i)
			distanceCosts[i] = costsCopy[i];
    }

	// Based on distance from the ctrl key and how much of a stretch it is.
	shortcutCosts[ 0] =  0; shortcutCosts[ 1] =  0; shortcutCosts[ 2] =  1; shortcutCosts[ 3] =  3; shortcutCosts[ 4] =  4; 
	shortcutCosts[ 5] =  8; shortcutCosts[ 6] = 10; shortcutCosts[ 7] = 10; shortcutCosts[ 8] = 10; shortcutCosts[ 9] = 10; 
	shortcutCosts[10] =  0; shortcutCosts[11] =  0; shortcutCosts[12] =  2; shortcutCosts[13] =  3; shortcutCosts[14] =  5; 
	shortcutCosts[15] =  8; shortcutCosts[16] = 10; shortcutCosts[17] = 10; shortcutCosts[18] = 10; shortcutCosts[19] = 10; 
	shortcutCosts[20] =  0; shortcutCosts[21] =  0; shortcutCosts[22] =  0; shortcutCosts[23] =  2; shortcutCosts[24] =  4; 
	shortcutCosts[25] =  8; shortcutCosts[26] = 10; shortcutCosts[27] = 10; shortcutCosts[28] = 10; shortcutCosts[29] = 10; 
	
	return 0;
}

void initCosts()
{
	detailedOutput = TRUE;
    
    /* If you do not wish to use multithreading, set numThreads to 1. */
	numThreads = 1;
	
	keepZXCV = FALSE;
	keepQWERTY = FALSE;
	keepNumbers = 1;
	keepBrackets = TRUE;
	keepShiftPairs = FALSE;
	keepTab = FALSE;
	keepConsonantsRight = FALSE;
	keepNumbersShifted = FALSE;
	
	zCost = 10;
	xCost =  6;
	cCost = 12;
	vCost = 14;
	qwertyPosCost = 14;
	qwertyFingerCost = 4;
	qwertyHandCost = 20;
	bracketsCost = 5000000;
	numbersShiftedCost = -1000000;

	if (fullKeyboard == K_KINESIS) {
		fingerPercentMaxes[0] = fingerPercentMaxes[FINGER_COUNT - 1] =  7.5;
		fingerPercentMaxes[1] = fingerPercentMaxes[FINGER_COUNT - 2] = 10.0;
		fingerPercentMaxes[2] = fingerPercentMaxes[FINGER_COUNT - 3] = 20.0;
		fingerPercentMaxes[3] = fingerPercentMaxes[FINGER_COUNT - 4] = 20.0;
		fingerPercentMaxes[4] = fingerPercentMaxes[FINGER_COUNT - 5] = 18.0;
	} else {
		fingerPercentMaxes[0] = fingerPercentMaxes[FINGER_COUNT - 1] =  9.0;
		fingerPercentMaxes[1] = fingerPercentMaxes[FINGER_COUNT - 2] = 11.5;
		fingerPercentMaxes[2] = fingerPercentMaxes[FINGER_COUNT - 3] = 22.0;
		fingerPercentMaxes[3] = fingerPercentMaxes[FINGER_COUNT - 4] = 22.0;
		fingerPercentMaxes[4] = fingerPercentMaxes[FINGER_COUNT - 5] = 18.0;		
	}

	
	fingerWorkCosts[0] = fingerWorkCosts[FINGER_COUNT - 1] = 40;
	fingerWorkCosts[1] = fingerWorkCosts[FINGER_COUNT - 2] = 30;
	fingerWorkCosts[2] = fingerWorkCosts[FINGER_COUNT - 3] = 20;
	fingerWorkCosts[3] = fingerWorkCosts[FINGER_COUNT - 4] = 20;
	fingerWorkCosts[4] = fingerWorkCosts[FINGER_COUNT - 5] = 20;
	
	/* All values are compounding. For example, say we jump over the home row
	 * on the index finger. The cost is 
     *     sameHand + rowChange + homeJump + homeJumpIndex.
     */
    sfmult = 3;
    irmult = 3;
    
	distance =		  1;
	inRoll =		-40*irmult;
	outRoll =		  -5;
	sameHand =		  5;
	sameFingerP =	150*sfmult;
	sameFingerR =	140*sfmult;
	sameFingerM =	110*sfmult;
	sameFingerI =	 90*sfmult;
	sameFingerT =	100*sfmult;
	rowChangeDown =  0;
	rowChangeUp =    0;
	handWarp =		 25;
	handSmooth =	- 5;
	homeJump =		0;
	homeJumpIndex = 0;
	doubleJump =	0; /* Does not compound with homeJump. */
	ringJump =       0;
	toCenter =		 100;
	toOutside =		 30;
	
	shiftCost =		100;
	doubleShiftCost=150;
}
