#pragma once
#include "Mutation.h"
#include <fstream>
#include <String>
class Mutator
{
    public:
	Mutator();
	virtual Mutation mutate();
	float dist(string reference, string probe);
};
