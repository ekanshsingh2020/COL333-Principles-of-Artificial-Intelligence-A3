#!/bin/bash
line=$(head -n 1 "$1.graph")

n=$(echo $line | cut -d' ' -f1)

low=1
high=$(($n))

while [ $low -lt $high ]; do
    mid=$(expr $low + '(' $high - $low + 1 ')' / 2)
    ./part2 $1 $mid
    timeout 5s ./minisat $1.satinput $1.satoutput
    line=$(head -n 1 "$1.satoutput")
    if [ "$line" == "SAT" ]; then 
        low=$(($mid))
    else
        high=$(expr $mid - 1)
    fi
done
./part2_map $1