//
//  main.cpp
//  Reader_writers
//
//  Created by Aman Khullar on 3/27/17.
//  Copyright © 2017 Aman Khullar. All rights reserved.
//

#include<iostream>
using namespace::std;

int main()
{
    int n=0,at[30],bt[30],wt[30],tat[30],sum;
    cout<<"enter the number of processes\n";
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cout<<"Enter the Arrival time of P["<<i+1<<"]\t";
        cin>>at[i];
        cout<<"Enter the Burst time of P["<<i+1<<"]\t";
        cin>>bt[i];
    }
    sum=at[0];
    for(int i=0;i<n;i++)
    {
        wt[i]=sum-at[i];
        sum+=bt[i];
        tat[i]=bt[i]-at[i];
    }
    cout<<"PROCESS \t WT \t TAT\n";
    for(int i=0;i<n;i++)
    {
        cout<<"P["<<i+1<<"]\t\t"<<wt[i]<<"\t\t"<<tat[i]<<"\n";
    }
    return 0;
    
}
