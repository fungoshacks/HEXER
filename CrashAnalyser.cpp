#include "CrashAnalyser.h"
#include "ProcessMonitor.h"

const string CrashAnalyser::CDB_CALL = "cdb -g -c Q";

CrashAnalyser::CrashAnalyser(ProcessMonitor *procMon){
    _procMon = procMon;
}

bool
CrashAnalyser::real_crash( string mutation, int rec )
{
   
   if ( _procMon->doesCrash(mutation) ) {

	if ( rec == 3 ) {
	    return true;
	}

        return real_crash( mutation, rec + 1 );

   }

   return false; 
}	

void
CrashAnalyser::checkcrash( string mutation )
{
    if ( real_crash ( mutation, 0 ) ) {

	printf("[++] Issue with: %s\n", mutation.c_str());	
	write_report(mutation);

    } else { 
	printf("[-] False - Positive :(\n");
    } 
}

void
CrashAnalyser::write_report( string mutation ) 
{

    STARTUPINFO si = { 0 };
    PROCESS_INFORMATION pi = { 0 };
    LPSTR call_string_windows;
    string call_string_debug;
    
    call_string_debug.append(CDB_CALL);
    call_string_debug.append(_procMon->getCallString());
    call_string_debug.append(" ");
    call_string_debug.append(mutation);
    call_string_debug.append(" > ");
    call_string_debug.append(mutation);
    call_string_debug.append(".report");

    call_string_windows = strdup(call_string_debug.c_str());

	
    if (!CreateProcess(NULL, call_string_windows, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi))
    {
	printf("[-] Failed to start CDB :(\n");
	exit(1);
    }

    rename(mutation.c_str(), mutation.append(".issue").c_str());
    Sleep(10);
    TerminateProcess(pi.hProcess, 0);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    free( call_string_windows);

    printf("[+] Written Report\n");

}
