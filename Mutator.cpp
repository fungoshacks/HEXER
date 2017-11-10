#include "Mutator.h"
int POPCOUNT_LOT[256]

Mutator::Mutator(){
 /* For 8 bit lookup */
for (int i=0; i<256; i++) {
    POPCOUNT_LOT[i] = POPCOUNT_LOT[i/2] + i&1
}


}
