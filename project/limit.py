import os
import json
import time

ID_PATH = "/data/czk/project/id.txt"
CONFIG_PATH = "/data/czk/project/con.json"
PROCESS_KEYWORD = "highcpu"
class limit:
  fd_con = 1
  cresult = ''
  id_path = ID_PATH
  config_path = CONFIG_PATH
  process_keyword = PROCESS_KEYWORD

  def __init__(self):
    '''
    construct function
    '''
    with open(self.config_path,'r') as self.fd_con:
      self.cresult=json.load(self.fd_con)

  def getpidtofile(self):
    '''
    get process_keyword PID and dup to file
    '''
    os.system("ps -ef|grep %s|grep -v 'grep'|awk '{print $2}' > %s" %(self.process_keyword,self.id_path))

  def loadcpu_con(self):
    '''
    loading CPU configuration
    '''
    try:
      os.system("echo %s > %s" %(self.cresult["CPU"]["period"]["val"],self.cresult["CPU"]["period"]["path"]))
      os.system("echo %s > %s" %(self.cresult["CPU"]["quota"]["val"],self.cresult["CPU"]["quota"]["path"]))
    except IOError:
      print "cpu load system called error"
    else:
      pass

  def loadmemory_con(self):
    '''
    loading MEMORY configuration
    '''
    try:
      os.system("echo %s > %s" %(self.cresult["MEMORY"]["limit"]["val"],self.cresult["MEMORY"]["limit"]["path"]))
      os.system("echo %s > %s" %(self.cresult["MEMORY"]["soft_limit"]["val"],self.cresult["MEMORY"]["soft_limit"]["path"]))
      os.system("sudo sh -c 'echo %s >> %s'" %(self.cresult["MEMORY"]["oom_control"]["val"],self.cresult["MEMORY"]["oom_control"]["path"]))
    except IOError:
      print "memory load system called error"
    else:
      pass

  def loadcpuset_con(self):
    '''
    loading CPUSET configuration
    '''
    try:
      os.system("echo %s > %s" %(self.cresult["CPUSET"]["cpus"]["val"],self.cresult["CPUSET"]["cpus"]["path"]))
      os.system("echo %s > %s" %(self.cresult["CPUSET"]["mems"]["val"],self.cresult["CPUSET"]["mems"]["path"]))
    except IOError:
      print "cpuset load system called error"
    else:
      pass

  def limitcpu(self):
    '''add PID to process cpu Cgroup'''
    try:
      self.loadcpu_con()
      fd = open(self.id_path,'r')
      while True:
        line = fd.readline()
        if line:
          os.system("echo %d > %s" %(int(line),self.cresult["CPU"]["task_path"]))
        else:
          break
    except IOError:
      print "Error(limitcpu): no such file or open failed"
    else:
      fd.close()

  def limitmemory(self):
    '''add PID to process memory Cgroup'''
    try:
      self.loadmemory_con()
      fd = open(self.id_path,'r')
      while True:
        line = fd.readline()
        if line:
          os.system("echo %d > %s" %(int(line),self.cresult["MEMORY"]["task_path"]))
        else:
          break
    except IOError:
      print "Error(limitmemory): no such file or open failed"
    finally:
      fd.close()

  def limitcpuset(self):
    "add PID to process memory Cgroup"
    try:
      self.loadcpuset_con()
      fd = open(self.id_path,'r')
      while True:
        line = fd.readline()
        if line:
          os.system("echo %d > %s" %(int(line),self.cresult["CPUSET"]["task_path"]))
        else:
          break
    except IOError:
      print "Error(limitcpuset): no such file or open failed"
    finally:
      fd.close()

  def limitcputest(self):
    self.getpidtofile()
    self.limitcpu()

  def limitmemorytest(self):
    self.getpidtofile()
    self.limitmemory()

  def __del__(self):
    self.fd_con.close()

if __name__ == '__main__':
  try:
    limit = limit()
    while True:
      limit.limitcputest()
  except ZeroDivisionError as err:
    print('Handling run-time error:', err)

