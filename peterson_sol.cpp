//
//  main.cpp
//  Petersons_solution
//
//  Created by Aman Khullar on 3/26/17.
//  Copyright © 2017 Aman Khullar. All rights reserved.
//

#include<iostream>
#include<stdio.h>
#include<pthread.h>
using namespace::std;
#define MAX 10000;
int sum=0;

int turn;
bool flag[2];

void entry_init()
{
    flag[0]=flag[1]=false;
    turn=0;
}
void entry(int self)
{
    flag[self]=true;
    turn=1-self;
    while(flag[1-self]==true&&turn==1-self);
}
void exit(int self)
{
    flag[self]=false;
}

void *runner(void *param);
int main(int argc,char *argv[])
{
    pthread_t p1,p2;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    entry_init();
    
    pthread_create(&p1,&attr,runner,argv[0]);
    pthread_create(&p2,&attr,runner,argv[1]);
    
    pthread_join(p1,NULL);
    pthread_join(p2,NULL);
    
    cout<<"actual count calculated\t"<<sum<<"\n"<<"expected count\t"<<2*MAX;
    return 0;
}

void *runner(void *param)
{
    int i=0;
    int self= (int *)param;
    //entry section
    entry(self);
    //critical section
    for(;i<10000;i++)
    {
        sum++;
    }
    //exit section
    exit(self);
}