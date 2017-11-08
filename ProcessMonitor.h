#include <string>

using namespace std;

class 
ProcessMonitor
{
    private:
	string _call_string;
    public:
	ProcessMonitor(string);
        bool runProcess(string);
};
