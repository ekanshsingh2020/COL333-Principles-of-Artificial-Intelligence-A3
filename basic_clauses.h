#pragma once
using namespace std;
// #ifndef BasicClauses
// #define BasicClauses
#include <vector>

class BasicClauses {
public:
    BasicClauses();
    vector<vector<int>>* clauses;
    void equal(int x, int y);
    void and1(int x, int y);
    void or1(int x, int y);
    void xor1(int x, int y);
    void and2(int x, int y, int z);
    void or2(int x, int y, int z);
    void xor2(int x, int y, int z);
};