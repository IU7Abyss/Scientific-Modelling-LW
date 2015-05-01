#!/bin/bash

cd `dirname "$0"`

./run_test1.sh &
sleep 1
./run_test2.sh &
sleep 1
./run_test3.sh