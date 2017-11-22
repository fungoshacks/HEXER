import time
import sys

from Report import Report
from winappdbg import Debug, Crash, win32, HexDump


EXCEPTIONS_CATCH = [
        win32.STATUS_ACCESS_VIOLATION,
        win32.STATUS_ILLEGAL_INSTRUCTION,
        win32.STATUS_ARRAY_BOUNDS_EXCEEDED
    ]

def event_handler(event):
    if event.get_event_code() == win32.EXCEPTION_DEBUG_EVENT and event.get_exception_code() != win32.STATUS_BREAKPOINT and (event.is_last_chance() or event.get_exception_code() in EXCEPTIONS_CATCH):
                crash = Crash ( event )
                return crash
    
    return None

def main(callstring, mutation):

    debugger = Debug( bKillOnExit = True )
    crash = None
    time_end   = time.time() + 5
    callargs = []
    callargs.append(callstring)
    callargs.append(mutation)

    proc = debugger.execv(callargs, bFollow = True)
    while time.time() < time_end:
        try:
            event = debugger.wait(1000)
            crash = event_handler(event)

            if crash:
                debugger.stop()
                break

            debugger.dispatch()
            debugger.cont()

        except WindowsError, e:
            if e.winerror in ( win32.ERROR_SEM_TIMEOUT, win32.WAIT_TIMEOUT ):
                continue
            else:
                raise

    if crash:
        report = Report( event, crash, mutation )
        report.writeReport()

main(sys.argv[1], sys.argv[2])
#main("C:\Program Files\Foxit Software\Foxit Reader\FoxitReader.exe", "C:\\Users\\IEUser\\Desktop\\crash.pdf")
