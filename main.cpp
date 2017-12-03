#include "ProcessMonitor.h"
#include "MutationFactory.h"
#include "Mutation.h"
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
   MutationFactory mut_factory(path_corpuses);
   bool crashed = false;

   srand(time(NULL) + seed);
   while ( true ) {

	try{
	       mut_tmp = mut_factory.new_mutation();
	       crashed = procMon.runProcess(mut_tmp->getMutationPath());

	       if ( crashed ) {
		   check_crash(path_exe, mut_tmp->getMutationPath());
		   crashed = false;
	       } else {
		   remove(mut_tmp->getMutationPath().c_str());
	       }
	}catch(...){
	
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

    printf("[!] Issue with: %s\n", path_mutation.c_str());
    call_string_argv = (LPSTR)malloc(strlen(python_call.c_str()) + strlen(path_exe.c_str()) +
		    strlen(path_mutation.c_str()) + 2);
    strcpy(call_string_argv, python_call.c_str());
    strcat(call_string_argv, path_exe.c_str());
    strcat(call_string_argv, "\" ");
    strcat(call_string_argv, path_mutation.c_str());

    if (!CreateProcess(NULL, call_string_argv, NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))
    {
	   printf("Unable to start crash checker\n");
	   printf("%s\n", call_string_argv);
           exit(1);
    }

    Sleep(20);

    free(call_string_argv);

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
