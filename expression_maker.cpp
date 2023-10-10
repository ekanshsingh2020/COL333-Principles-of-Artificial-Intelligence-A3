#include "expression_maker.h"
// #include <cassert>

ExpressionMaker::ExpressionMaker(int num)
{
    bc.clauses = &cnfinput;
    oc.clauses = &cnfinput;
    // bc.equal(1,1);
    n=num;
    for(int i=0;i<((2*n)+1);i++)
    {
        adj_mat.emplace_back(vector<bool>(((2*n)+1),false));
    }
    //Need n vars for graph1 - {1,n} - G1 vars
    //Need n vars for graph2 - {n+1,2n} - G2 vars
    helper_vars=2*n+1;
}

void ExpressionMaker::remove_nonedges(int k2)
{
    if(k2>=0)
    {
        for(int i=1;i<=n;i++)
        {
            for(int j=i+1;j<=n;j++)
            {
                if(!adj_mat[i][j])
                {
                    bc.or1(-i,-j);
                    bc.or1(-i-n,-j-n);
                }
            }
        }
    }
    else
    {
        for(int i=1;i<=n;i++)
        {
            for(int j=i+1;j<=n;j++)
            {
                if(!adj_mat[i][j])
                {
                    bc.or1(-i,-j);
                }
            }
        }
    }   
}

void ExpressionMaker::remove_repetition()
{
    for(int i=1;i<=n;i++)
    {
        bc.or1(-i,-i-n);
    }
}

vector<int> ExpressionMaker::half_adder(int l, int r)
{
    int sum = helper_vars;
    oc.xor1(sum,l,r);
    helper_vars++;
    int carry = helper_vars;
    oc.and1(carry,l,r);
    helper_vars++;
    vector<int> ans{sum,carry};
    return ans;
}

vector<int> ExpressionMaker::full_adder(int a, int b, int c)
{
    vector<int> temp = half_adder(a,b);
    int sum = helper_vars;
    oc.xor1(sum,temp[0],c);
    helper_vars++;
    int carry = helper_vars;
    helper_vars++;
    int gen_carry = helper_vars;
    helper_vars++;
    oc.and1(gen_carry,temp[0],c);
    oc.or1(carry,temp[1],gen_carry);
    vector<int> ans{sum,carry};
    return ans;
}

vector<int> ExpressionMaker::adder(int l, int r)
{
    if((r-l)==1)
    {
        return half_adder(l,r);
    }
    else if((r-l)==2)
    {
        return full_adder(l,l+1,r);
    }

    vector<int> l_half_sum = adder(l,(l+r)/2);
    vector<int> r_half_sum = adder((l+r+2)/2,r);

    if(r_half_sum.size()!=l_half_sum.size())
    {
        int trailing_zero = helper_vars;
        helper_vars++;
        oc.zero(trailing_zero);
        r_half_sum.emplace_back(trailing_zero);
    }
    // // cout<<l<<" "<<r<<" "<<l_half_sum.size()<<" "<<r_half_sum.size()<<"\n";
    // assert(r_half_sum.size()==l_half_sum.size());
    int carry_var=0;
    vector<int> full_sum;
    for(int i=0;i<l_half_sum.size();i++)
    {
        vector<int> temp;
        if(i==0)
        {
            temp = half_adder(l_half_sum[i], r_half_sum[i]);
        }
        else
        {
            temp = full_adder(l_half_sum[i],r_half_sum[i],carry_var);
        }
        carry_var = temp[1];
        full_sum.emplace_back(temp[0]);
    }
    full_sum.emplace_back(carry_var);
    return full_sum;
}

void ExpressionMaker::add_range(int l, int r, int k)
{
    vector<int> k_bits;
    // cout<<"Range addition started"<<endl;
    while(k>0)
    {
        k_bits.emplace_back(k%2);
        k=k>>1;
    }
    if(k_bits.size()==0)
    {
        k_bits.emplace_back(0);
    }
    // cout<<"Bits of k stored"<<endl;
    // // cout<<"Range addition starting "<<l<<" "<<r<<"\n";
    vector<int> sum = adder(l,r);
    // cout<<"Range adder finished computation, now starting comparison"<<endl;
    for(int i=0;i<k_bits.size();i++)
    {
        if(k_bits[i])
        {
            vector<int> sm1{sum[i]};
            cnfinput.emplace_back(sm1);
        }
        else
        {
            vector<int> sm2{-sum[i]};
            cnfinput.emplace_back(sm2);
        }
    }
    for(int i=k_bits.size();i<sum.size();i++)
    {
        vector<int> sm2{-sum[i]};
        cnfinput.emplace_back(sm2);
    }
}

void ExpressionMaker::process(int k1, int k2)
{
    // // cout<<"Process hit"<<endl;
    remove_nonedges(k2);
    // // cout<<"Nonedges removed"<<endl;
    if(k2>=0)
    {
        remove_repetition();
        // // cout<<"No repetition handled"<<endl;
    }
    else
    {
        helper_vars = n+1;
    }
    //adder_1toN should give k1
    //adder_N+1to2N should give k2
    add_range(1,n,k1);
    // // cout<<"Addition clauses 1 put"<<endl;
    if(k2 != -1)
    {
        add_range(n+1,2*n,k2);
    }
    // // cout<<"Addition clauses 2 put"<<endl;

    //addition clauses put
}
