#include "ByteReplace.h"


Mutation *
ByteReplace::mutate(string corpus)
{

	Mutation *mutation;
	FILE *f_mutation;
	int rand_offset, f_size = 0;
	unsigned char x = '\0';

	mutation = new Mutation();
	mutation->setCorpus(corpus);
	mutation->setMutationPath(tmpnam(NULL));

	/* Create a copy of corpus to mutate with */
	CopyFile(corpus.c_str(), mutation->getMutationPath().c_str(), false);
	f_mutation = fopen(mutation->getMutationPath().c_str(), "wb+"); //open binary

	int val[4] = { 0, 128, 196, 255};
	int repeat[10] = { 1, 10, 32, 64, 128, 256, 512, 8, 16, 1024 };


	if (f_mutation != NULL) {

		fseek(f_mutation, 0, SEEK_END);
		f_size = ftell(f_mutation);

		/* Hier dann fette hamming dist */
		for (int cycle = 0; cycle < 65; cycle++) {

			rewind(f_mutation);
			rand_offset = rand() % f_size + 1;
			fseek(f_mutation, rand_offset, SEEK_SET);
			fread(&x, 1, 1, f_mutation);
			fseek(f_mutation, -1, SEEK_CUR);
			x = val[rand() % 4]; //what byte?
			unsigned int repeat = rand() % 10; // how often do we append?
			vector<char> buffer; //build char array which we want to write
			for (unsigned int occ = 0; occ < repeat; occ++) {
				buffer.push_back(x);
			}
			fwrite(buffer.data(), sizeof(char), sizeof(buffer.data()), f_mutation); //drop that shit
		}
		fclose(f_mutation); //mic dropped.
	}

	return mutation;
}

