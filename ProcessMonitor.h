#include <string>
#include "windows.h"

using namespace std;

class 
ProcessMonitor
{
    private:
	string _call_string;
	int _ttl;
	bool _debugloop(PROCESS_INFORMATION *);
    public:
	ProcessMonitor(string, int);
        bool doesCrash(string);
	string getCallString();
};
