#include "Mutation.h"

void
Mutation::setCorpus(string corpus)
{
   _corpus = corpus; 
}

string
Mutation::getCorpus()
{
    return _corpus;
}


void
Mutation::setMutationPath(string mutation_path)
{
   _mutation_path = mutation_path;
}

string
Mutation::getMutationPath()
{
    return _mutation_path;
}

void
Mutation::setReport(string report)
{
   _report = report; 
}

string
Mutation::getReport()
{
   return _report;
}
