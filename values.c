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
		
	} else if (fullKeyboard == K_NOT) {
		// Set keyboard position costs. These costs were determined by looking 
		// at how the positions were valued on some of the best alternative 
		// layouts.
		static int64_t costsCopy[KSIZE_MAX] = {
			 60,  40,  30,  30,  70, 999, 999,  70,  30,  30,  40,  60, 
			  0,   0,   0,   0,  50, 999,  10,  50,   0,   0,   0,   0, 
			 90,  60,  40,  40,  90,   0,  10,  90,  40,  40,  60,  90, 
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
			
	} else if (fullKeyboard == K_LAPTOP) {
		
		// These costs are optimized for a full standard layout. Any cost that 
		// is 999 is not supposed to contain any character.
		static int64_t costsCopy[KSIZE_MAX] = {
	    90,  75,  42,  30,  36,   72,  333,  84,  36,  30,  42,  75,  90, 100, 
	    60,   15,   6,   0,   0,   57,  333,  57,   0,   0,   6,  15,      60,
		75,       54,  45,  21, 48, 333, 333,  48,  21,  45,  54,          75, 
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
	} else if (fullKeyboard == K_NOKI) {
		
		// These costs are optimized for Kinesis. Any cost that is 999 is not 
		// supposed to contain any character.
		static int64_t costsCopy[KSIZE_MAX] = {
			999,  40,  40,  30,  40,  70,  70,  40,  30,  40,  40, 999,
			999,   0,   0,   0,   0,  40,  40,   0,   0,   0,   0, 999,
			999,  70,  70,  70,  50,  80,  80,  50,  70,  70,  70, 999,
			999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999, 999,
			999, 999, 999, 999,  50,   0,   0,  50, 999, 999, 999, 999,  
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
		
	} else if (fullKeyboard == K_TRIM) {
	    
	    static int64_t costsCopy[KSIZE_MAX] = {
			 40,  40,  30,  40,       70,  40,  30,  40,  40,  100, 
			  0,   0,   0,   0,  40,  40,   0,   0,   0,   0,  90, 
			                          80,  50,  70,  70,  70 
	    };
		for (i = 0; i < ksize; ++i)
			distanceCosts[i] = costsCopy[i];
    } else if (fullKeyboard == K_GIGI) {
	    
	    static int64_t costsCopy[KSIZE_MAX] = {
			 60,  40,  30,  30,  70, 30,     30,  70,  30,  30,  40,  60, 
			  0,   0,   0,   0,  50,  0,      0,  50,   0,   0,   0,   0, 
			999,  60,  40, 999, 999, 10,      0, 999, 999,  40,  60, 999, 
	    };
		for (i = 0; i < ksize; ++i)
			distanceCosts[i] = costsCopy[i];    
    } else if (fullKeyboard == K_MINI) {
	    
	    static int64_t costsCopy[KSIZE_MAX] = {
/*			 60,  40,  30,  40,  70,       70,  40,  30,  30, 999, 
			  5,   0,   0,   0,  40,       40,   0,   0,   0,   5, 
			 70,  70,  70,  50,  80,       80,  50,  70,  70, 999,
			              999,  0, 20,  20,  0, 999,
*/
			 75,   6,   0,   0, 576,      576,   0,   0,   6,  15, 
			 15,   6,   0,   0, 456,      456,   0,   0,   6,  15, 
			552, 384, 336, 168, 504,      504, 168, 336, 384, 552, 
			               30,  0, 20,  20,  0, 30,
	    };
		for (i = 0; i < ksize; ++i)
			distanceCosts[i] = costsCopy[i];    
    } else if (fullKeyboard == K_ADD) { 
	    
	    static int64_t costsCopy[KSIZE_MAX] = {
			 60,  40,  30,  40,  40,  30,  40,  60, 
			  0,   0,   0,   0,   0,   0,   0,   0, 
			 90,  70,  70,  70,  60,  60,  70,  90,
	    };
		for (i = 0; i < ksize; ++i)
			distanceCosts[i] = costsCopy[i];    
    } else if (fullKeyboard == K_BADHD) { 
	    
	    static int64_t costsCopy[KSIZE_MAX] = {
			 60,  40,  30,  30,      30,  30,  40,  60, 
			  0,   0,   0,   0,       0,   0,   0,   0,
			 90,  70,  60,  60,      60,  60,  70,  90, 
			999,  30,   0,   0,       0,   0,  30, 999, 
	    };
		for (i = 0; i < ksize; ++i)
			distanceCosts[i] = costsCopy[i];    
    } else if (fullKeyboard == K_GIBO) {
	    
	    static int64_t costsCopy[KSIZE_MAX] = {
			 42,  41,  31,  41,  31,  30,  40,  30,  40,  42,
			  1,   0,   0,   0,   0,   0,   0,   0,   0,   1,
			142, 141, 131, 141, 131, 131, 141, 131, 141, 142,
			101, 100, 100, 100, 100, 100, 100, 100, 100, 101,
			202, 201, 201, 201, 201, 201, 201, 201, 201, 202,
			201, 200, 200, 200, 200, 200, 200, 200, 200, 201,
	    };
		for (i = 0; i < ksize; ++i)
			distanceCosts[i] = costsCopy[i];    
    } else if (fullKeyboard == K_HOCUS) {
	    
	    static int64_t costsCopy[KSIZE_MAX] = {
       40,  40,  30,  40,  50,  50,  40,  30,  40,  40,
	1,   0,   0,   0,  40,  40,   0,   0,   0,   1,
      140, 140, 130, 140, 150, 150, 140, 130, 140, 140,
      101, 100, 100, 100, 140, 140, 100, 100, 100, 101,
      333, 101,  10,   0,  10,  10,   0,  10, 101, 333,
	    };
		for (i = 0; i < ksize; ++i)
			distanceCosts[i] = costsCopy[i];    
    } else if (fullKeyboard == K_HOMU) {
	    static int64_t costsCopy[KSIZE_MAX] = {
			 60,  40,  30,  30,  80, 30,     30,  80,  30,  30,  40,  60, 
			  0,   0,   0,   0,  50,  0,      0,  50,   0,   0,   0,   0, 
			 60,  60,  40,  40,  70,  0,      0,  70,  40,  40,  60,  60, 
	    };
		for (i = 0; i < ksize; ++i)
			distanceCosts[i] = costsCopy[i];    
    } else if (fullKeyboard == K_GODOT) {
	    
	    static int64_t costsCopy[KSIZE_MAX] = {
		 70,  40,  30,  40,  30,        30,  40,  30,  40,  70, 
		  0,   0,   0,   0,   0,         0,   0,   0,   0,   0, 
		 70,  70,  40,  30,  70,        70,  30,  40,  70,  70, 
		170, 140, 130, 140, 130,       130, 140, 130, 140, 170, 
		100, 100, 100, 100, 100,       100, 100, 100, 100, 100, 
		170, 170, 140, 130, 170,       170, 130, 140, 170, 170, 
	    };
		for (i = 0; i < ksize; ++i)
			distanceCosts[i] = costsCopy[i];    
	} else if (fullKeyboard == K_GEORGI) {
		
		static int64_t costsCopy[KSIZE_MAX] = {
			110,  40,  40,  30,  40,  70,  70,  40,  30,  40,  40, 110, 
			 60,   0,   0,   0,   0,  40,  40,   0,   0,   0,   0,  60, 
			999, 999, 999,  40,   0,  30,  30,   0,  40, 999, 999, 999, 
		};
		for (i = 0; i < ksize; ++i)
			distanceCosts[i] = costsCopy[i];		
	} else if (fullKeyboard == K_RUNNER) {
		
		static int64_t costsCopy[KSIZE_MAX] = {
			  0,   0,   0,   0,  40,  40,   0,   0,   0,   0, 
			  0,   0,   0,   0,  40,  40,   0,   0,   0,   0, 
		    100, 100, 100, 100, 140, 140, 100, 100, 100, 100, 
	   160, 100, 100, 100, 100, 140, 140, 100, 100, 100, 100, 160,
		     999, 999, 999,
		};
		for (i = 0; i < ksize; ++i)
			distanceCosts[i] = costsCopy[i];		
	} else if (fullKeyboard == K_SNOTDOG) {
		
		static int64_t costsCopy[KSIZE_MAX] = {
			 40,  40,  30,  40,      40,  30,  40,  40,
			  0,   0,   0,   0,       0,   0,   0,   0,
			 99,  99,   0,  30,      30,   0,  99,  99,
       99,  99,  99,  99,      99,  99,  99,  99,
		};
		for (i = 0; i < ksize; ++i)
			distanceCosts[i] = costsCopy[i];		
	} else if (fullKeyboard == K_TWENTYSEVEN) {
		
		static int64_t costsCopy[KSIZE_MAX] = {
			 60,  40,  20,  30, 10,      10,  30,  20,  40,  60,
			 10,   0,   0,   0,  0,       0,   0,   0,   0,  10,
			 90,  60,  40,  40, 10,      10,  40,  40,  60,  90,
		};
		for (i = 0; i < ksize; ++i)
			distanceCosts[i] = costsCopy[i];		
	} else if (fullKeyboard == K_ELEVEN) {
		
		static int64_t costsCopy[KSIZE_MAX] = {
			 60,  40,  20,  30, 10,      10,  30,  20,  40,  60,
			 10,   0,   0,   0,  0,       0,   0,   0,   0,  10,
		};
		for (i = 0; i < ksize; ++i)
			distanceCosts[i] = costsCopy[i];		
	} else if (fullKeyboard == K_EIGHTEEN) {
		
		static int64_t costsCopy[KSIZE_MAX] = {
			 60,  40,  20,  30, 10,      10,  30,  20,  40,  60,
			 10,   0,   0,   0,  0,       0,   0,   0,   0,  10,
		};
		for (i = 0; i < ksize; ++i)
			distanceCosts[i] = costsCopy[i];		
	} else if (fullKeyboard == K_NINETEEN) {
		
		static int64_t costsCopy[KSIZE_MAX] = {
			 60,  40,  20,  30, 10,      10,  30,  20,  40,  60,
			 10,   0,   0,   0,  0,       0,   0,   0,   0,  10,
		};
		for (i = 0; i < ksize; ++i)
			distanceCosts[i] = costsCopy[i];		
	};
		         
	

	// Based on distance from the ctrl key and how much of a stretch it is.
	shortcutCosts[ 0] =  0; shortcutCosts[ 1] =  0; shortcutCosts[ 2] =  0; shortcutCosts[ 3] =  0; shortcutCosts[ 4] =  0; 
	shortcutCosts[ 5] =  0; shortcutCosts[ 6] =  0; shortcutCosts[ 7] =  0; shortcutCosts[ 8] =  0; shortcutCosts[ 9] =  0; 
	shortcutCosts[10] =  0; shortcutCosts[11] =  0; shortcutCosts[12] =  0; shortcutCosts[13] =  0; shortcutCosts[14] =  0; 
	shortcutCosts[15] =  0; shortcutCosts[16] =  0; shortcutCosts[17] =  0; shortcutCosts[18] =  0; shortcutCosts[19] =  0; 
	shortcutCosts[20] =  0; shortcutCosts[21] =  0; shortcutCosts[22] =  0; shortcutCosts[23] =  0; shortcutCosts[24] =  0; 
	shortcutCosts[25] =  0; shortcutCosts[26] =  0; shortcutCosts[27] =  0; shortcutCosts[28] =  0; shortcutCosts[29] =  0; 
	
	return 0;
};

void initCosts()
{
	detailedOutput = TRUE;
    
    /* If you do not wish to use multithreading, set numThreads to 1. */
	numThreads = 8;
	
	keepZXCV = FALSE;
	keepQWERTY = FALSE;
	keepNumbers = FALSE;
	keepBrackets = TRUE;
	keepTab = FALSE;
	keepConsonantsRight = TRUE;
	keepNumbersShifted = FALSE;

    // Variables for keeping shifted key in same location as associated starting key
	keepShiftPairs = 0; // keeps everything attached
	keepAlphaPairs = 1; // keeps alphabetical characters (usually want true for standard layouts)
	keepSpacePairs = 0; // keep all whitespace (space, tab, newline). Usually used to keep, for example, shift+tab as shift+tab and not shift+e (E)
	keepPairs = TRUE;
  //Pais list is 30 in values.h if you need to make it bigger
  strcpy(pairList, "\b\t\n ,.;/");
  //\x0E is the code for ascii_shift. which doesn't? work correctly?
  //Add things to this to have them move with their shift partner when it swaps
	
	lockLetters = FALSE;
	//Lock list is 30 in values.h if you need to make it bigger
	strcpy(lockList, "aoeiu");//aion ehtsr,");//y:,lgf|u;pmdc&");//trnsgclpw");
  //    strcpy(lockList, "youfldncaie \nmhtsr,\tpb");        
  //    strcpy(lockList, "\t_;`y()jk");
  //	strcpy(lockList, "-_.,(){}jkqvxz/&;'");
	keepLeft = FALSE;
	strcpy(leftList, "aieou");
  

  rowLock = FALSE;
  lockAlphas = FALSE;
  isCommaDead = FALSE;

	
	zCost = 10;
	xCost =  6;
	cCost = 12;
	vCost = 14;
	qwertyPosCost = 14;
	qwertyHandCost = 20;
	qwertyFingerCost = 4;
	bracketsCost = 5000000;
	numbersShiftedCost = -1000000;
	leftCost = 5000000;
	
	if ((fullKeyboard == K_KINESIS || fullKeyboard == K_HOCUS || fullKeyboard == K_HOMU || fullKeyboard == K_GIBO || fullKeyboard == K_BADHD || fullKeyboard == K_GODOT || fullKeyboard == K_SNOTDOG)) {
		fingerPercentMaxes[0] = fingerPercentMaxes[FINGER_COUNT - 1] =  6.0;
		fingerPercentMaxes[1] = fingerPercentMaxes[FINGER_COUNT - 2] =  8.0;
		fingerPercentMaxes[2] = fingerPercentMaxes[FINGER_COUNT - 3] = 10.0;
		fingerPercentMaxes[3] = fingerPercentMaxes[FINGER_COUNT - 4] = 12.0;
		fingerPercentMaxes[4] = fingerPercentMaxes[FINGER_COUNT - 5] = 12.0;
	} else {
		fingerPercentMaxes[0] = fingerPercentMaxes[FINGER_COUNT - 1] = 7.5;
		fingerPercentMaxes[1] = fingerPercentMaxes[FINGER_COUNT - 2] = 11.5;
		fingerPercentMaxes[2] = fingerPercentMaxes[FINGER_COUNT - 3] = 22.0;
		fingerPercentMaxes[3] = fingerPercentMaxes[FINGER_COUNT - 4] = 22.0;
		fingerPercentMaxes[4] = fingerPercentMaxes[FINGER_COUNT - 5] = 22.0;		
	}

int fwc_mult = 1;
int sf_mult =  7;
int sh_mult =  1;
int o_mult =   -2;
int i_mult =   3;

	fingerWorkCosts[0] = fingerWorkCosts[FINGER_COUNT - 1] = fwc_mult*40;
	fingerWorkCosts[1] = fingerWorkCosts[FINGER_COUNT - 2] = fwc_mult*30;
	fingerWorkCosts[2] = fingerWorkCosts[FINGER_COUNT - 3] = fwc_mult*20;
	fingerWorkCosts[3] = fingerWorkCosts[FINGER_COUNT - 4] = fwc_mult*20;
	fingerWorkCosts[4] = fingerWorkCosts[FINGER_COUNT - 5] = fwc_mult*20;
	
	/* All values are compounding. For example, say we jump over the home row
	 * on the index finger. The cost is 
     *     sameHand + rowChange + homeJump + homeJumpIndex.
     */

	distance =		            1;
	inRoll =	  	   i_mult*-40;
	outRoll =          o_mult*5;
	sameHand =		    sh_mult*5;
	sameFingerP =	  sf_mult*150;
	sameFingerR =	  sf_mult*140;
	sameFingerM =	  sf_mult*110;
	sameFingerI =	   sf_mult*90;
	sameFingerT =	  sf_mult*100;
	rowChangeDown =           0;
	rowChangeUp =             0;
	handWarp =		            0;
	handSmooth =	            0;
	homeJump =		            0;
	homeJumpIndex =           0;
	doubleJump =	            0; // Does not compound with homeJump. 
	ringJump =               40;
	toCenter =		           0;
	toOutside =		           0;
/*
	rowChangeDown =          10;
	rowChangeUp =            15;
	handWarp =		           25;
	handSmooth =	           -5;
	homeJump =		          100;
	homeJumpIndex =         -90;
	doubleJump =	          220; //Does not compound with homeJump.
	ringJump =               40;
	toCenter =		           30;
	toOutside =		           30;

don't work properly with thumb keys	
*/
	shiftCost =		          100;
	doubleShiftCost=        150;

}
