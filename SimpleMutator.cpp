#include "SimpleMutator.h"



SimpleMutator::SimpleMutator()
{
	/* For 8 bit lookup */
	for (int i = 0; i<256; i++) {
		POPCOUNT_LOT[i] = POPCOUNT_LOT[i / 2] + i & 1
	}

}


SimpleMutator::~SimpleMutator()
{
}
