#include <string>
#include "ProcessMonitor.h"

int
main(int argc, char *argv[])
{
    ProcessMonitor procMon("C:\\Program Files\\Adobe\\Acrobat Reader DC\\Reader\\AcroRd32.exe");
    procMon.runProcess("C:\\Users\\IEUser\\Desktop\\test.pdf");
    return 0;
}
