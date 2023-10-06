#pragma once
using namespace std;
#include <vector>
#include "basic_clauses.h"

class ExpressionMaker {
public:
    ExpressionMaker();
    ~ExpressionMaker();

    BasicClauses bc;
    vector<vector<int>> cnfinput;
};