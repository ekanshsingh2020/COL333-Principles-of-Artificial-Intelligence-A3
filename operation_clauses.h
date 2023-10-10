#pragma once
using namespace std;
#include <vector>

class OperationClauses {
public:
    OperationClauses();
    vector<vector<int>>* clauses;
    void equal(int x, int y);
    void and1(int x, int y, int z);
    void or1(int x, int y, int z);
    void xor1(int x, int y, int z);
    void zero(int x);
};