#include <string>

#include "Mutator.h"
#include "Mutation.h"
#include "Windows.h"

class 
BitFlip:public Mutator
{
    using Mutator::Mutator;
    public:
        Mutation *mutate(string);
};
