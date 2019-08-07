#!/usr/bin/python
#coding=utf-8

import os

class limit:
    '''
    resource management
    '''
    ID_PATH = "/home/caozongkai/git/linux1/Cgroup/id.txt"
    PROCESS_TYPE="python"

    def getpidtofile(self):
        os.system("ps -ef|grep %s|grep -v 'grep'| awk '{print $2}' > %s" %(self.PROCESS_TYPE,self.ID_PATH))

    def limitmemory(self):
        try:
            fd=open(self.ID_PATH,'r')
            for line in fd:
                os.system("cgclassify -g memory:g1 %s" %line)
        except IOError:
            print "Error: no such file or open fail"
        else:
            print "operator success"
            fd.close()

    def limitcpu(ID_PATH):
        try:
            fd=open(ID_PATH,'r')
            for line in fd:
                os.system("cgclassify -g cpu:g1 %s" %line)
        except IOError:
            print "Error: no such file or open fail"
        else:
            print "operator success"
            fd.close()

class decetionstandard:
    '''
    Detection exceeded the StandardError
    '''


if __name__ == '__main__':
    try:
        pass
    except ZeroDivisionError as err:
        print('Handling run-time error:', err)
