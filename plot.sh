#!/bin/bash

make clean && make
rm -f /tmp/results.dat

MAX=100000000

echo "Running sort program..."
for ((i=1000; $i<=$MAX; i*=10)); do
    ./sort -n 0 -p -s $i -c 8 >> /tmp/results.dat
done

awk '($1 == "Parallel") { print $4, $6 }' /tmp/results.dat >/tmp/Parallel.dat
awk '($1 == "Merge") { print $3, $5 } ' /tmp/results.dat >/tmp/Merge.dat
awk '($1 == "Optimized") && ($5 != "V2,") { print $5, $7 }' /tmp/results.dat >/tmp/Optimized.dat
awk '($1 == "Optimized") && ($5 == "V2,") { print $6, $8 }' /tmp/results.dat >/tmp/OptimizedV2.dat

echo "Plotting..."
gnuplot << EOF
set terminal epslatex color
set title "Parallel, Optimized Parallel, Sequential"
set xlabel "Elements"
set ylabel "Time (seconds)"
set logscale
set xtics nologscale
set ytics nologscale
set yrange[:100]
set output "time.tex"
plot "/tmp/Parallel.dat" using 1:2 title 'Parallel' with lines , \
"/tmp/Optimized.dat" using 1:2 title 'Optimized Parallel' with lines , \
"/tmp/OptimizedV2.dat" using 1:2 title 'Optimized Parallel V2' with lines, \
"/tmp/Merge.dat" using 1:2 title 'Sequential' with lines
EOF
echo "Done."
make writeup
open writeup.pdf
