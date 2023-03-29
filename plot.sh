#!/bin/bash

set -x

make clean && make
rm -f /tmp/*.dat

MAX=10000000

echo "Running sort program..."
for ((i=100; $i<=$MAX; i*=10)); do
    ./sort -n 0 -p -s $(($i/4)) -c 8 >> /tmp/results.dat
    ./sort -n 0 -p -s $(($i/3)) -c 8 >> /tmp/results.dat
    ./sort -n 0 -p -s $(($i/2)) -c 8 >> /tmp/results.dat
    ./sort -n 0 -p -s $i -c 8 >> /tmp/results.dat
done

awk '($1 == "Parallel") { print $4, $6 }' /tmp/results.dat >/tmp/Parallel.dat
awk '($1 == "Merge") { print $3, $5 } ' /tmp/results.dat >/tmp/Merge.dat

echo "Plotting..."
gnuplot << EOF
set terminal epslatex color
set title "Parallel vs. Sequential Merge Sort (8 cores)"
set xlabel "Elements"
set ylabel "Time (seconds)"
set logscale
set xtics nologscale
set ytics nologscale
set output "first_attempt.tex"
plot "/tmp/Parallel.dat" using 1:2 title 'Parallel' with lines , \
"/tmp/Merge.dat" using 1:2 title 'Sequential' with lines
EOF
echo "Done."

rm -f /tmp/*.dat

echo "Running sort program..."
for ((i=100; $i<=$MAX; i*=10)); do
    ./sort -n 0 -p -s $(($i/4)) -c 8 >> /tmp/results.dat
    ./sort -n 0 -p -s $(($i/3)) -c 8 >> /tmp/results.dat
    ./sort -n 0 -p -s $(($i/2)) -c 8 >> /tmp/results.dat
    ./sort -n 0 -p -s $i -c 8 >> /tmp/results.dat
done

awk '($1 == "Parallel") { print $4, $6 }' /tmp/results.dat >/tmp/Parallel.dat
awk '($1 == "Merge") { print $3, $5 } ' /tmp/results.dat >/tmp/Merge.dat
awk '($1 == "Optimized") && ($5 != "V2,") { print $5, $7 }' /tmp/results.dat >/tmp/Optimized.dat
awk '($1 == "Optimized") && ($5 == "V2,") { print $6, $8 }' /tmp/results.dat >/tmp/OptimizedV2.dat

echo "Plotting..."
gnuplot << EOF
set terminal epslatex color
set title "Parallel vs. Optimized vs. Sequential (8 cores)"
set xlabel "Elements"
set ylabel "Time (seconds)"
set logscale
set xtics nologscale
set ytics nologscale
set output "optimized.tex"
plot "/tmp/Parallel.dat" using 1:2 title 'Parallel' with lines , \
"/tmp/Optimized.dat" using 1:2 title 'Optimized Parallel' with lines , \
"/tmp/OptimizedV2.dat" using 1:2 title 'Optimized Parallel V2' with lines, \
"/tmp/Merge.dat" using 1:2 title 'Sequential' with lines
EOF
echo "Done."

rm -f /tmp/*.dat

MAX=1000000

echo "Running sort program..."
for ((i=10000; $i<=$MAX; i+=10000)); do
    ./sort -n 0 -p -s $i -c 8 >> /tmp/results.dat
done

awk '($1 == "Parallel") { print $4, $6 }' /tmp/results.dat >/tmp/Parallel.dat
awk '($1 == "Merge") { print $3, $5 } ' /tmp/results.dat >/tmp/Merge.dat
awk '($1 == "Optimized") && ($5 != "V2,") { print $5, $7 }' /tmp/results.dat >/tmp/Optimized.dat
awk '($1 == "Optimized") && ($5 == "V2,") { print $6, $8 }' /tmp/results.dat >/tmp/OptimizedV2.dat

echo "Plotting..."
gnuplot << EOF
set terminal epslatex color
set title "Parallel vs. Optimized vs. Sequential (8 cores)"
set xlabel "Elements"
set ylabel "Time (seconds)"
set logscale
set xtics nologscale
set ytics nologscale
set output "large.tex"
plot "/tmp/Parallel.dat" using 1:2 title 'Parallel' with lines , \
"/tmp/Optimized.dat" using 1:2 title 'Optimized Parallel' with lines , \
"/tmp/OptimizedV2.dat" using 1:2 title 'Optimized Parallel V2' with lines, \
"/tmp/Merge.dat" using 1:2 title 'Sequential' with lines
EOF
echo "Done."

rm -f /tmp/*.dat

MAX=10000000

echo "Running sort program..."
for ((i=1000000; $i<=$MAX; i+=1000000)); do
    ./sort -n 0 -p -s $i -c 8 >> /tmp/results.dat
done

awk '($1 == "Parallel") { print $4, $6 }' /tmp/results.dat >/tmp/Parallel.dat
awk '($1 == "Merge") { print $3, $5 } ' /tmp/results.dat >/tmp/Merge.dat
awk '($1 == "Optimized") && ($5 != "V2,") { print $5, $7 }' /tmp/results.dat >/tmp/Optimized.dat
awk '($1 == "Optimized") && ($5 == "V2,") { print $6, $8 }' /tmp/results.dat >/tmp/OptimizedV2.dat

echo "Plotting..."
gnuplot << EOF
set terminal epslatex color
set title "Parallel vs. Optimized vs. Sequential (8 cores)"
set xlabel "Elements"
set ylabel "Time (seconds)"
set logscale
set xtics nologscale
set ytics nologscale
set output "huge.tex"
plot "/tmp/Parallel.dat" using 1:2 title 'Parallel' with lines , \
"/tmp/Optimized.dat" using 1:2 title 'Optimized Parallel' with lines , \
"/tmp/OptimizedV2.dat" using 1:2 title 'Optimized Parallel V2' with lines, \
"/tmp/Merge.dat" using 1:2 title 'Sequential' with lines
EOF
echo "Done."

rm -f /tmp/*.dat

MAX=999999

echo "Running sort program..."
for ((i=99; $i<=$MAX; i=i*10+9)); do
    ./sort -n 0 -p -s $i -c 8 >> /tmp/results.dat
done

awk '($1 == "Parallel") { print $4, $6 }' /tmp/results.dat >/tmp/Parallel.dat
awk '($1 == "Merge") { print $3, $5 } ' /tmp/results.dat >/tmp/Merge.dat
awk '($1 == "Optimized") && ($5 != "V2,") { print $5, $7 }' /tmp/results.dat >/tmp/Optimized.dat
awk '($1 == "Optimized") && ($5 == "V2,") { print $6, $8 }' /tmp/results.dat >/tmp/OptimizedV2.dat

echo "Plotting..."
gnuplot << EOF
set terminal epslatex color
set title "Parallel vs. Optimized vs. Sequential (8 cores)"
set xlabel "Elements"
set ylabel "Time (seconds)"
set logscale
set xtics nologscale
set ytics nologscale
set output "remainder.tex"
plot "/tmp/Parallel.dat" using 1:2 title 'Parallel' with linespoints , \
"/tmp/Optimized.dat" using 1:2 title 'Optimized Parallel' with linespoints , \
"/tmp/OptimizedV2.dat" using 1:2 title 'Optimized Parallel V2' with linespoints, \
"/tmp/Merge.dat" using 1:2 title 'Sequential' with linespoints
EOF
echo "Done."
