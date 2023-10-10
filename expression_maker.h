#pragma once
using namespace std;
#include <vector>
#include <iostream>
#include "basic_clauses.h"
#include "operation_clauses.h"

class ExpressionMaker {
public:
    ExpressionMaker(int n);
    void process(int k1, int k2);
    void remove_nonedges();
    void remove_repetition();
    void add_range(int l, int r, int k);
    vector<int> half_adder(int l, int r);
    vector<int> full_adder(int a, int b, int carry);
    vector<int> adder(int l, int r);

    BasicClauses bc;
    OperationClauses oc;
    int n;
    int helper_vars;
    vector<vector<int>> cnfinput;
    vector<vector<bool>> adj_mat;
};