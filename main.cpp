#include "ProcessMonitor.h"
#include "MutationFactory.h"

void usage();
void work(string, string);

int 
main(int argc, char *argv[])
{
    if ( argc < 3 )
        usage();

    string path_exe, path_corpuses;

    path_exe = argv[1];
    path_corpuses = argv[2];
    
    work(path_exe, path_corpuses);

    return 0;
}

/* Multi-Thread this */
void
work(string path_exe, string path_corpuses)
{
   ProcessMonitor procMon(path_exe);
   MutationFactory mut_factory(path_corpuses);
}

void
usage()
{
    printf("Usage: Hexer <path executable> <path corpus dir>");
    exit(0);
}
