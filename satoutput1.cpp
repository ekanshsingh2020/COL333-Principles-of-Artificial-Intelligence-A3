#include <iostream>
#include <fstream>
#include <vector>

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
    // // cout<<"Input started2"<<endl;
    int n;
    graph_input>>n;
    // // cout<<n<<"\n";
    graph_input.close();
    // // cout<<"Input started3"<<endl;
    // infile = argv[1];
    postname = ".satoutput";
    ingraph = infile + postname;
    // // cout<<"Input started4"<<endl;

    ifstream sat_input;
    sat_input.open(ingraph);
    // // cout<<"Input started5"<<endl;
    // int n,m,k1,k2,a,b;
    string satisfiability;
    sat_input>>satisfiability;
    vector<int> result;
    // // cout<<"Input started6"<<endl;
    int a;
    if(satisfiability == "SAT")
    {
        for(int i=0;i<2*n;i++)
        {
            sat_input>>a;
            result.push_back(a);
            // // cout<<i<<" ";
        }
    }
    sat_input.close();
    // // cout<<"Input ended"<<endl;

    ofstream sat_output;
    postname = ".mapping";
    string outgraph = infile + postname;
    sat_output.open(outgraph);
    //Printing the clauses made in processing for sat input
    if(satisfiability == "UNSAT")
    {
        sat_output<<"0\n";
    }
    else
    {
        sat_output<<"#1\n";
        bool printed_smt = false;
        for(int i=0;i<n;i++)
        {
            if(result[i]>0)
            {
                if(printed_smt){sat_output<<" "<<result[i];}
                else{sat_output<<result[i];printed_smt=true;}
            }
        }
        sat_output<<"\n#2\n";
        printed_smt = false;
        for(int i=n;i<2*n;i++)
        {
            if(result[i]>0)
            {
                if(printed_smt){sat_output<<" "<<result[i]-n;}
                else{sat_output<<result[i]-n;printed_smt=true;}
            }
        }
    }
    sat_output.close();
    // // cout<<"Done"<<endl;
}