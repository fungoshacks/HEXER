#include <string>
#include "Mutation.h"
#include "Mutator.h"
#include "ByteRepeate.h"
#include "time.h"

int
main(int argc, char *argv[])
{
    //ProcessMonitor procMon("C:\\Program Files\\Adobe\\Acrobat Reader DC\\Reader\\AcroRd32.exe");
    //procMon.runProcess("C:\\Users\\IEUser\\Desktop\\test.pdf");

    srand(time(NULL));
    ByteRepeate repeater(0);	
    Mutation *mut = repeater.mutate("C:\\Users\\IEUser\\Desktop\\mutateme.txt");

    return 0;
}
