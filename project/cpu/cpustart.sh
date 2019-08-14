#!/bin/bash
echo "running...."

total()
{
  cat /sys/fs/cgroup/cpu/g1/tasks | wc -l
}

{
  i=1
  while ((i<500))
  do
    t=':'
    name='process'
    CPU='%CPU'
    M='%'
    SPACE=' '
    res=`total`
    num=$(ps -aux | grep highcpu |grep -v grep | awk '{sum += $3} END {print sum}')
    str=$name$t${res}$SPACE$CPU$t$M$num
    if ((i%10==0))
    then
      echo "30s later..." >>../cpushow/cpusums.txt
    fi
    echo $str >> ../cpushow/cpusums.txt
    sleep 3s
    ((i++))
  done
}
