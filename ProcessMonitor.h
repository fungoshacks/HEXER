#include <string>
#include "windows.h"

using namespace std;

class 
ProcessMonitor
{
    private:
	string _call_string;
	bool _debugloop(PROCESS_INFORMATION *);
    public:
	ProcessMonitor(string);
        bool doesCrash(string);
	string getCallString();
};
