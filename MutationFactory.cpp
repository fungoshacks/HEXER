#include "MutationFactory.h"

MutationFactory::MutationFactory(string corpus_dir)
{
   HANDLE hFind;
   WIN32_FIND_DATA data; 
   int cntr = 0;

   /* Get a list of all corpuses found in a corpus_dir */
   hFind = FindFirstFile(corpus_dir.c_str(), &data);
   if (hFind != INVALID_HANDLE_VALUE) {
       do {
          if ( cntr < 2 ) {
              cntr++;
              continue;
           }
           _corpus_paths.push_back(string(corpus_dir).substr(0, 
				   strlen(corpus_dir.c_str())-1).append(data.cFileName));
       } while (FindNextFile(hFind, &data));
       FindClose(hFind);
   }

}

Mutation *
MutationFactory::new_mutation()
{
   Mutation *mut;
   Mutator *mut_tmp = _mutators[0];
   mut = mut_tmp->mutate(_corpus_paths[rand() % _corpus_paths.size()]);

   return mut;
}
