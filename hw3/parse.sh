#!/bin/bash

# Conner Thomas
# CSE 374 HW 3
# Problem 2
# 1-26-15

if [ ! -f $1 ];then
 echo "Error: $1 does not exist"
 exit
fi

if [ $# -lt 2 ]; then
 echo "Usage: $0 input_file output_file"
 exit
fi

grep -io 'http://[a-z0-9./-]*' $1 > /tmp/parsefile
grep -vwE 'altavista|100bestwebsites|en.wikipedia.org' /tmp/parsefile > $2
rm /tmp/parsefile

exit
