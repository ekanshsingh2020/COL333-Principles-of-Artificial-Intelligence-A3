#pragma once
using namespace std;
#include <vector>

class BasicClauses {
public:
    BasicClauses();
    vector<vector<int>>* clauses;
    void equal(int x, int y);
    void and(int x, int y);
    void or(int x, int y);
    void xor(int x, int y);
    void and(int x, int y, int z);
    void or(int x, int y, int z);
    void xor(int x, int y, int z);

    ~BasicClauses();
};