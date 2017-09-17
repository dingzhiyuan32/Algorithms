//
//  bucketSort.cpp
//  Bucket-sort an array with List.
//
//  @Zhiyuan Ding.
//

#include <iostream>
using namespace std;

//The definition of nodes in the list
typedef struct Node
{
    int data;                             //data is the key for the sort
    Node *next;                           //next is the pointer to the next node
}Node;

//MAX is the number of elements in the array to be sorted
#define MAX 20
//BKTNB is the number of bucket using in bucketSort
#define BKTNB 10

//number[] is the array to be sorted
int number[MAX] = {667, 734, 602, 436, 911, 110, 23, 758,
    333, 867, 610, 1, 99, 890, 111, 773, 433, 778, 725, 644};

//print the data of every element in the list
//@param n The pointer to the first node of the list
void prt(Node *n)
{
    Node *temp = n;                  //use temp to get every element in the list
    while(temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

//count the length of a list
//@param n The pointer to the first node of the list
int getLength(Node *n)
{
    int i = 0;
    Node *temp = n;
    while(temp != NULL)
    {
        i++;
        temp = temp->next;
    }
    return i;
}

//use insertion sort to sort a list (a bucket used in bucketSort)
//@param n The pointer to the first node of the bucket
void insertionSort(Node *&n)
{
    if(getLength(n) >= 2)        //the sort is not necessary when the length < 2
    {
        
        Node *key = n;                       //the elements before key is sorted
        while(key != NULL && key->next != NULL)
        {
            //insert current to the sorted list before key
            Node *current = key->next;
            Node *temp = n;
            key->next = current->next;
            if(n->data > current->data)
            {
                current->next = n;
                n = current;
            }
            else
            {
                while(temp->next != NULL &&
                      temp->next->data <= current->data && temp != key)
                {
                    temp = temp->next;
                }
                current->next = temp->next;
                temp->next = current;
            }
            key = key->next;             //move key to next after insert current
        }
    }
}

//use bucket sort to sort the list
//@param n The pointer to the firsr node of the list
//@param min The minimum of the element
//@param max The maximum of the element
void bucketSort(Node n[], int min, int max)
{
    int len = getLength(n);                          //the length of the list
    int k = (max - min) / BKTNB;                     //the width of the bucket
    Node *bucket[BKTNB];                             //the bucket list
    Node *bucketTop[BKTNB];          //the pointer to the last element in bucket
    for(int i = 0; i < BKTNB; i++)
        bucket[i] = bucketTop[i] = NULL;
    for(int i = 0; i < len; i++)
    {
        int bn = (n[i].data - min) / k;              //decide which bucket
        Node *temp = (Node *) malloc (sizeof(Node)); //create a new node
        temp->data = n[i].data;                      //copy the data of n[i]
        temp->next = NULL;
        if(bucket[bn] == NULL)                       //insert temp to bucket
        {
            bucket[bn] = bucketTop[bn] = temp;
        }
        else
        {
            bucketTop[bn]->next = temp;
            bucketTop[bn] = bucketTop[bn]->next;
        }
    }
    cout << endl << "every bucket before insertion sort:" << endl;
    for(int i = 0; i < BKTNB; i++)                   //print bucket before sort
    {
        prt(bucket[i]);
    }
    for(int i = 0; i < BKTNB; i++)                   //insertion sort buckets
    {
        insertionSort(bucket[i]);
    }
    cout << endl << "every bucket after insertion sort"  << endl;
    for(int i = 0; i < BKTNB; i++)                   //print bucket after sort
    {
        prt(bucket[i]);
    }
    Node *list = n;        //change the data of element in list n with new order
    for(int i = 0; i < BKTNB; i++)
    {
        Node *bkt = bucket[i];
        while(bkt != NULL)
        {
            list->data = bkt->data;
            bkt = bkt->next;
            list = list->next;
        }
    }
}

//main function
int main()
{
    Node n[MAX];                                     //a list to be sorted
    for(int i = 0; i < MAX; i++)                     //copy array to a new list
    {
        n[i].data = number[i];
        if(i == MAX - 1)
        {
            n[i].next = NULL;
        }
        else
        {
            n[i].next = &n[i+1];
        }
    }
    cout << "list before sort:" << endl;
    prt(n);                                          //print list before sort
    bucketSort(n, 0, 1000);
    cout << endl << "list after sort:" << endl;
    prt(n);                                          //print list after sort
    return 0;
}
