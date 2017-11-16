#pragma once
#include <string>

using namespace std;

class
Mutation
{
    private:
        string _corpus;
        string _mutation_path;
        string _report;

    public:
        void setCorpus(string);
        string getCorpus();
        void setMutationPath(string);
        string getMutationPath();
        void setReport(string);
        string getReport(); 
};
