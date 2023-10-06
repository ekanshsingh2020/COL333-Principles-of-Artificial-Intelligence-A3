#include <basic_clauses.h>
using namespace std;

BasicClauses::BasicClauses()
{
}

void BasicClauses::equal(int x, int y)
{
    vector<int> eq1{x,-y};
    vector<int> eq2{-x,y};
    clauses->push_back(eq1);
    clauses->push_back(eq2);
}

void BasicClauses::and(int x, int y)
{
    vector<int> eq1{x};
    vector<int> eq2{y};
    clauses->push_back(eq1);
    clauses->push_back(eq2);
}

void BasicClauses::or(int x, int y)
{
    vector<int> eq1{x,y};
    clauses->push_back(eq1);
}

void BasicClauses::xor(int x, int y)
{
    vector<int> eq1{x,y};
    vector<int> eq2{-x,-y};
    clauses->push_back(eq1);
    clauses->push_back(eq2);
}

void BasicClauses::and(int x, int y, int z)
{
    vector<int> eq1{z};
    vector<int> eq2{y};
    vector<int> eq3{x};
    clauses->push_back(eq1);
    clauses->push_back(eq2);
    clauses->push_back(eq3);
}

void BasicClauses::or(int x, int y, int z)
{
    vector<int> eq1{x,y,z};
    clauses->push_back(eq1);
}

void BasicClauses::xor(int x, int y, int z)
{
    vector<int> eq1{x,y,z};
    vector<int> eq2{-x,-y,z};
    vector<int> eq3{x,-y,-z};
    vector<int> eq4{-x,y,-z};
    clauses->push_back(eq1);
    clauses->push_back(eq2);
    clauses->push_back(eq3);
    clauses->push_back(eq4);
}

BasicClauses::~BasicClauses()
{
}