#include "BitFlip.h"
#include <iostream>
#include <fstream>

Mutation *
BitFlip::mutate(string corpus)
{

    Mutation *mutation;
    string mutation_path = "tmp\\";
    static const int MAX_RANGE = 10;
    int rand_offset, rand_range;
    int xor_values[8] = {1,2,4,8,16,32,64,128};
    unsigned char flipme;

    /* Mutation object to return
     * set used corpus and the path to the mutation in the FS 
     */
    mutation_path = random_filename(mutation_path);
    mutation = new Mutation();
    mutation->setCorpus(corpus);
    mutation->setMutationPath(mutation_path);

    /* Read orig corpus in buffer */
    ifstream file(corpus, std::ios::binary | std::ios::ate);
    streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    vector<char> mutation_buffer(size);

    if ( file.read(mutation_buffer.data(), size )) {

	for ( int cycles = 0; cycles < 150; cycles++ ) {

		rand_offset = rand() % size;
		rand_range = rand() % MAX_RANGE;

		if ( rand_offset + rand_range >= size - MAX_RANGE ) 
		    continue;

		for ( int round = 0; round < rand_range; round++ ) {
		     flipme = mutation_buffer[rand_offset + round];
		     flipme ^= xor_values[rand() % 8];

		     mutation_buffer[rand_offset + round] = flipme;
		}

	}

	ofstream mutation_file(mutation->getMutationPath(), std::ios::out | std::ofstream::binary);
        copy(mutation_buffer.begin(), mutation_buffer.end(), ostreambuf_iterator<char>(mutation_file));
    }


    return mutation;
}
