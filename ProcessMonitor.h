#include <string>
#include "windows.h"

using namespace std;

class 
ProcessMonitor
{
    private:
	string _call_string;
	bool _debugloop(HANDLE);
    public:
	ProcessMonitor(string);
        bool runProcess(string);
};
