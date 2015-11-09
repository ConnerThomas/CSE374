#!/bin/bash

# Conner Thomas
# CSE 374 HW 3
# Problem 1
# 1-26-15

if [ $# -lt 1 ]; then
 echo "Usage: $0 page_url"
 exit
fi

wget --tries=1 --timeout=3 -q -O page $1 
wc -c page | egrep -o '[0-9]* '
rm page

exit
