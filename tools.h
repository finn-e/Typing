/*
 *  tools.h
 *  Typing
 *
 *  Created by Michael Dickens on 8/7/09.
 *
 */

#ifndef __TOOLS_H__
#define __TOOLS_H__
 
#include "values.h"

#define streq(str1, str2) (strcmp(str1, str2) == 0)
#define streqn(str1, str2, n) (strncmp(str1, str2, n) == 0)

#define ASCII_SHIFT 14
 
#define DI_LEN_MAX 5000
#define MON_LEN_MAX 200

#define ERROR_RATE_PERCENT 2

#define MONOGRAPHFILE "data/allChars.txt"
#define DIGRAPH_FILE "data/allDigraphs.txt"

/* Global variable declarations */

int64_t totalMon;
int64_t totalDi;
int monLen, diLen, triLen;

struct Monograph {
    char key;
    int64_t value;
};

struct Digraph {
    char key[2];
    int64_t value;
};

struct NGraph {
    char *key;
    int64_t value;
};

struct Monograph monographs[MON_LEN_MAX];
struct Digraph digraphs[DI_LEN_MAX];

/* Constant declarations */

#define LEFT 0
#define RIGHT 1

#define PINKY 0
#define RING 1
#define MIDDLE 2
#define INDEX 3
#define THUMB 4

/* Reduces monValues and diValues so as to prevent integer overflow. */
#define DIVISOR 100

/* These are guaranteed to hold a standard QWERTY layout. */
//#define DEFAULT_KEYBOARD_30 "qwer\ttyuiopasdfghjklzxcvbnm; \nQWER\tTYUIOPASDFGHJKLZXCVBNM, \n"
//#define DEFAULT_KEYBOARD_30 "xyouvfldncaie \nmhtsrk,\tg\bqjpbwXYOUVFLDNCAIE \nMHTSRK?\tG\bQJPBW"
#define DEFAULT_KEYBOARD_30       "',.pyrlcmfaoeiudhtns;qzjkxgwbv\"?!PYRLCMFAOEIUDHTNS:QZJKXGWBV"
#define DEFAULT_KEYBOARD_NOT      "qypcjkldfwinerbavhtsu,./;x ozmg[]QYPCJKLDFWINERBAVHTSU?!\\:X OZMG{}"
#define DEFAULT_KEYBOARD_STANDARD " 1234567890"
#define DEFAULT_KEYBOARD_NOKI     "qwertyuiopasdfghjklzxcvbnm \bQWERTYUIOPASDFGHJKLZXCVBNM \b"
#define DEFAULT_KEYBOARD_KINESIS  "1234567890-\tqwertyuiop=asdfghjkl;'zxcvbnm,./`\\[]\n !@#\b%^&*()_\tQWERTYUIOP+ASDFGHJKL:\"ZXCVBNM<>?~|{}\n "
#define DEFAULT_KEYBOARD_TRIM     "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM"
//#dejfine DEFAULT_KEYBOARD_GIGI   "/yqz\t*jkx=(v, \n{b\"e)%~&;gpou^fndlcai._}mhtsr-:w`"
//#define DEFAULT_KEYBOARD_GIGI "\byou~qw\terti p\n{}^asdfghjk_l;\"zxcvbnm,./()-=#&*@"
#define DEFAULT_KEYBOARD_GIGI     "etaoinsrhldcumf gpwybvkxjqzETAOINSRHLDCUMF GPWYBVKXJQZ"
#define DEFAULT_KEYBOARD_MINI     ",mwlz.qudftaiorshnxkcy';jpgb\b \t\nev<MWLZ>QUDFTAIORSHNXKCY\":JPGB\b \t\nEV"
#define DEFAULT_KEYBOARD_LAPTOP   ",\bou\t(q)fndlcjaie \n{z}mhtsrpgkxyv./=\"bw?\bOU\t(Q)FNDLCJAIE \n{Z}MHTSRPGKXYV!\\='BW"
#define DEFAULT_KEYBOARD_ADD      "qlucpmw~anishtro``ygfd``QLUCPMW~ANISHTRO``YGFD``"
#define DEFAULT_KEYBOARD_BADHD    "qldumfgbrenihtscpwyvkxjz ,aoQLDUMFGBRENIHTSCPWYVKXJZ ,AO"
//#define DEFAULT_KEYBOARD_BADHD    "maldg,inorhtscufype MALDG?INORHTSCUFYPE "
//#define DEFAULT_KEYBOARD_GODOT    ";dcumfgpwyaion ehtsrbv,xkjqzl\b\t\n:/'\\][=-<@#$%```````?DCUMFGPWYAION EHTSRBV.XKJQZL\b\t\n!>\"|}{+_)(*&^```````"
#define DEFAULT_KEYBOARD_GODOT    "qlucpmwsion ehtarygfdbvkxjz,./;QLUCPMWSION EHTARYGFDBVKXJZ?!*:"
//2345678901234567890123456789012345678901234567890123456789
#define DEFAULT_KEYBOARD_GIBO     "ldhcoumgpwy ,iaestrnbfvkxjqzLDHCOUMGPWY ,IAESTRNBFVKXJQZ"
#define DEFAULT_KEYBOARD_HOMU     " etaoinsrhldcumfgpwybvkxjqz ETAOINSRHLDCUMFGPWYBVKXJQZ"
//#define DEFAULT_KEYBOARD_HOCUS ",youdnglaie\t fthrs.cp\n?:+\\xkmv'-$@_zwbjq!=`|/YOUDNGLAIE\t\bFTHRS;CP\n~)(\"XKMV%}{~`ZWBJQ^*`&88"
#define DEFAULT_KEYBOARD_HOCUS    "cfd,unilgstherpmywbvkxjqoa zCFD?UNILGSTHERPMYWBVKXJQOA Z"
#define DEFAULT_KEYBOARD_GEORGI   "ldmfgpwybvkxjuserqztnich aoLDMFGPWYBVKXJUSERQZTNICH AO"
#define DEFAULT_KEYBOARD_SNOTDOG  " etaoinsrhldcumfgpwybvkxjqz\b\t\n,; ETAOINSRHLDCUMFGPWYBVKXJQZ\b\t\n,;"
//#define DEFAULT_KEYBOARD_RUNNER " eta\toins\b\nrhldcumfgpywbvkxjqz,.-)(;=/{}&\"~%@ ETA\tOINS\b\nRHLDCUMFGPYWBVKXJQZ?!+><:*\\[]|'`#$"
#define DEFAULT_KEYBOARD_TWENTYSEVEN  "idcmfgpqlthe arnsuwybvokxjzIDCMFGPQLTHE ARNSUWYBVOKXJZ"
#define DEFAULT_KEYBOARD_ELEVEN  "atlin oresuATLIN ORESU"
#define DEFAULT_KEYBOARD_EIGHTEEN  " etaoinsrhldcumfgq ETAOINSRHLDCUMFGQ"
#define DEFAULT_KEYBOARD_NINETEEN  "hdcmafgpqlint oresuLDCMAFGPQLINT ORESU"
#define DEFAULT_KEYBOARD_RUNNER   "``oui fdslphea`mtnrckqxjzvgywb,.-)(;=/{}&\"~%@``OUI\bFDSLPHEA`MTNRCKQXJZVGYWB?!+><:*\\[]|'`#$"

