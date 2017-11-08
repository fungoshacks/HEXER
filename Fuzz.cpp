#include <string>
#include "stdafx.h"
#include "windows.h"
#include "Mutator.h"

using namespace std;

bool debugloop(HANDLE);
void check_crash(DEBUG_EVENT);
void usage();

int 
main(int argc, char *argv[])
{

    if ( argc != 3 )
        usage();

    printf("[*] Hexer started\n");

    LPSTR call_string = argv[1];
    LPSTR corpus_path = argv[2];
    LPSTR call_string_conc;  
    string mutation;

    STARTUPINFO si = { 0 };
    PROCESS_INFORMATION pi = { 0 };
    bool crashed = FALSE;

    Mutator mutator(corpus_path);
    mutator.init();

    while ( 1 ) {
	    mutation = mutator.mutation();
	    call_string_conc = (LPSTR)malloc(strlen(call_string) + strlen(mutation.c_str()) + 1);
	    strcpy(call_string_conc, call_string);
	    strcat(call_string_conc, " ");
	    strcat(call_string_conc, mutation.c_str());

	    if (CreateProcess(NULL, call_string_conc, NULL, NULL, TRUE, DEBUG_PROCESS, NULL, NULL, &si, &pi))
	    {
		crashed = debugloop(pi.hProcess);
	    }

	    if ( !crashed ) {
		remove(mutation.c_str());
	    }else {
		printf("Crashed junge\n");
                CopyFile(mutation.c_str(), "C:\\Users\\IEUser\\Desktop\\Crash.pdf", false);
	    }
	    free(call_string_conc);
    }

    printf("[!] Bye\n");
	
    
    return 0;
}

void 
check_crash(DEBUG_EVENT event){

	printf("DBG: Exception: %x, Addr: %p, FirstChance: %d\n", event.u.Exception.ExceptionRecord.ExceptionCode,
                event.u.Exception.ExceptionRecord.ExceptionAddress, event.u.Exception.dwFirstChance);

}


bool
debugloop(HANDLE p_handle)
{

    DEBUG_EVENT event;

    while ( TRUE ) {

	   if ( WaitForDebugEvent(&event, (DWORD)1000)){

		   switch (event.dwDebugEventCode){
			   
			   case EXCEPTION_DEBUG_EVENT:

				   if ( !event.u.Exception.dwFirstChance ) {
					   check_crash(event);
				   	   return TRUE;
				   }

				   break;

			   default:
				   // Idgaf
				   break;
		   }

		   ContinueDebugEvent(event.dwProcessId,
				   event.dwThreadId,
				   DBG_EXCEPTION_NOT_HANDLED);


	   }else {
		   printf("[!] Timeout\n");
		   TerminateProcess(p_handle, 0);
		   return FALSE;
	   }
    }
}

void 
usage()
{
    printf("Usage: Hexer.exe <call_string> <path_to_corpuses>");
    exit(0);
}
