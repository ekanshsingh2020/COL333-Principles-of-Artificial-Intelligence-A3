#include "expression_maker.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
    // // cout<<"Binary started"<<endl;
    string infile = argv[1];
    string postname = ".graph";
    string ingraph = infile + postname;
    // // cout<<ingraph<<endl;
    // // cout<<"Input started"<<endl;
    ifstream graph_input; 
    graph_input.open(ingraph);
    int n,m,k1,k2,a,b;
    graph_input>>n>>m;
    // // cout<<n<<" "<<m<<" "<<k1<<" "<<k2<<"\n";

    // // cout<<"Input finished"<<endl;
    // vector<vector<bool>> adjacency_mat(n,vector<bool>(n,false));
    //Storing input in adjacency matrix representation
    ExpressionMaker em(n);
    for(int i=0;i<m;i++)
    {
        graph_input>>a>>b;
        em.adj_mat[a][b] = true;
        em.adj_mat[b][a] = true;
    }
    graph_input.close();

    // // cout<<"Process started"<<endl;
    //The entire pipeline starts
    k1 = stoi(argv[2]);
    em.process(k1,-1);

    // // cout<<"Process ended"<<endl;

    ofstream graph_output;
    postname = ".satinput";
    string outgraph = infile + postname;
    graph_output.open(outgraph);
    //Printing the clauses made in processing for sat input 
    graph_output<<"p cnf "<<em.helper_vars-1<<" "<<em.cnfinput.size()<<"\n";
    for(int i=0;i<em.cnfinput.size();i++)
    {
        for(int j=0;j<em.cnfinput[i].size();j++)
        {
            graph_output<<em.cnfinput[i][j]<<" ";
        }
        graph_output<<"0\n";
    }
    graph_output.close();
    // // cout<<"Done"<<endl;
}