#include "ProcessMonitor.h"
#include "MutationFactory.h"
#include "Mutation.h"
#include "CrashAnalyser.h"
#include "time.h"
#include <thread>
#include "windows.h"

void usage();
void logo();
void work(string, string, int);
void check_crash(string, string);

int 
main(int argc, char *argv[])
{

    if ( argc < 3 )
        usage();

    const int NUM_THREADS = 10;
    string path_exe = argv[1];
    string path_corpuses = argv[2];
    std::thread threads[NUM_THREADS];
    //NUM_THREADS = atoi(argv[3]); //has to be const value
    logo();

    for (unsigned int i = 0; i < NUM_THREADS; i++) {
	threads[i] = std::thread(work,path_exe, path_corpuses, i * 1337);
    }

    for (unsigned int i = 0; i < NUM_THREADS; i++) {
	threads[i].join();
    }
    
    return 0;
}

/* Multi-Thread this */
void
work(string path_exe, string path_corpuses, int seed)
{

   Mutation *mut_tmp;
   ProcessMonitor procMon(path_exe);
   CrashAnalyser crashAnalyser(&procMon);
   MutationFactory mut_factory(path_corpuses);
   bool crashed = false;

   srand(time(NULL) + seed);
   while ( true ) {

	try{
	       mut_tmp = mut_factory.new_mutation();
	       if ( procMon.doesCrash(mut_tmp->getMutationPath()) ) {

		       crashAnalyser.checkcrash(mut_tmp->getMutationPath());
			
	       } else {
		   remove(mut_tmp->getMutationPath().c_str());
	       }
	}catch(...){
	    printf("[--] Worker error");	
	}

       delete mut_tmp;

   }

}

void
logo()
{
    printf(" _   _  _______   __ ___________\n");
    printf("| | | ||  ___\\ \\ / /|  ___| ___ \n");
    printf("| |_| || |__  \\ V / | |__ | |_/ /\n");
    printf("|  _  ||  __| /   \\ |  __||    /\n");
    printf("| | | || |___/ /^\\ \\| |___| |\\ \\ \n");
    printf("\\_| |_/\\____/\\/   \\/\\____/\\_| \\_|\n");
    printf("v2223\n");
}

void
usage()
{
    printf("Usage: Hexer <path executable> <path corpus dir>");
    exit(0);
}
