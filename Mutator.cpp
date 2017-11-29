#include "Mutator.h"
#include "windows.h"

Mutator::Mutator(int cycles)
{
    _cycles = cycles;
}

string
Mutator::random_filename(string name)
{

    static const char values[25] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'n', 'p', 'q', 'r', 's','t', 'u', 'v', 'x', 'y', 'z'};
    char x;

    for (int i = 0; i < 16; ++i) {
	x = values[rand() % 25];
        name.append(&x, 1);
    }

    name.append(".pdf");
    return name;

}

