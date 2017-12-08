#include "ByteDel.h"
#include <iostream>
#include <fstream>

Mutation *
ByteDel::mutate(string corpus)
{

    Mutation *mutation;
    string mutation_path = "C:\\Users\\IEUser\\Desktop\\hexer\\tmp\\";
    int rand_offset, rand_range;
    const int MAX_RANGE = 10;

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
	    rand_range = rand() % MAX_RANGE;

	    if ( rand_offset + rand_range >= size - 5 ) {
		continue;
	    }

	    for ( int del_index = 0; del_index < rand_range; del_index ++ ) {

		mutation_buffer.erase(mutation_buffer.begin() + rand_offset );

	    }

	    
	    size = mutation_buffer.size();
	}

	ofstream mutation_file(mutation->getMutationPath(), std::ios::out | std::ofstream::binary);
	copy(mutation_buffer.begin(), mutation_buffer.end(), ostreambuf_iterator<char>(mutation_file));
    }

    return mutation;
}

