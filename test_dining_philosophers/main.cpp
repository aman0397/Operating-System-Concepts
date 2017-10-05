//
//  main.cpp
//  test_dining_philosophers
//
//  Created by Aman Khullar on 5/24/17.
//  Copyright © 2017 Aman Khullar. All rights reserved.
//

#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>

std::mutex m;
std::condition_variable cv;

int chopstick[5]={1,1,1,1,1};

void hungry(int p_id)
{
    std::unique_lock<std::mutex> lk(m);
    while(chopstick[p_id]==0||chopstick[(p_id+4)%5]==0)
        cv.wait(lk);
    std::cout<<"philosopher "<<p_id+1<<" is eating\n";
    chopstick[p_id]--;
    chopstick[(p_id+4)%5]--;
    cv.notify_one();
    chopstick[p_id]++;
    chopstick[(p_id+4)%5]++;
    cv.notify_one();
    lk.unlock();
}

/*void finish(int p_id)
{
    std::unique_lock<std::mutex> lk(m);
    while(!(chopstick[p_id]==0&&chopstick[(p_id+4)%5]==0))
          cv.wait(lk);
    std::cout<<"Philosopher "<<p_id+1<<" has finished\n";
    chopstick[p_id]++;
    chopstick[(p_id+4)%5]++;
    cv.notify_one();
    lk.unlock();
}*/
int main()
{
    std::thread philosophers[5];
    std::cout<<"This is the simulation of the dining philosophers problem\n";
    for(int i=0;i<5;i++)
    {
        philosophers[i]=std::thread(hungry,i);
    }
    //for(int i=0;i<5;i++)
      //  philosophers[i]=std::thread(finish,i);
    for(int i=0;i<5;i++)
        philosophers[i].join();
    return 0;
}
