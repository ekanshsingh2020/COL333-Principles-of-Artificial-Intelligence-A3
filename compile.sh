#!/bin/bash
#Run this in terminal
g++ -g runmain.cpp operation_clauses.cpp basic_clauses.cpp expression_maker.cpp -o part1
g++ -g satoutput1.cpp -o part1_map
g++ -g runmain2.cpp operation_clauses.cpp basic_clauses.cpp expression_maker.cpp -o part2
g++ -g satoutput2.cpp -o part2_map