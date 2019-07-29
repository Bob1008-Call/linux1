#!/bin/bash

#echo "Language:$1"
#echo "URL:$2"

#num=(1 2 3 4 5 6)
#echo ${num[*]}
#echo $num[*]
#echo $num[@]

#num1=(1 2 3)
#num2=(4 5 6)
#num_new=(${num1[*]}" "${num2[@]})
#echo ${num_new[*]}

#str="caozongkai"
#echo ${#str}

#alias timestamp='date +%s'
#begin=`timestamp`  
#sleep 20s
#finish=$(timestamp)
#difference=$((finish - begin))
#echo "run time: ${difference}s"

current=`date "+%Y-%m-%d %H:%M:%S"`  
timeStamp=`date -d "$current" +%s`   
#将current转换为时间戳，精确到毫秒  
currentTimeStamp1=$((timeStamp*1000+`date "+%N"`/1000000)) 
sleep 2s
currentTimeStamp2=$((timeStamp*1000+`date "+%N"`/1000000)) 
diff=$((currentTimeStamp2-currentTimeStamp1))
echo $diff
