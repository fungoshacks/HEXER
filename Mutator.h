#pragma once
#include "Mutation.h"
#include <fstream>
#include <String>
class Mutator
{
    private:
        int _h_dist;
        float dist(string reference, string probe);
    public:
        Mutator();
        virtual Mutation mutate(string);
        void setH_dist(int);
};
