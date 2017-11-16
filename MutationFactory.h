#pragma once
#include <string>
#include <vector>
#include "time.h"
#include "windows.h"
#include "Mutation.h"
#include "Mutator.h"
#include "BitFlip.h"

using namespace std;

class MutationFactory
{
    private:
        vector<string>  _corpus_paths;
        vector<Mutator> _mutators(BitFlip());
    public:
        MutationFactory(string);
        Mutation new_mutation();
};
