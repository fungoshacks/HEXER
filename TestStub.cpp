#include <string>
#include "Mutation.h"
#include "Mutator.h"
#include "ByteDel.h"
#include "time.h"

int
main(int argc, char *argv[])
{
    //ProcessMonitor procMon("C:\\Program Files\\Adobe\\Acrobat Reader DC\\Reader\\AcroRd32.exe");
    //procMon.runProcess("C:\\Users\\IEUser\\Desktop\\test.pdf");

    srand(time(NULL));
    ByteDel deler(0);	
    Mutation *mut = deler.mutate("C:\\Users\\IEUser\\Desktop\\mutateme.txt");
    printf("%s\n", mut->getMutationPath().c_str());

    return 0;
}
