#!/bin/bash
#Run this in terminal
g++ -Wall -Wextra -g runmain.cpp operation_clauses.cpp basic_clauses.cpp expression_maker.cpp -o part1
g++ -Wall -Wextra -g satoutput1.cpp -o part1_map
g++ -Wall -Wextra -g runmain2.cpp operation_clauses.cpp basic_clauses.cpp expression_maker.cpp -o part2
g++ -Wall -Wextra -g satoutput2.cpp -o part2_map