#pragma once
#include <string>
#include "Mutator.h"
#include "Mutation.h"
#include "Windows.h"
#include <fstream>
#include <stdlib.h> 
#include <vector>

class ByteInvert :
	public Mutator
{
public:
	using Mutator::Mutator;
	Mutation *mutate(vector<char>);
	unsigned char reverse(unsigned char);
};

