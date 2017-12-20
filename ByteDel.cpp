#include "ByteDel.h"
#include <iostream>
#include <fstream>

Mutation *
ByteDel::mutate(vector<char> corpus)
{

    Mutation *mutation;
    string mutation_path = "tmp\\ByteDeleter";
    int rand_offset, rand_range;
    const int MAX_RANGE = 10;
    vector<char> mutation_buffer = corpus;

    mutation_path = random_filename(mutation_path);
    mutation = new Mutation();
    //mutation->setCorpus(corpus);
    mutation->setMutationPath(mutation_path);

    for ( int cycles = 0; cycles < _cycles; cycles++ ) {

	    rand_offset = rand() % mutation_buffer.size();
	    rand_range  = rand() % MAX_RANGE;

	    if ( rand_offset + rand_range >= mutation_buffer.size() - 5 ) {
		continue;
	    }

	    for ( int del_index = 0; del_index < rand_range; del_index ++ ) {
		mutation_buffer.erase( mutation_buffer.begin() + rand_offset );
	    }

    }

    ofstream mutation_file(mutation->getMutationPath(), std::ios::out | std::ofstream::binary);
    copy(mutation_buffer.begin(), mutation_buffer.end(), ostreambuf_iterator<char>(mutation_file));
    

    return mutation;
}

