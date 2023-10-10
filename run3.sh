#!/bin/bash
#Run this in terminal
# if [ $# -eq 0 ]; then
#     echo "Usage: $0 <test>"
#     exit 1
# fi

# input = $1
# echo $1
inputgraph="$1.graph"
line=$(head -n 1 $inputgraph)
# assign n the first integer in line
n=$(echo $line | cut -d' ' -f1)

low=1
high=$(($n))

while [ $low -lt $high ]; do
    mid=$(expr $low + '(' $high - $low + 1 ')' / 2)
    ./part2 $1 $mid
    timeout 5s ./minisat $1.satinput $1.satoutput
    outgraph="$1.satoutput"
    line=$(head -n 1 $outgraph)
    if [ "$line" == "SAT" ]; then 
        low=$(($mid))
    else
        high=$(expr $mid - 1)
    fi
done
./part2_map $1