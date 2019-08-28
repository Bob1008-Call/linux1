#!/bin/bash
echo "running...."


total()
{
  cat /sys/fs/cgroup/memory/g1/tasks |wc -l
}

{
  i=1
  while ((i<500))
  do
    t=':'
    name='process'
    res=`total`
    RSS='RSS'
    M='M'
    SPACE=' '
    num=$(ps -aux | grep highmem |grep -v grep | awk '{sum += $6} END {print sum}')
    num=$((10#${num}/1024))
    str=$name$t${res}$SPACE$RSS$t$num$M
    echo $str >> ../memshow/memsums.txt
    ((i++))
  done
}
