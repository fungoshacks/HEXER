#ifndef MUTATOR_H
#define MUTATOR_H

#include <vector>
#include "windows.h"
#include "time.h"
#include "stdafx.h"

class Mutator
{

	private :
    	     LPSTR _corpus_path;
	     std::vector<std::string> _corpus_list;

	public :
	     Mutator(LPSTR);
	     void init(void);
	     std::string mutation();
};

#endif
