#include "operation_clauses.h"
using namespace std;

OperationClauses::OperationClauses()
{
}

void OperationClauses::equal(int x, int y)
{
    vector<int> eq1{x,-y};
    vector<int> eq2{-x,y};
    clauses->emplace_back(eq1);
    clauses->emplace_back(eq2);
}

void OperationClauses::and1(int x, int y, int z)
{
    //x=y and z
    vector<int> eq1{x,-y,-z};
    vector<int> eq2{-x,y};
    vector<int> eq3{-x,z};
    clauses->emplace_back(eq1);
    clauses->emplace_back(eq2);
    clauses->emplace_back(eq3);
}

void OperationClauses::or1(int x, int y, int z)
{
    // x = y or z
    vector<int> eq1{-x,y,z};
    vector<int> eq2{x,-y};
    vector<int> eq3{x,-z};
    clauses->emplace_back(eq1);
    clauses->emplace_back(eq2);
    clauses->emplace_back(eq3);
}

void OperationClauses::xor1(int x, int y, int z)
{
    // x = y xor z
    vector<int> eq1{-x,y,z};
    vector<int> eq2{x,-y,z};
    vector<int> eq3{x,y,-z};
    vector<int> eq4{-x,-y,-z};
    clauses->emplace_back(eq1);
    clauses->emplace_back(eq2);
    clauses->emplace_back(eq3);
    clauses->emplace_back(eq4);
}

void OperationClauses::zero(int x)
{
    // x = 0
    vector<int> eq1{-x};
    clauses->emplace_back(eq1);
}
