#include "BitFlip.h"

Mutation *
BitFlip::mutate(string corpus)
{

    Mutation *mutation;
    FILE *f_mutation;
    int rand_offset, f_size;
    int xor_values[8] = {1,2,4,8,16,32,64,128};
    unsigned char x;

    mutation = new Mutation();
    mutation->setCorpus(corpus);
    mutation->setMutationPath(tmpnam(NULL));

    /* Create a copy of corpus to mutate with */
    CopyFile(corpus.c_str(), mutation->getMutationPath().c_str(), false);
    f_mutation = fopen(mutation->getMutationPath().c_str(), "r+");

    if ( f_mutation != NULL ) {

        fseek(f_mutation, 0, SEEK_END);
        f_size = ftell(f_mutation);

        /* Hier dann fette hamming dist */
        for ( int cycle = 0; cycle < 65; cycle ++ ) {

            rewind(f_mutation);
            rand_offset = rand() % f_size + 1;
            fseek(f_mutation, rand_offset, SEEK_SET);
            fread(&x, 1,1, f_mutation);
            fseek(f_mutation, -1, SEEK_CUR);
            x ^= xor_values[rand() % 8];
            fwrite(&x, 1,1,f_mutation);

        }

        fclose(f_mutation);

    }

    return mutation;
}
