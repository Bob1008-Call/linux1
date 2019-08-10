import os
import json

ID_PATH = "/data/czk/Cgroup/id.txt"
CONFIG_PATH = "/data/czk/Cgroup/configure.json"
OOM_CONTROL_PATH = "/sys/fs/cgroup/memory/g1/memory.oom_control"
PROCESS_KEYWORD = "mem"

class limit:
        fd_con = 1
        cresult = ''
        id_path = ID_PATH
        config_path = CONFIG_PATH
        process_keyword = PROCESS_KEYWORD
        oom_control_path = OOM_CONTROL_PATH

        def __init__(self):
                '''
                construct function
                '''
                with open(self.config_path,'r') as self.fd_con:
                        self.cresult=json.load(self.fd_con)

        def loadcpu_con(self):
                '''
                loading CPU configuration
                '''
                try:
                        os.system("cgset -r cpu.cfs_quota_us=%s g1" %self.cresult["CPU"]["cpu.cfs_quota_us"])
                        os.system("cgset -r cpu.cfs_period_us=%s g1" %self.cresult["CPU"]["cpu.cfs_quota_us"])
                except WindowsError:
                        print "cpu load system called error"
                else:
                        print "cpu load success"

        def loadmemory_con(self):
                '''
                loading MEMORY configuration
                '''
                try:
                        os.system("cgset -r memory.limit_in_bytes=%s g1" %self.cresult["MEMORY"]["memory.limit_in_bytes"])
                        os.system("sudo sh -c 'echo %s >> %s'" %(self.cresult["CONTROL"]["memory.oom_control"],self.oom_control_path))
                except WindowsError:
                        print "memory load system called error"
                else:
                        print "memory load success"

        def getpidtofile(self):
                '''
                get process_keyword PID and dup to file
                '''
                os.system("ps -ef|grep %s|grep -v 'grep'|awk '{print $2}' > %s" %(self.process_keyword,self.id_path))

        def limitmemory(self):
                '''add PID to process memory Cgroup'''
                try:
                        fd=open(self.id_path,'r')
                        for line in fd:
                                os.system("cgclassify -g memory:g1 %s" %line)
                except IOError:
                        print "Error(limitmemory): no such file or open failed"
                else:
                        print "limit memory operator success"
                        fd.close()

        def limitcpu(id_path):
                '''add PID to process cpu Cgroup'''
                try:
                        fd=open(id_path,'r')
                        for line in fd:
                                os.system("cgclassify -g cpu:g1 %s" %line)
                except IOError:
                        print "Error(limitcpu): no such file or open fail"
                else:
                        fd.close()
                        print "limit cpu operator success"

        def __del__():
            pass

if __name__ == '__main__':
        try:
                limit1 = limit()
                limit1.loadmemory_con()
                limit1.getpidtofile()
                limit1.limitmemory()
        except ZeroDivisionError as err:
                print('Handling run-time error:', err)
