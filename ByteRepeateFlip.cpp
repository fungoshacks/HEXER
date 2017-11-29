#include "ByteRepeateFlip.h"
#include <iostream>
#include <fstream>

Mutation *
ByteRepeateFlip::mutate(string corpus)
{

    Mutation *mutation;
    string mutation_path = "tmp\\rflip";
    int rand_offset, rand_multiplier;
    static const int MAX_MULTIPLIER = 7;
    int xor_values[8] = {1,2,4,8,16,32,64,128};
    unsigned char multi_me;
    unsigned char flipped;

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

        for ( int cycles = 0; cycles < 100; cycles++ ) {

	    rand_offset = rand() % size;
	    rand_multiplier = rand() % MAX_MULTIPLIER;
	    multi_me = mutation_buffer[rand_offset];

	    for (int round = 0; round < rand_multiplier; round++) {
		if ( rand() % 2 == 0 ) {
	            mutation_buffer.insert(mutation_buffer.begin() + rand_offset + round, multi_me); 
		} else {
		    flipped = multi_me ^ xor_values[rand() % 8];
	            mutation_buffer.insert(mutation_buffer.begin() + rand_offset + round, flipped); 
		}
	    }

	}

	ofstream mutation_file(mutation->getMutationPath(), std::ios::out | std::ofstream::binary);
	copy(mutation_buffer.begin(), mutation_buffer.end(), ostreambuf_iterator<char>(mutation_file));
    }

    return mutation;
}

