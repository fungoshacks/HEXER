from winappdbg import Debug, Crash, win32, HexDump
from winappdbg.util import MemoryAddresses

import string
import random
import os

class Report:

    def __init__( self, event, crash, mutation_path ):

        self.event    = event
        self.crash    = crash
        self.mutation_path = mutation_path
        self.issue_id = ''.join(random.choice(string.ascii_uppercase +
            string.digits) for _ in range(6))
        self.f_report = open( self.issue_id + "_REPORT", "w")

    def writeReport( self ):

        ( exploitable, type_crash, info ) = self.crash.isExploitable()			
        self.f_report.write( "[General] \n\n" )
        self.f_report.write( "Exploitablity: %s\n" % exploitable )
        self.f_report.write( "Type: %s\n" % type_crash )
        self.f_report.write( "Info: %s\n" % info)
        self.f_report.write( "Details: %s\n" % self.crash.fullReport())
        self.f_report.write( "\n" * 2 )

        self.f_report.write( "[Crash analysis] \n\n" )
        self.f_report.write( "Code: %s\n" % self.__code())
        self.f_report.write( "Near Null: %s\n" % self.__near_null())
        self.f_report.write( "Location: %s\n" % self.__location())
        self.f_report.write( "Fault Address: %s\n" % self.__fault_address())
        self.f_report.write( "\n" * 2 )

        self.f_report.write( "[Stacktrace] \n\n" )
        self.f_report.write( self.__get_stack() ) 
        self.f_report.write( "\n" * 2 )

        self.f_report.close()

        os.rename(self.mutation_path, self.issue_id + "_CRASH")
        
        print "[!] Issue: " + self.issue_id

    def __get_stack( self ):
        
        stack = ""
        stList = self.__getStackTraceRelList(self.event.get_thread())
        if len(stList)>0:
            for ra in stList:
                lib = self.event.get_thread().get_process().get_module_at_address(ra)
                if lib != None:
                    stack += lib.get_label_at_address(ra) + " " + HexDump.address(ra, self.event.get_thread().get_process().get_bits()) + "\n"
                else:
                    stack += HexDump.address(ra, self.event.get_thread().get_process().get_bits()) + "\n"
                if stack == "":
                    stack = "NO_STACK"

        return stack

    def __getStackTraceRelList(self, thread):

        ret = []

        try:
            sp = thread.get_sp()
            ebp = thread.get_context(win32.CONTEXT_CONTROL)['Ebp']
            for x in xrange(0,10):
                addr = thread.get_process().peek_pointer(ebp + 4)
                if addr == None:
                    break
                ebp = thread.get_process().peek_pointer(ebp)
                lib = thread.get_process().get_module_at_address(addr)
                if thread.get_process().is_address_executable(addr) and lib != None:
                    ret.append(addr)
                else:
                    break
        except:
            pass
        return ret

    def __code ( self ):

        code = ""
        try:
            code = self.event.get_thread().disassemble( self.crash.pc, 0x10 ) [0][2]
        except:
            code = "None"

        return code

    def __near_null( self ) :

        nearNull = False

        if self.crash.faultAddress is None or \
                MemoryAddresses.align_address_to_page_start(self.crash.faultAddress) == 0:

            nearNull = True
        else:
            nearNull = False

        return nearNull

    def __location( self ):

        location = None
        lib = self.event.get_thread().get_process().get_module_at_address(self.crash.pc)

        if lib != None:
            location = lib.get_label_at_address(self.crash.pc)
        else:
            location = HexDump.address(self.crash.pc,
                    self.event.get_thread().get_process().get_bits())[-4:]
        
        return location

    def __fault_address( self ):

        faultAddr = None
        if self.crash.faultAddress == None:
            self.crash.faultAddress = 0
        faultAddr = HexDump.address(self.crash.faultAddress, 
                self.event.get_thread().get_process().get_bits())

        return faultAddr
