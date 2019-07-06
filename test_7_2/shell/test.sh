#!/bin/bash 
#echo It is a test

myint=123
mystr="helloworld"
mychar='c'
myfloat=3.14

#i=1
#sum=0
#while [ $i -le 100 ]
#do 
#  echo i
#done

#i=1
#sum=0
#for (( i=0;i<100;++i ))
#do 
#  echo 
#done 
#

# -eq -lt -gt -le -ge -ne

#function show()
#{
#  echo "\$1" $1 
#  echo "\$2" $2
#}
#
#show 123 345 456

if [ $? -eq 0 ];
then
  echo "success"
else
  echo "failed"
fi
