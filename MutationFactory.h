#pragma once
#include <string>
#include <vector>
#include "windows.h"
#include "Mutator.h"
#include "BitFlip.h"
#include "ByteReplace.h"

using namespace std;

class MutationFactory
{
    private:
        vector<string>  _corpus_paths;
        vector<Mutator *> _mutators = {new BitFlip(0), new ByteReplace(0)};
    public:
        MutationFactory(string);
        Mutation *new_mutation();
};
