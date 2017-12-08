#pragma once
#include <string>
#include <vector>
#include "windows.h"
#include "Mutator.h"
#include "BitFlip.h"
#include "ByteRepeate.h"
#include "ByteInvert.h"
#include "ByteRepeateFlip.h"
#include "ByteDel.h"
#include "NullKiller.h"

using namespace std;

class MutationFactory
{
    private:
        vector<string>  _corpus_paths;
        vector<Mutator *> _mutators = {new BitFlip(0), new ByteRepeateFlip(0),  new ByteDel(0), new ByteRepeate(0), new NullKiller(0)};

    public:
        MutationFactory(string);
        Mutation *new_mutation();
};
