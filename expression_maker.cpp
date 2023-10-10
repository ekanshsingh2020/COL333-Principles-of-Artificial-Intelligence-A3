#include "expression_maker.h"
#pragma once

ExpressionMaker::ExpressionMaker(int num)
{
    bc.clauses = &cnfinput;
    oc.clauses = &cnfinput;
    // bc.equal(1,1);
    n=num;
    for(int i=0;i<2*n;i++)
    {
        adj_mat.push_back(vector<bool>(2*n,false));
    }
    //Need n vars for graph1 - {1,n} - G1 vars
    //Need n vars for graph2 - {n+1,2n} - G2 vars
    helper_vars=2*n+1;
}

void ExpressionMaker::remove_nonedges()
{
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(!adj_mat[i][j])
            {
                bc.or1(-i,-j);
                bc.or1(-i-n,-j-n);
            }
        }
    }
}

void ExpressionMaker::remove_repetition()
{
    for(int i=0;i<n;i++)
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
    vector<int> temp = adder(a,b);
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
        r_half_sum.push_back(trailing_zero);
    }
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
        full_sum.push_back(temp[0]);
    }
    full_sum.push_back(carry_var);
    return full_sum;
}

void ExpressionMaker::add_range(int l, int r, int k)
{
    vector<int> k_bits;
    cout<<"Range addition started"<<endl;
    while(k>0)
    {
        k_bits.push_back(k%2);
        k=k>>1;
    }
    if(k_bits.size()==0)
    {
        k_bits.push_back(0);
    }
    cout<<"Bits of k stored"<<endl;

    vector<int> sum = adder(l,r);
    cout<<"Range adder finished computation, now starting comparison"<<endl;
    for(int i=0;i<k_bits.size();i++)
    {
        if(k_bits[i])
        {
            vector<int> sm1{sum[i]};
            cnfinput.push_back(sm1);
        }
        else
        {
            vector<int> sm2{-sum[i]};
            cnfinput.push_back(sm2);
        }
    }
    for(int j=k_bits.size();j<sum.size();j++)
    {
        vector<int> sm2{-sum[j]};
        cnfinput.push_back(sm2);
    }
}

void ExpressionMaker::process(int k1, int k2)
{
    cout<<"Process hit"<<endl;
    remove_nonedges();
    cout<<"Nonedges removed"<<endl;
    remove_repetition();
    cout<<"No repetition handled"<<endl;

    //adder_1toN should give k1
    //adder_N+1to2N should give k2
    add_range(1,n,k1);
    cout<<"Addition clauses 1 put"<<endl;
    add_range(n+1,2*n,k2);
    cout<<"Addition clauses 2 put"<<endl;

    //addition clauses put
}
