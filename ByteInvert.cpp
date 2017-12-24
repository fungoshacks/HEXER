#include "ByteInvert.h"

unsigned char 
ByteInvert::reverse(unsigned char b) {
	b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
	b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
	b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
	return b;
}


Mutation *
ByteInvert::mutate(vector<char> corpus)
{

    Mutation *mutation;
    string mutation_path = "tmp\\Inverter";
    static const int MAX_RANGE = 10;
    int rand_offset, rand_range;
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

        flipme = mutation_buffer[rand_offset];
	flipme = reverse(flipme);

	if ( rand_offset + rand_range >= mutation_buffer.size() - MAX_RANGE ) {
	    continue;
	}

	for ( int round = 0; round < rand_range; round++ ) {
	     flipme = mutation_buffer[rand_offset + round];
	     flipme = reverse(flipme);

	     mutation_buffer[rand_offset + round] = flipme;
	}
    }

    ofstream mutation_file(mutation->getMutationPath(), std::ios::out | std::ofstream::binary);
    copy(mutation_buffer.begin(), mutation_buffer.end(), ostreambuf_iterator<char>(mutation_file));
    mutation_file.close();

    return mutation;

}
