#include "MutationFactory.h"

MutationFactory::MutationFactory(vector<vector<char>> *corpuses, int aggr)
{

    _corpuses = corpuses;

    //_mutators = {new BitFlip(aggr)};
    _mutators = {new BitFlip(aggr), new ByteRepeate(aggr),
	    new ByteRepeateFlip(aggr), new NullKiller(aggr), new ByteDel(aggr)};

}

Mutation *
MutationFactory::new_mutation()
{

   Mutation *new_mutation;
   Mutator *random_mutator = _mutators[rand() % _mutators.size()];
   vector<char> corpus = (*_corpuses)[rand() %  _corpuses->size()];

   new_mutation = random_mutator->mutate(corpus);

   return new_mutation;

}
