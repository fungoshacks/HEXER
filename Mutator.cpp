#include <vector>
#include "windows.h"
#include "stdafx.h"
#include "time.h"

#include "Mutator.h"

using namespace std;

Mutator :: Mutator(LPSTR corpus_path){
    _corpus_path = corpus_path;
    srand( (unsigned)time( NULL ) );
}

/*
 * Reads corpus names into _corpus_list
 * */
void Mutator :: init(){

   HANDLE hFind;
   WIN32_FIND_DATA data; 
   int cntr = 0;

   hFind = FindFirstFile(_corpus_path, &data);
   if (hFind != INVALID_HANDLE_VALUE) {
       do {
	  if ( cntr < 2 ) {
	      cntr++;
	      continue;
	   }
	   _corpus_list.push_back(string(_corpus_path).substr(0, 
				   strlen(_corpus_path)-1).append(data.cFileName));
       } while (FindNextFile(hFind, &data));
       FindClose(hFind);
   }

}

string Mutator :: mutation(){
   string corpus, mutation;
   corpus = _corpus_list[rand() % _corpus_list.size()];

   /* Create copy of corpus for mutation */
   mutation = tmpnam(NULL);
   CopyFile(corpus.c_str(), mutation.c_str(), false);

   printf("%s\n", mutation.c_str());

   FILE *f_mutation;
   int rand_offset, f_size;
   int xor_values[8] = {1, 2, 4, 8, 16, 32, 64, 128};
   unsigned char x;

   f_mutation = fopen(mutation.c_str(), "r+");
   if ( f_mutation != NULL ) {
       fseek(f_mutation, 0, SEEK_END);
       f_size =ftell(f_mutation);

       for (int i = 0; i < 65 ; i++){

	       rewind(f_mutation);
	       rand_offset = rand() % f_size;
	       //printf("%d\n", rand_offset);
	       fseek(f_mutation, rand_offset, SEEK_SET);

	       fread(&x, 1,1,f_mutation);
	       fseek(f_mutation, -1, SEEK_CUR);
	       //printf("%c\n", x);
	       x ^= xor_values[rand() % 8];
	       fwrite(&x, 1, 1, f_mutation);

       }

       fclose(f_mutation);
   }

   return mutation;
}
