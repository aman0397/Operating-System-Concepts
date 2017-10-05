//
//  main.cpp
//  producer_consumer_self
//
//  Created by Aman Khullar on 4/7/17.
//  Copyright © 2017 Aman Khullar. All rights reserved.
//

#include <iostream>
#include<thread>
#include<mutex>
#include<condition_variable>

using namespace::std;
mutex m1;
condition_variable produce,consume;

int empty=10;

void production_unit();
void consumption_unit(int);

int main()
{
    thread producer[10],consumer[10];
    for(int i=0;i<10;i++)
    {
        producer[i]=thread(production_unit);
        consumer[i]=thread(consumption_unit,i+1);
    }
    for(int i=0;i<10;i++)
    {
        consumer[i].join();
        producer[i].join();
    }
}

void production_unit()
{
    unique_lock<mutex> lck(m1);
    while(empty==0) produce.wait(lck);
    empty--;
    consume.notify_one();
}

void consumption_unit(int p_id)
{
    unique_lock<mutex> lck(m1);
    while(empty==10) consume.wait(lck);
    empty++;
    cout<<"for thread\t"<<p_id<<"empty buffers are\t"<<empty<<"\n";
    produce.notify_one();
}
