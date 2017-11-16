#pragma once
#include "Mutation.h"
#include <fstream>
#include <string>

class Mutator
{
    private:
        int _h_dist;
        float dist(string reference, string probe);
    public:
        Mutator();
        virtual Mutation mutate(string){return Mutation();};
};
