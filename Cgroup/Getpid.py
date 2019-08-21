#!/usr/bin/python
#coding=utf-8

import json
import subprocess

CONFIG_PATH = "/data/czk/project/con.json"

class LimitBase(object):
  '''
  基础配置
  '''
  #初始化成员 conf 和 typelist
  def __init__(self):
    with open(CONFIG_PATH,'r') as con_fd:
      self.conf=json.load(con_fd)
    self.typelist=list()
    if isinstance(self.conf,dict):
      key_name="type"
      for key in self.conf.keys():
        if key == key_name and self.conf[self.conf[key]]["USE"]=="1":
          self.typelist.append(self.conf[key])

  #系统调用
  def sub_popen(self,cmd):
    p1 = subprocess.Popen(cmd,shell=True,stdout=subprocess.PIPE,stderr=subprocess.PIPE)

  #获取进程ID
  def get_pid(self):
    if self.typelist:
      for typename in self.typelist:
        cmd="ps -ef | grep "
        cmd+=typename
        cmd+="| grep -v 'grep'"
        cmd+="| grep -v /"
        cmd+=typename
        cmd+="| grep -v '/conf'"
        cmd+="| awk '{print $2}'"
        cmd+=" > "
        cmd+=str(self.conf[typename]["ID_PATH"])
        try:
          self.sub_popen(cmd)
        except IOError:
          print "Error(getpid): write pid to file error"

class LimitCpuResou(LimitBase):
  """
  限制CPU
  """
  def __init__(self):
    super(LimitCpuResou, self).__init__()

  def mk_cpug(self):
    if self.typelist:
      for typename in self.typelist:
        if self.conf[typename]["USE"]=="1":
          cmd="mkdir "
          cmd+=str(self.conf[typename]["CPU"]["dir_path"])
          self.sub_popen(cmd)

  #加载CPU配置
  def config_cpu(self):
    if self.typelist:
      for typename in self.typelist:
        cmd_p="echo "
        cmd_p+=str(self.conf[typename]["CPU"]["period"]["val"])
        cmd_p+=" > "
        cmd_p+=str(self.conf[typename]["CPU"]["period"]["path"])

        cmd_q="echo "
        cmd_q+=str(self.conf[typename]["CPU"]["quota"]["val"])
        cmd_q+=" > "
        cmd_q+=str(self.conf[typename]["CPU"]["quota"]["path"])
        try:
          self.sub_popen(cmd_p)
          self.sub_popen(cmd_q)
        except IOError:
          print "cpu load system called error"
        else:
          pass

  #将进程 pid 加入到 CPU 控制组
  def push_to_cpug(self):
    if self.typelist:
      for typename in self.typelist:
        with open(self.conf[typename]["ID_PATH"],'r') as fd:
          while True:
            line = fd.readline()
            line = line.strip('\n')
            if line:
              #构造指令
              #例如: echo 1000 > /sys/fs/cgroup/cpu/python/tasks
              cmd="echo "
              cmd+=str(line)
              cmd+=" > "
              cmd+=self.conf[typename]["CPU"]["task_path"]
              try:
                self.sub_popen(cmd)
              except IOError:
                print "Error(limitcpu): no such file process"
              finally:
                pass
            else:
              break

class LimitMemResou(LimitBase):
  """
  限制内存
  """
  def __init__(self):
    super(LimitMemResou, self).__init__()

  def mk_memoryg(self):
    if self.typelist:
      for typename in self.typelist:
        if self.conf[typename]["USE"]=="1":
          cmd="mkdir "
          cmd+=str(self.conf[typename]["MEMORY"]["dir_path"])
          self.sub_popen(cmd)


  #加载内存配置
  def config_mem(self):
    if self.typelist:
      for typename in self.typelist:
        cmd_limit="echo "
        cmd_limit+=str(self.conf[typename]["MEMORY"]["limit"]["val"])
        cmd_limit+=" > "
        cmd_limit+=str(self.conf[typename]["MEMORY"]["limit"]["path"])

        cmd_softlimit="echo "
        cmd_softlimit+=str(self.conf[typename]["MEMORY"]["soft_limit"]["val"])
        cmd_softlimit+=" > "
        cmd_softlimit+=str(self.conf[typename]["MEMORY"]["soft_limit"]["path"])

        cmd_oom="echo "
        cmd_oom+=str(self.conf[typename]["MEMORY"]["oom_control"]["val"])
        cmd_oom+=" > "
        cmd_oom+=str(self.conf[typename]["MEMORY"]["oom_control"]["path"])

        try:
          self.sub_popen(cmd_limit)
          self.sub_popen(cmd_softlimit)
          self.sub_popen(cmd_oom)
        except IOError:
          print "memory load system called error"
        else:
          pass

  #将进程 pid 加入到 memory 控制组中
  def push_to_memg(self):
    if self.typelist:
      for typename in self.typelist:
        with open(self.conf[typename]["ID_PATH"],'r') as fd:
          while True:
            line = fd.readline()
            line = line.strip('\n')
            if line:
              #构造指令
              #例如: echo 1000 > /sys/fs/cgroup/cpu/python/tasks
              cmd="echo "
              cmd+=str(line)
              cmd+=" > "
              cmd+=self.conf[typename]["MEMORY"]["task_path"]
              try:
                self.sub_popen(cmd)
              except IOError:
                print "Error(limitmemory): no such file process"
              finally:
                pass
            else:
              break

if "__main__"==__name__:
  limitbase=LimitBase()
  limitbase.get_pid()
  limitcpu=LimitCpuResou()
  limitcpu.config_cpu()
  limitcpu.push_to_cpug()
