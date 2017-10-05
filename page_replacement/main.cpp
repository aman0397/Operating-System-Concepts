//
//  main.cpp
//  page_replacement
//
//  Created by Aman Khullar on 5/24/17.
//  Copyright © 2017 Aman Khullar. All rights reserved.
//

#include<iostream>
#include<random>

int search(int[],int,int);
struct node{
    int data;
    node *next;
    node *prev;
};

node *search_list(node**,int);

class page_replacement
{
    int reference_string[30];
    int string_size;
    int page_table[10];
    int table_size;
    int f_page_fault=0;
    int l_page_fault=0;
    int head=0;
    int count_list=0;
public:
    page_replacement()
    {
        std::cout<<"Enter the size of the reference string\n";
        std::cin>>string_size;
        std::cout<<"Enter the size of the page table\n";
        std::cin>>table_size;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0,9);
        for(int i=0;i<string_size;i++)
            reference_string[i]=dis(gen);
        for(int i=0;i<10;i++)
            page_table[i]=(-1);
        std::cout<<"the reference string is\n";
        for(int i=0;i<string_size;i++)
            std::cout<<reference_string[i]<<" ";
    }
    void fifo();
    void lru();
    int get_f_page_faults()
    {
        return f_page_fault;
    }
    int get_l_page_faults()
    {
        return l_page_fault;
    }
};

void page_replacement::fifo()
{
    int found=0;
    for(int i=0;i<string_size;i++)
    {
        found=search(page_table,table_size,reference_string[i]);
        if(!found)
        {
            f_page_fault++;
            page_table[head]=reference_string[i];
            head++;
            if(head==table_size)
                head=0;
        }
    }
}

void page_replacement::lru()
{
    node *START=NULL;
    node *temp;
    node *PTR;
    for(int i=0;i<string_size;i++)
    {
        PTR=search_list(&START,reference_string[i]);
        if(PTR==NULL)
        {
            l_page_fault++;
            if(count_list<table_size)
            {
                temp=new node;
                temp->data=reference_string[i];
                if(START==NULL)
                {
                    START=temp;
                    START->prev=START;
                    START->next=START;
                }
                else
                {
                    (START->prev)->next=temp;
                    temp->next=START;
                    temp->prev=START->prev;
                    START->prev=temp;
                    START=temp;
                }
                count_list++;
            }
            else
            {
                temp=new node;
                temp->data=reference_string[i];
                ((START->prev)->prev)->next=temp;
                temp->next=START;
                temp->prev=((START->prev)->prev);
                START->prev=temp;
                START=temp;
            }
        }
        else
        {
            if(START!=PTR)
            {
                (PTR->prev)->next=PTR->next;
                (PTR->next)->prev=PTR->prev;
                (START->prev)->next=PTR;
                PTR->next=START;
                PTR->prev=START->prev;
                START->prev=PTR;
                START=PTR;
            }
        }
    }
}

int search(int x[],int size,int value)
{
    int flag=0;
    for(int i=0;i<size;i++)
    {
        if(x[i]==value)
            flag=1;
    }
    return flag;
}

node *search_list(node **START,int value)
{
    node *PTR=(*START);
    if((*START)==NULL)
        return NULL;
    if(((*START)->data)==value)
        return PTR;
    PTR=PTR->next;
    while(PTR!=(*START))
    {
        if((PTR->data)==value)
            return PTR;
        PTR=PTR->next;
    }
    return NULL;
}

int main()
{
    page_replacement p;
    p.fifo();
    std::cout<<"\nthe number of fifo page faults are\n";
    std::cout<<p.get_f_page_faults()<<"\n";
    p.lru();
    std::cout<<"the number of lru page faults are\n";
    std::cout<<p.get_l_page_faults()<<"\n";
    return 0;
}
