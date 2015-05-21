#!/bin/bash

cd `dirname "$0"`

./example-1.sh &
sleep 1
./example-2.sh &
sleep 1
./example-3.sh &
sleep 1
./example-4.sh