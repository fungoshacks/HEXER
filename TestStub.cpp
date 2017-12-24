#include <string>
#include "Mutation.h"
#include "Mutator.h"
#include "ByteSpecial.h"
#include "time.h"
#include <iostream>
#include <fstream>

int
main(int argc, char *argv[])
{

    ifstream file("C:\\Users\\IEUser\\Desktop\\mutateme.txt", std::ios::binary | std::ios::ate);
    streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    vector<char> corpus_buffer(size);

    if ( file.read(corpus_buffer.data(), size )) {

	 srand(time(NULL));
	 ByteSpecial specer(1);	
	 Mutation *mut = specer.mutate(corpus_buffer);
	 printf("%s\n", mut->getMutationPath().c_str());

    }




    return 0;
}
