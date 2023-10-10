#!/bin/bash
#Run this in terminal
g++-11 -g runmain.cpp operation_clauses.cpp basic_clauses.cpp expression_maker.cpp -o part1
g++-11 -g satoutput1.cpp -o part1_map
g++-11 -g runmain2.cpp operation_clauses.cpp basic_clauses.cpp expression_maker.cpp -o part2
g++-11 -g satoutput2.cpp -o part2_map