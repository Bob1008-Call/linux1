#!/usr/bin/python
#coding=utf-8

import os
import abc
import json
import time
import logging
import subprocess

CONFIG_PATH = "/data/czk/project/con.json"

class Singleton(type):
  def __init__(cls, name, bases, dct):
    super(Singleton, cls).__init__(name, bases, dct)
    cls.instance=None

  def __call__(cls, *args, **kwargs):
    if cls.instance is None:
      cls.instance = super(Singleton, cls).__call__(*args, **kwargs)
    return cls.instance

class LimitBase(object):
  '''
  基础配置
  '''
  #初始化成员 conf 和 typelist
  def __init__(self):
    self.white_list=list()
    with open(CONFIG_PATH,'r') as con_fd:
      self.conf=json.load(con_fd)
    self.typelist=list()
    if isinstance(self.conf,dict):
      key_name="type"
      for key in self.conf.keys():
        if key == key_name and self.conf[self.conf[key]]["USE"]=="1":
          self.typelist.append(self.conf[key])

  #系统调用
  def sub_popen(self,cmd,flag=False):
    p = subprocess.Popen(cmd,shell=True,\
                          stdout=subprocess.PIPE,\
                          stderr=subprocess.PIPE,\
                          close_fds=True)
    if flag:
      return p
    else:
      return p.stderr.read().decode()

  #打印日志接口
  def log(self,txt):
    logging.basicConfig(filename="limit.log",level=logging.INFO,format='%(asctime)s %(levelname)s %(message)s %(filename)s %(funcName)s  %(lineno)s',datefmt='%Y/%m/%d %H:%M:%S %p')
    logging.info(txt)

  #创建存放 PID 路径
  def mk_idpath(self):
    idpath="/data/czk/project/id"
    if not os.path.exists(idpath):
      cmd="mkdir "
      cmd+=idpath
      p = self.popen(cmd)


  #完善白名单
  def get_white_id(self):
    list_id=[]
    for list_name in self.conf["whitelist"]["name"]:
      cmd="ps aux | grep python"
      cmd+=" |grep "
      cmd+=list_name
      cmd+=" |grep -v grep"
      cmd+=" |awk '{print $2}'"
      p=self.sub_popen(cmd,True)
      self.log(p)
      while True:
        tmp_id=p.stdout.readline()
        tmp_id=tmp_id.strip("\n")
        if tmp_id:
          list_id.append(tmp_id)
        else:
          break
    self.white_list=list_id

  #获取进程ID
  def get_pid(self):
    if self.typelist:
      for typename in self.typelist:
        cmd="ps -ef | grep "
        cmd+=typename
        cmd+="| grep -v grep"
        cmd+="| awk '{print $2}'"
        cmd+=" > "
        cmd+=str(self.conf[typename]["ID_PATH"])
        p=self.sub_popen(cmd)
        self.log(p)

  #三个抽象方法
  #创建进程控制组
  @abc.abstractmethod
  def mk_cgroup(self):
    pass

  #加载配置文件
  @abc.abstractmethod
  def load_config(self):
    pass

  #向控制组写入 PID
  @abc.abstractmethod
  def add_pid_to_cgroup(self):
    pass


class LimitCpuResou(LimitBase):
  """
  限制CPU
  """
  def __init__(self):
    super(LimitCpuResou, self).__init__()

  #创建 CPU 子系统（控制组）
  def mk_cgroup(self):
    if self.typelist:
      for typename in self.typelist:
        if self.conf[typename]["USE"]=="1":
          if not os.path.exists(self.conf[typename]["CPU"]["dir_path"]):
            cmd="mkdir "
            cmd+=str(self.conf[typename]["CPU"]["dir_path"])
            p=self.sub_popen(cmd)
            self.log(p)

  #加载 CPU 配置
  def load_config(self):
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
        p=self.sub_popen(cmd_p)
        q=self.sub_popen(cmd_q)
        self.log(p)
        self.log(q)

  #将进程 pid 加入到 CPU 控制组
  def add_pid_to_cgroup(self):
    self.get_white_id()
    if self.typelist:
      for typename in self.typelist:
        if self.conf[typename]["CPU"]["USE"]=="1":
          with open(self.conf[typename]["ID_PATH"],'r') as fd:
            while True:
              line = fd.readline()
              line = line.strip('\n')
              if line:
                if line in self.white_list:
                  continue
                else:
                  #构造指令
                  #例如: echo 1000 > /sys/fs/cgroup/cpu/python/tasks
                  cmd="echo "
                  cmd+=str(line)
                  cmd+=" > "
                  cmd+=self.conf[typename]["CPU"]["task_path"]
                  p=self.sub_popen(cmd)
                  self.log(p)
              else:
                break

class LimitMemResou(LimitBase):
  """
  限制内存
  """
  def __init__(self):
    super(LimitMemResou, self).__init__()

  #创建 memory 子系统（控制组）
  def mk_cgroup(self):
    if self.typelist:
      for typename in self.typelist:
        if self.conf[typename]["USE"]=="1":
          if os.path.exists(self.conf[typename]["MEMORY"]["dir_path"]):
            cmd="mkdir "
            cmd+=str(self.conf[typename]["MEMORY"]["dir_path"])
            p=self.sub_popen(cmd)
            self.log(p)

  #加载内存配置
  def load_config(self):
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

        p1=self.sub_popen(cmd_limit)
        p2=self.sub_popen(cmd_softlimit)
        p3=self.sub_popen(cmd_oom)
        self.log(p1)
        self.log(p2)
        self.log(p3)


  #将进程 pid 加入到 memory 控制组中
  def add_pid_to_cgroup(self):
    if self.typelist:
      for typename in self.typelist:
        if self.conf[typename]["CPU"]["USE"]=="1":
          with open(self.conf[typename]["ID_PATH"],'r') as fd:
            while True:
              line = fd.readline()
              line = line.strip('\n')
              if line:
                if line not in self.conf["whitelist"]["id"]:
                  #构造指令
                  #例如: echo 1000 > /sys/fs/cgroup/cpu/python/tasks
                  cmd="echo "
                  cmd+=str(line)
                  cmd+=" > "
                  cmd+=self.conf[typename]["MEMORY"]["task_path"]
                  p=self.sub_popen(cmd)
                  self.log(p)
              else:
                break

class Run(object):
  __metaclass__=Singleton
  def __init__(self):
    pass

  def run(self):
    self.base = LimitBase()
    self.derived = LimitCpuResou()
    self.base.get_pid()
    self.derived.mk_cgroup()
    self.derived.load_config()
    self.derived.add_pid_to_cgroup()

if "__main__"==__name__:
  while True:
    run1=Run()
    run1.run()
    time.sleep(0.1)
