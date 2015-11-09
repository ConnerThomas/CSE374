#!/bin/bash

# Conner Thomas
# CSE 274 HW 3
# Problem 3
# 1-26-15

if [ $# -lt 2 ];then
 echo "Usage: $0 input_file_output_file"
 exit
fi 

if [ ! -f $1 ];then
 echo "Error: $1 does not exist"
 exit
fi

URLS="$(< $1)"
rank=1
for URL in $URLS;do
 echo "Performing measurement on "$URL
 OUT="$(./perform-measurement.sh $URL)"
 if [ $OUT == 0 ];then
  echo "...failed"
  ((rank++))
 else
  echo "...success"
  echo "$rank $URL $OUT" >> $2 
  ((rank++))
 fi
done
# sort -n -r -k 2 /tmp/unsorted.out > /tmp/sorted.out
# nl -w1 -s " " -nrn /tmp/sorted.out > $2
# rm /tmp/unsorted.out
# rm /tmp/sorted.out
exit

