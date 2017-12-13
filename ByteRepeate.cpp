#include "ByteRepeate.h"
#include <iostream>
#include <fstream>

Mutation *
ByteRepeate::mutate(string corpus)
{

    Mutation *mutation;
    string mutation_path = "tmp\\";
    int rand_offset, rand_multiplier;
    static const int MAX_MULTIPLIER = 10;
    unsigned char multi_me;

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

        for ( int cycles = 0; cycles < 250; cycles++ ) {

	    rand_offset = rand() % size;
	    rand_multiplier = rand() % MAX_MULTIPLIER;
	    multi_me = mutation_buffer[rand_offset];

	    if ( rand_offset + rand_multiplier >= size - MAX_MULTIPLIER )
		    continue;

	    for (int round = 0; round < rand_multiplier; round++) {
	        mutation_buffer.insert(mutation_buffer.begin() + rand_offset, multi_me); 
	    }

	}

	ofstream mutation_file(mutation->getMutationPath(), std::ios::out | std::ofstream::binary);
	copy(mutation_buffer.begin(), mutation_buffer.end(), ostreambuf_iterator<char>(mutation_file));
    }

    return mutation;
}

