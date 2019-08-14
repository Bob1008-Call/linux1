#!/usr/bin/python
#coding=utf-8

import os
def getpidtofile():
  os.system("ps -ef|grep highcpu|awk '{print $2}' > ./kill.txt")

def killprocess():
  fd = open("./kill.txt")
  while True:
    pid = fd.readline()
    if pid:
      try:
        os.system("kill -9 %d" %int(pid))
        print "kill -9 %d" %pid
      except Exception:
        print "no process"
    else:
      break

if __name__ == '__main__':
  getpidtofile()
  killprocess()
