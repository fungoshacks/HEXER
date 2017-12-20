#include "NullKiller.h"

Mutation*
NullKiller::mutate(vector<char> corpus)
{

    Mutation *mutation;
    string mutation_path = "tmp\\NullKiller";
    int rand_offset, pos;

    mutation = new Mutation();
    //mutation->setCorpus(corpus);
    mutation->setMutationPath(random_filename(mutation_path));
    vector<char>::iterator it;
    vector<char> mutation_buffer = corpus;

    for ( int cycles = 0; cycles < _cycles; cycles++ ) {

	it = find( mutation_buffer.begin() + (rand() % mutation_buffer.size()), mutation_buffer.end(), 0x00);

	if ( it != mutation_buffer.end() ) {

	    *it = 0x41;
	    pos = it - mutation_buffer.begin() + 1;
	    for ( int i = 0; i < rand() % 30; i++ ) {
		mutation_buffer.insert(mutation_buffer.begin() + pos + i, 0x41);
	    }
	    
	}

    }

    ofstream mutation_file(mutation->getMutationPath(), std::ios::out | std::ofstream::binary);
    copy(mutation_buffer.begin(), mutation_buffer.end(), ostreambuf_iterator<char>(mutation_file));

    return mutation;

}
