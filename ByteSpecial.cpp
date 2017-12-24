#include "ByteSpecial.h"
#include <iostream>
#include <fstream>

Mutation *
ByteSpecial::mutate(vector<char> corpus)
{

    Mutation *mutation;
    string mutation_path = "tmp\\ByteSpecial";
    int rand_offset;
    vector<char> mutation_buffer = corpus;
    vector<unsigned char> chosen_values;
    static const vector<vector<unsigned char>> byte_values = {{0x00}, {0xFF}, {0xFE}, {0xFF,0xFF}, {0xFF,0xFE}, {0xFE,0xFF}, {0xFF,0xFF,0xFF,0xFF}, {0xFF,0xFF,0xFF,0xFE}, {0xFE,0xFF,0xFF,0xFF}, {0x7F}, {0x7E}, {0x7F,0xFF}, {0x7F,0xFE}, {0xFF,0x7F}, {0xFE,0x7F}, {0x7F,0xFF,0xFF,0xFF}, {0x7F,0xFF,0xFF,0xFE}, {0xFF,0xFF,0xFF,0x7F}, {0xFE,0xFF,0xFF,0x7F}};

    mutation_path = random_filename(mutation_path);
    mutation = new Mutation();
    mutation->setMutationPath(mutation_path);

    for ( int cycles = 0; cycles < _cycles; cycles++ ) {
	chosen_values = byte_values[rand() % byte_values.size()];
	rand_offset = rand() % mutation_buffer.size();
	for ( int i = 0; i < chosen_values.size(); i++ ) {
	    mutation_buffer[rand_offset + i] = chosen_values[i];
	}

    }

    ofstream mutation_file(mutation->getMutationPath(), std::ios::out | std::ofstream::binary);
    copy(mutation_buffer.begin(), mutation_buffer.end(), ostreambuf_iterator<char>(mutation_file));
    mutation_file.close();

    return mutation;
}
