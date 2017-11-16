#include "MutationFactory.h"

MutationFactory::MutationFactory(string corpus_dir)
{
   _corpus_dir = corpus_dir;
   /* Create vector of corpuses */
   // corpus_paths = getAllFiles();
   //
   // _mutators = <Mutator1, Mutator2>
}

Mutation 
MutationFactory::new_mutation()
{
   Mutation mut;
   // mut = random.choice(_mutators).mutate(random.corpus);
   return mut;
}
