#include <string>
#include "windows.h"

using namespace std;

class ProcessMonitor;

class
CrashAnalyser
{

    private:
	static const string CDB_CALL;
	bool real_crash(string, int);
	void write_report(string);
	ProcessMonitor *_procMon;
    public:
	CrashAnalyser(ProcessMonitor *procMon);
        void checkcrash(string);

};
