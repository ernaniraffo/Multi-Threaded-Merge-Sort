#!/bin/bash

make clean && make
rm -f /tmp/results.dat

MAX=1000

for ((i=100; $i<=$MAX; i*=10)); do
    ./sort -n 0 -p -s $i -c 8 >> /tmp/results.dat
done

lines=$(wc -l </tmp/results.dat)
echo $lines
for ((i=1; $i<=$lines; i+=2)); do
    awk '{ print $6 }' /tmp/results.dat
    awk '{ print $5 }' /tmp/results.dat
done

