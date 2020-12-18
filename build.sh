#!/bin/sh

./bootstrap.sh

sudo \
./b2 --without-coroutine \
     --without-locale \
     --without-log \
     --without-python \
     --without-regex \
     --without-serialization \
     --without-wave \
     --without-random \
     --without-mpi \
     install
