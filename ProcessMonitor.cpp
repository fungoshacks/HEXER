#include "ProcessMonitor.h"

using namespace std;

ProcessMonitor::ProcessMonitor(string call_string){
	_call_string = call_string;
}

bool 
ProcessMonitor::runProcess(string mutation)
{

    STARTUPINFO si = { 0 };
    PROCESS_INFORMATION pi = { 0 };
    bool crashed = false;
    LPSTR call_string_argv;

    call_string_argv = (LPSTR)malloc(strlen(_call_string.c_str()) + strlen(mutation.c_str()) + 1);
    strcpy(call_string_argv, _call_string.c_str());
    strcat(call_string_argv, " ");
    strcat(call_string_argv, mutation.c_str());
    
    if (CreateProcess(NULL, call_string_argv, NULL, NULL, TRUE, DEBUG_PROCESS, NULL, NULL, &si, &pi))
    {
	crashed = _debugloop(pi.hProcess);
    }

    free(call_string_argv);

    return crashed;
}

bool
ProcessMonitor::_debugloop(HANDLE p_handle)
{

    DEBUG_EVENT event;

    while ( TRUE ) {

	   if ( WaitForDebugEvent(&event, (DWORD)1000)){

		   switch (event.dwDebugEventCode){
			   
			   case EXCEPTION_DEBUG_EVENT:

				   if ( !event.u.Exception.dwFirstChance ) {
					   // Gekracht
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
        
    return false;
}

