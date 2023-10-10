#include "expression_maker.cpp"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv)
{
    cout<<"Binary started"<<endl;
    string infile = argv[1];
    string postname = ".graph";
    string ingraph = infile + postname;
    cout<<ingraph<<endl;
    cout<<"Input started"<<endl;
    ifstream graph_input; 
    graph_input.open(ingraph);
    int n,m,k1,k2,a,b;
    graph_input>>n>>m>>k1>>k2;
    cout<<n<<" "<<m<<" "<<k1<<" "<<k2<<"\n";

    cout<<"Input finished"<<endl;
    // vector<vector<bool>> adjacency_mat(n,vector<bool>(n,false));
    //Storing input in adjacency matrix representation
    ExpressionMaker em(n);
    for(int i=0;i<m;i++)
    {
        graph_input>>a>>b;
        em.adj_mat[a-1][b-1] = true;
        em.adj_mat[b-1][a-1] = true;
        em.adj_mat[a+n-1][b+n-1] = true;
        em.adj_mat[b+n-1][a+n-1] = true;
    }
    graph_input.close();

    // for(int i=0;i<2*n;i++)
    // {
    //     for(int j=0;j<2*n;j++)
    //     {
    //         cout<<em.adj_mat[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }

    cout<<"Process started"<<endl;
    //The entire pipeline starts
    em.process(k1,k2);

    cout<<"Process ended"<<endl;

    ofstream graph_output;
    postname = ".satinput";
    string outgraph = infile + postname;
    graph_output.open(outgraph);
    //Printing the clauses made in processing for sat input 
    for(int i=0;i<em.cnfinput.size();i++)
    {
        for(int j=0;j<em.cnfinput[i].size();j++)
        {
            graph_output<<em.cnfinput[i][j]<<" ";
        }
        graph_output<<"\n";
    }
    graph_output.close();
    cout<<"Done"<<endl;
}