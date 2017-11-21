#include "ProcessMonitor.h"
#include "MutationFactory.h"
#include "Mutation.h"
#include <thread>

void usage();
void work(string, string, int);
void check_crash(string, string);

int 
main(int argc, char *argv[])
{
    if ( argc < 3 )
        usage();

    string path_exe = "";
    string path_corpuses = "";
    const int NUM_THREADS = 10;
    std::thread threads[NUM_THREADS];

    path_exe = argv[1];
    path_corpuses = argv[2];
    //NUM_THREADS = atoi(argv[3]); //has to be const value

    for (unsigned int i = 0; i < NUM_THREADS; i++) {
	threads[i] = std::thread(work,path_exe, path_corpuses, i);
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
   MutationFactory mut_factory(path_corpuses);
   bool crashed = false;

   srand(seed);
   while ( true ) {

       mut_tmp = mut_factory.new_mutation();
       crashed = procMon.runProcess(mut_tmp->getMutationPath());

       if ( crashed ) {
           check_crash(path_exe, mut_tmp->getMutationPath());
	   crashed = false;
       } else {
           remove(mut_tmp->getMutationPath().c_str());
       }

       delete mut_tmp;

   }

}

void
check_crash(string path_exe, string path_mutation)
{

    STARTUPINFO si = { 0 };
    PROCESS_INFORMATION pi = { 0 };
    LPSTR call_string_argv;
    string python_call = "python crash_analyzer.py \"";

    call_string_argv = (LPSTR)malloc(strlen(python_call.c_str()) + strlen(path_exe.c_str()) +
		    strlen(path_mutation.c_str()) + 2);
    strcpy(call_string_argv, python_call.c_str());
    strcat(call_string_argv, path_exe.c_str());
    strcat(call_string_argv, "\" ");
    strcat(call_string_argv, path_mutation.c_str());

    printf("%s\n", call_string_argv);
    if (!CreateProcess(NULL, call_string_argv, NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))
    {
	printf("Unable to start crash checker\n");
	printf("%s\n", call_string_argv);
    	exit(1);
    }

}

void
usage()
{
    printf("Usage: Hexer <path executable> <path corpus dir>");
    exit(0);
}
