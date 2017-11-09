#pragma once
#include <string>

using namespace std;

class
Mutation
{
    public:
	string getCorpus();
	string getMutationPath();
	string getReport(); // Aus dem Report sollten wir auch noch ne Klasse machen, damit wir da elegant report.create_report() machen koennen.
};
