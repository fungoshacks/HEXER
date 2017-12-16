#include "ProcessMonitor.h"

using namespace std;

ProcessMonitor::ProcessMonitor(string call_string, int ttl){
	_call_string = call_string;
	_ttl = ttl;
}

bool 
ProcessMonitor::doesCrash(string mutation)
{

    STARTUPINFO si = { 0 };
    PROCESS_INFORMATION pi = { 0 };
    bool crashed = false;
    LPSTR call_string_argv;
    string call_string_tmp = _call_string;

    call_string_tmp.append(" ");
    call_string_tmp.append(mutation);
    call_string_argv = strdup(call_string_tmp.c_str());

    if ( CreateProcess(NULL, call_string_argv, NULL, NULL, FALSE, DEBUG_PROCESS, NULL, NULL, &si, &pi) )
    {
	crashed = _debugloop(&pi);
    }


    DebugActiveProcessStop(pi.dwProcessId);
    TerminateProcess(pi.hProcess, 0);
    WaitForSingleObject(pi.hProcess, 500);

    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

    free(call_string_argv);

    return crashed;
}

bool
ProcessMonitor::_debugloop(PROCESS_INFORMATION *pi)
{

    DEBUG_EVENT event;
    DWORD dwStart = GetTickCount();

    while ( ( GetTickCount() ) - dwStart < _ttl ) {

	   if ( WaitForDebugEvent(&event, (DWORD)200) ) {

		   switch (event.dwDebugEventCode){

			   case LOAD_DLL_DEBUG_EVENT:
				   CloseHandle(event.u.LoadDll.hFile);
				   break;
			   case CREATE_PROCESS_DEBUG_EVENT:
				   CloseHandle(event.u.CreateProcessInfo.hFile);
				   break;
			   case EXCEPTION_DEBUG_EVENT:

				   /* Yeay */
				   if ( !event.u.Exception.dwFirstChance ) 
				   	   return true;
				   break;

			   default:
				   break;
		   }

		   ContinueDebugEvent(event.dwProcessId,
			   event.dwThreadId,
			   DBG_EXCEPTION_NOT_HANDLED);
	   }
    }

    return false;
}

string ProcessMonitor::getCallString()
{
    return _call_string;
}
