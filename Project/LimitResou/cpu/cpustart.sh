#!/bin/bash
echo "running...."

total()
{
  cat /sys/fs/cgroup/cpu/g2/tasks | wc -l
}

caltotal()
{
  top -d 1 -n 1 -b| grep python| awk '{sum+=$9} END {print sum}'
}

{
  i=1
  while ((i<50000))
  do
    t=':'
    name='process'
    CPU='CPU'
    M='%'
    SPACE=' '
    res=`total`
    cal=`caltotal`
    str=$name$t${res}$SPACE$CPU$t$M${cal}
    echo $str
    echo $str >> ../cpushow/cpusums3.txt
    ((i++))
  done
}
