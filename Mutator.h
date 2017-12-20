#pragma once
#include "Mutation.h"
#include <fstream>
#include <string>
#include <vector>

class Mutator
{
    public:
        Mutator(int cycles);
	virtual ~Mutator(){};
	string random_filename(string);
        virtual Mutation* mutate(vector<char>){return (new Mutation());};
        int _cycles;
};
