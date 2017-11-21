#include "ByteInvert.h"

unsigned char ByteInvert::reverse(unsigned char b) {
	b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
	b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
	b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
	return b;
}


Mutation *
ByteInvert::mutate(string corpus)
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

	unsigned int repeat[10] = { 1, 10, 32, 64, 128, 256, 512, 8, 16, 1024 };


	if (f_mutation != NULL) {

		fseek(f_mutation, 0, SEEK_END);
		f_size = ftell(f_mutation);

		/* Hier dann fette hamming dist */
		for (int cycle = 0; cycle < 65; cycle++) {

			rewind(f_mutation);
			rand_offset = rand() % f_size + 1;
			unsigned char inverted;
			unsigned int occurances = repeat[rand() % 10]; // how many bytes do we invert?
			for (unsigned int occ = 0; occ < occurances; occ++) {
				fseek(f_mutation, rand_offset+occ, SEEK_SET);
				fread(&x, 1, 1, f_mutation);
				fseek(f_mutation, -1, SEEK_CUR);
				fread(&x, 1, 1, f_mutation);
				inverted = reverse(x);
				fwrite(&x, 1, 1, f_mutation);
			}
			
			}
		}
		fclose(f_mutation); //mic dropped.
		return mutation;
}