#define CHECK_FILE_FOR_NULL(file, filename) \
	if ((file) == NULL) { \
		fprintf(stderr, "Unable to open file: %s\n", (filename)); \
		return 1; \
	}
char keysToInclude[200];

typedef struct {
	char layout[KSIZE_MAX + 1]; /* The one extra character is set to '\0' so 
								(layout) can be treated as a string. */
	char shiftedLayout[KSIZE_MAX + 1];
	int64_t fingerUsage[FINGER_COUNT];
	int64_t fitness;
	int64_t distance;
	int64_t fingerWork;
	int64_t inRoll;
	int64_t outRoll;
	int64_t sameHand;
	int64_t sameFinger;
	int64_t rowChange;
	int64_t homeJump;
	int64_t ringJump;
	int64_t toCenter;
	int64_t toOutside;
} Keyboard;


Keyboard nilKeyboard;

void copyArray(int dest[], int src[], int length);
void printTime(time_t start);

int initData();
void initKeyboardData();
int initTypingData();
int compileTypingData(char *outfileName, const char *filenames[], 
		int multipliers[], int length, int unit, int max);
int sortTypingData(char **keys, int *values, int left, int right);
int convertEscapeChar(int c);

/* Sort by values from highest to lowest.
 */
int cmpDigraphsByValue(const void *one, const void *two);
int cmpMonographsByValue(const void *one, const void *two);
int cmpNGraphsByValue(const void *one, const void *two);

int sortMonographs(char keys[], int64_t values[], int left, int right);

struct VarInfo {
    const char *name; /* The name of the variable. */
    int *addr; /* A pointer to the variable itself. */
    const char *description;
};

#define VARIABLES_MAX_LEN 100
struct VarInfo variables[VARIABLES_MAX_LEN];
int variablesLength;

void initVariables();
int getValue(const char *name);
int setValue(char *str);

#define isBracket(c) (getMatchingBracket(c) != 0)
char getMatchingBracket(char c);

int keepShiftPair(char c);


char qwerty[31];

/* For each key, indicates which hand (LEFT or RIGHT) is responsible for typing 
 * that key.
 */
int hand[KSIZE_MAX];

/* For each key, indicates which finger (PINKY, RING, MIDDLE or INDEX) is 
 * responsible for typing that key.
 */
int finger[KSIZE_MAX];

/* Where 0 is pinky, -1 is left of pinky, ..., 3 is index, 4 is right of index.
 * Anything greater than 4 is thumb.
 */
int column[KSIZE_MAX];

/* For each key, indicates which row that key lies on. The top row is 0, 
 * the row below it is 1, the row below that is 2, etc.
 */
int row[KSIZE_MAX];

/* Indicates which row is the home row.
 */
int homeRow;

/* Indicates the index of the first number in the layout, assuming 
 * keepNumbers is TRUE.
 */
int firstNumberIndex;

/* For each key, indicates whether that key requires a reach to the center.
 */
int isCenter[KSIZE_MAX];

/* For each key, indicates whether that key requires a reach to the outside.
 */
int isOutside[KSIZE_MAX];

/* For each key, indicates whether that key requires a reach to the center OR 
 * a reach to the outside. This one is produced automatically from isCenter[] 
 * and isOutside[].
 */
int isCenterOrOutside[KSIZE_MAX];

int isAlpha[KSIZE_MAX];
// Denote if key is for alphas, so that alphas and others can be shuffled separate.

/* For each key, indicates whether that key should be printed. Any place-holder 
 * key that does not actually exist on the keyboard should not be printed.
 */
int printable[KSIZE_MAX];

/* Lookup tables for calcRowChange(). Each row and column represents a finger.
 */
int rowChangeTableUp[5][5];
int rowChangeTableDown[5][5];


#endif
