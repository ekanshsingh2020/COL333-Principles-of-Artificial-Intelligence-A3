#include "basic_clauses.h"
using namespace std;

BasicClauses::BasicClauses()
{
}

void BasicClauses::equal(int x, int y)
{
    vector<int> eq1{x,-y};
    vector<int> eq2{-x,y};
    clauses->emplace_back(eq1);
    clauses->emplace_back(eq2);
}

void BasicClauses::and1(int x, int y)
{
    vector<int> eq1{x};
    vector<int> eq2{y};
    clauses->emplace_back(eq1);
    clauses->emplace_back(eq2);
}

void BasicClauses::or1(int x, int y)
{
    vector<int> eq1{x,y};
    clauses->emplace_back(eq1);
}

void BasicClauses::xor1(int x, int y)
{
    vector<int> eq1{x,y};
    vector<int> eq2{-x,-y};
    clauses->emplace_back(eq1);
    clauses->emplace_back(eq2);
}

void BasicClauses::and2(int x, int y, int z)
{
    vector<int> eq1{z};
    vector<int> eq2{y};
    vector<int> eq3{x};
    clauses->emplace_back(eq1);
    clauses->emplace_back(eq2);
    clauses->emplace_back(eq3);
}

void BasicClauses::or2(int x, int y, int z)
{
    vector<int> eq1{x,y,z};
    clauses->emplace_back(eq1);
}

void BasicClauses::xor2(int x, int y, int z)
{
    vector<int> eq1{x,y,z};
    vector<int> eq2{-x,-y,z};
    vector<int> eq3{x,-y,-z};
    vector<int> eq4{-x,y,-z};
    clauses->emplace_back(eq1);
    clauses->emplace_back(eq2);
    clauses->emplace_back(eq3);
    clauses->emplace_back(eq4);
}
