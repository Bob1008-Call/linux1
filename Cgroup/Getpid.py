import os
import json

ID_PATH = "/data/czk/project/id.txt"
CONFIG_PATH = "/data/czk/project/con.json"
PROCESS_KEYWORD = "highmem"

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

  def getpidtofile(self):
    '''
    get process_keyword PID and dup to file
    '''
    os.system("ps -ef|grep %s|grep -v 'grep'|awk '{print $2}' > %s" %(self.process_keyword,self.id_path))

  def limitmemory(self):
    '''add PID to process memory Cgroup'''
    try:
      fd = open(self.id_path,'r')
      while True:
        line = fd.readline()
        if line:
          os.system("echo %s > %s" %(int(line),self.cresult["MEMORY"]["task_path"]))
        else:
          break
    except IOError:
      print "Error(limitmemory): no such file or open failed"
    finally:
      fd.close()

  def limitcpu(self):
    '''add PID to process cpu Cgroup'''
    try:
      fd = open(self.id_path,'r')
      while True:
        line = fd.readline()
        if line:
          os.system("echo %d > %s" %(int(line),self.cresult["CPU"]["task_path"]))
        else:
          break
    except IOError:
      print "Error(limitcpu): no such file or open fail"
    else:
      fd.close()

  def __del__(self):
    self.fd_con.close()

if __name__ == '__main__':
  try:
    limit1=limit()
    limit1.loadcpu_con()
    limit1.getpidtofile()
    limit1.limitcpu()
  except ZeroDivisionError as err:
    print('Handling run-time error:', err)
