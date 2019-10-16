#!/bin/bash

dirs="algorithm common concurrency
      container date_time function
      math memory os string test utility"

for d in $dirs
do
    echo "-------$d-------"
    cd ${d}

    #b2 clean
    b2 > build.log 2>&1 || (cat build.log && exit 1)
    b2 clean > build.log 2>&1 || (cat build.log && exit 1)
    rm build.log

    cd ..
done
