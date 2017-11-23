#include "ByteInvert.h"

unsigned char 
ByteInvert::reverse(unsigned char b) {
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
	int rand_offset, f_size;
	unsigned char x;

	mutation = new Mutation();
	mutation->setCorpus(corpus);
	mutation->setMutationPath(tmpnam(NULL));

	/* Create a copy of corpus to mutate with */
	CopyFile(corpus.c_str(), mutation->getMutationPath().c_str(), false);
	f_mutation = fopen(mutation->getMutationPath().c_str(), "r+");

	if (f_mutation != NULL) {

		fseek(f_mutation, 0, SEEK_END);
		f_size = ftell(f_mutation);

		for (int cycle = 0; cycle < 65; cycle++) {

			rewind(f_mutation);
			rand_offset = rand() % f_size;
			fseek(f_mutation, rand_offset, SEEK_SET);
			fread(&x, 1, 1, f_mutation);
			fseek(f_mutation, -1, SEEK_CUR);
			x = reverse(x);
			fwrite(&x, 1, 1, f_mutation);

		}

		fclose(f_mutation);

	}

	return mutation;
}
