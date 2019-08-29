#!/usr/bin/python
#coding=utf-8
"""
  限制系统资源
  已完成：CPU 内存
"""

import os
import abc
import json
import time
import logging
import subprocess

CONFIG_PATH = "/data/czk/project/con.json"

class Singleton(type):
  '''
  单例模式
  '''
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
  #初始化成员 conf  typelist whitelist
  def __init__(self):
    self.whitelist=list()
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
    p = subprocess.Popen(cmd,\
                         shell=True,\
                         stdout=subprocess.PIPE,\
                         stderr=subprocess.PIPE,\
                         close_fds=True)
    if flag:
      return p
    else:
      return p.stderr.read().decode()

  #打印日志接口
  def log(self,txt):
    #打印当前日志到默认文件路径
    logging.basicConfig(filename="limittest.log",\
                        level=logging.INFO,\
                        format='%(asctime)s %(levelname)s %(message)s %(filename)s %(funcName)s %(lineno)s',\
                        datefmt='%Y/%m/%d %H:%M:%S %p')
    logging.info(txt)

  #创建存放 PID 路径
  def mk_idpath(self):
    idpath="/data/czk/project/id"
    if not os.path.exists(idpath):
      cmd="mkdir "
      cmd+=idpath
      p = self.sub_popen(cmd)


  #构造白名单
  def get_white_id(self):
    list_id=[]
    for list_name in self.conf["whitelist"]["name"]:
      cmd="ps aux | grep python"
      cmd+=" |grep "
      cmd+=list_name
      cmd+=" |grep -v grep"
      cmd+=" |awk '{print $2}'"
      #构造获取白名单进程 PID 的指令
      p=self.sub_popen(cmd,True)
      while True:
        tmp_id=p.stdout.readline()
        tmp_id=tmp_id.strip("\n")
        if tmp_id:
          list_id.append(tmp_id)
        else:
          break
    self.whitelist=list_id


  #获取进程ID
  def get_pid(self):
    if self.typelist:
      for typename in self.typelist:
        cmd="ps -ef | grep "
        cmd+=typename
        cmd+="| grep -v grep"
        cmd+="| awk '{print $2}'"
        cmd+=" > "
        #构造获取不同类型进程 PID 的指令
        cmd+=str(self.conf[typename]["ID_PATH"])
        p=self.sub_popen(cmd)

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
  '''
  限制CPU
  '''
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
            p = self.sub_popen(cmd)
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

        self.sub_popen(cmd_p)
        self.sub_popen(cmd_q)

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
                if line in self.whitelist:
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
  '''
  限制内存
  '''
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
            p = self.sub_popen(cmd)
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

        self.sub_popen(cmd_limit)
        self.sub_popen(cmd_softlimit)
        self.sub_popen(cmd_oom)


  #将进程 pid 加入到 memory 控制组中
  def add_pid_to_cgroup(self):
    self.get_white_id()
    if self.typelist:
      for typename in self.typelist:
        if self.conf[typename]["MEMORY"]["USE"]=="1":
          with open(self.conf[typename]["ID_PATH"],'r') as fd:
            while True:
              line = fd.readline()
              line = line.strip('\n')
              if line:
                if line in self.whitelist:
                  continue
                else:
                  cmd="echo "
                  cmd+=str(line)
                  cmd+=" > "
                  cmd+=self.conf[typename]["MEMORY"]["task_path"]
                  p=self.sub_popen(cmd)
                  self.log(p)
              else:
                break

class LimitDiskResou(LimitBase):
  '''
    限制磁盘读写
  '''
  def __init__(self):
    super(LimitDskResou, self).__init__()

  #创建 blkio 子系统（控制组）
  def mk_cgroup(self):
    if self.typelist:
      for typename in self.typelist:
        if self.conf[typename]["USE"]=="1":
          if os.path.exists(self.conf[typename]["DISK"]["dir_path"]):
            cmd="mkdir "
            cmd+=str(self.conf[typename]["DISK"]["dir_path"])
            p = self.sub_popen(cmd)
            self.log(p)

  #加载磁盘配置
  def load_config(self):
    if self.typelist:
      for typename in self.typelist:
        # 8:16 是磁盘驱动号
        cmd_read="echo 8:16 "
        cmd_read+=str(self.conf[typename]["DISK"]["read_bps"]["val"])
        cmd_read+=" > "
        cmd_read+=str(self.conf[typename]["DISK"]["read_bps"]["path"])

        cmd_write="echo 8:16 "
        cmd_write+=str(self.conf[typename]["DISK"]["write_bps"]["val"])
        cmd_write+=" > "
        cmd_write+=str(self.conf[typename]["DISK"]["write_bps"]["path"])

        self.sub_popen(cmd_read)
        self.sub_popen(cmd_write)

  #将进程 pid 加入到 blkio 控制组中
  def add_pid_to_cgroup(self):
    self.get_white_id()
    if self.typelist:
      for typename in self.typelist:
        if self.conf[typename]["DISK"]["USE"]=="1":
          with open(self.conf[typename]["ID_PATH"],'r') as fd:
            while True:
              line = fd.readline()
              line = line.strip('\n')
              if line:
                if line in self.whitelist:
                  continue
                else:
                  cmd="echo "
                  cmd+=str(line)
                  cmd+=" > "
                  cmd+=self.conf[typename]["DISK"]["task_path"]
                  p=self.sub_popen(cmd)
                  self.log(p)
              else:
                break

class Run(object):
  __metaclass__=Singleton
  def __init__(self):
    pass

  def run(self):
    '''
      限制CPU
    '''
    self.base = LimitBase()
    self.derived = LimitCpuResou()
    self.derived.mk_cgroup()
    self.derived.load_config()
    while True:
      self.base.get_pid()
      self.derived.add_pid_to_cgroup()
      time.sleep(1)
    '''
      限制内存
    '''
    #self.base = LimitBase()
    #self.base.get_pid()

    #self.derived = LimitMemResou()
    #self.derived.mk_cgroup()
    #self.derived.load_config()
    #self.derived.add_pid_to_cgroup()

    '''
      限制磁盘
    '''
    #self.base = LimitBase()
    #self.base.get_pid()

    #self.derived = LimitDiskResou()
    #self.derived.mk_cgroup()
    #self.derived.load_config()
    #self.derived.add_pid_to_cgroup()
if "__main__"==__name__:
  run1=Run()
  run1.run()
