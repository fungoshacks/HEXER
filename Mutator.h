#pragma once
#include "Mutation.h"
#include <fstream>
#include <string>

class Mutator
{
    private:
        int _cycles;
    public:
        Mutator(int cycles);
	virtual ~Mutator(){};
	string random_filename(string);
        virtual Mutation* mutate(string){return (new Mutation());};
};
