#!/bin/sh
# copyright (c) 2020 by chrono

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
     --without-math \
     --without-graph \
     --without-graph_parallel \
     install
