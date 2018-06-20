#!/bin/bash

dirs="algorithm common
      container date_time function
      math memory os string test utility"
#concurrency

for d in $dirs
do
    echo "---$d---"
    cd ${d}
    b2 clean #&& b2
    cd ..
done
