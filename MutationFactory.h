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
#include "ByteSpecial.h"

using namespace std;

class MutationFactory
{
    private:
        vector<vector<char>> *_corpuses;
        vector<Mutator *> _mutators;

    public:
        MutationFactory(vector<vector<char>> *, int);
        Mutation *new_mutation();
};
