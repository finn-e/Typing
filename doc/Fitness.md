This document describes in depth how fitness is calculated.

##GENERAL
The program contains a list of digraphs and gives the frequency of each digraph. Here is the pseudocode for how a layout is scored. 

For each digraph: 
*	calculate the fitness for this individual digraph
*	multiply that by the digraph's frequency
*	add to total fitness

The program also has a list of characters, which are used to calculate finger travel distance.

The process of calculating the fitness for a single character or digraph requires calculating a number of independent factors.

###DISTANCE
This measure indicates how far one's fingers must travel, taking into account that some areas of the keyboard are more difficult to reach than others. For example, the bottom row counts as more effort than the top row.

###FINGER WORK
This adds a penalty when a finger is overloaded. The overload point depends on finger strength: for the index finger it is much higher than for the pinky. This does not add any points to the total fitness unless a finger's work exceeds a particular point, so it is possible for finger work to have a score of 0. The primary use of this measure is to prevent the pinky and ring finger from tiring.

###ROLLS
A roll is when adjacent keys in the same row are typed in succession. Inward rolls are favorable and outward rolls should be avoided.

###ROW CHANGE
When two keys are typed consecutively on the same hand and different rows. There are two special types of row change.

* _Hand Smooth_: When the two keys are on the index and middle finger where the middle finger is above the index. This is easier than other kinds of row change.
* _Hand Warp_: When the two keys are adjacent, and not Hand Smooth. This is harder than other kinds of row change.

###HOME JUMP
When two keys are typed consecutively on the same hand and jump over the home row. There are two special types of home jump.
* _Double Jump_: Jumping over at least two rows adds an additional penalty.
* _Hame Jump Index_: When one of the keys lies under the index finger on the bottom row, the cost is significantly reduced because such jumps are significantly easier.

###RING JUMP
When two keys are typed consecutively on the same hand where one is on the pinky and the other is on the middle finger. This move is considered to be difficult because of the ring finger's minimal dexterity.

###TO CENTER/TO OUTSIDE
When two keys are typed consecutively on the same hand where one is in the center column (or an outside column) and the other is on one of the main columns.
