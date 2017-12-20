#include "BitFlip.h"
#include <iostream>
#include <fstream>

Mutation *
BitFlip::mutate(vector<char> corpus)
{

    Mutation *mutation;
    string mutation_path = "tmp\\Flipper";
    static const int MAX_RANGE = 10;
    int rand_offset, rand_range;
    int xor_values[8] = {1,2,4,8,16,32,64,128};
    unsigned char flipme;
    vector<char> mutation_buffer = corpus;

    /* Mutation object to return
     * set used corpus and the path to the mutation in the FS 
     */
    mutation_path = random_filename(mutation_path);
    mutation = new Mutation();
    //mutation->setCorpus(corpus);
    mutation->setMutationPath(mutation_path);

    for ( int cycles = 0; cycles < _cycles; cycles++ ) {

	rand_offset = rand() % mutation_buffer.size();
	rand_range = rand() % MAX_RANGE;

	if ( rand_offset + rand_range >= mutation_buffer.size() - MAX_RANGE ) {
	    continue;
	}

	for ( int round = 0; round < rand_range; round++ ) {
	     flipme = mutation_buffer[rand_offset + round];
	     flipme ^= xor_values[rand() % 8];

	     mutation_buffer[rand_offset + round] = flipme;
	}

    }

    ofstream mutation_file(mutation->getMutationPath(), std::ios::out | std::ofstream::binary);
    copy(mutation_buffer.begin(), mutation_buffer.end(), ostreambuf_iterator<char>(mutation_file));

    return mutation;
}
