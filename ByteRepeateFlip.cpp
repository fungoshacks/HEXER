#include "ByteRepeateFlip.h"
#include <iostream>
#include <fstream>

Mutation *
ByteRepeateFlip::mutate(vector<char> corpus)
{

    Mutation *mutation;
    string mutation_path = "tmp\\RepeateFlipper";
    int rand_offset, rand_multiplier;
    static const int MAX_MULTIPLIER = 10;
    int xor_values[8] = {1,2,4,8,16,32,64,128};
    unsigned char multi_me;
    unsigned char flipped;
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
	    rand_multiplier = rand() % MAX_MULTIPLIER;
	    multi_me = mutation_buffer[rand_offset];

	    if ( rand_offset + rand_multiplier >= mutation_buffer.size() - MAX_MULTIPLIER ) {
		    continue;
	    }


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
    mutation_file.close();

    return mutation;
}

