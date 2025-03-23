#include "Queue.h"
using namespace std;

int frontIndex = 0, rearIndex = -1, sizequeue = 0;
int queue[1000];


void enqueue(int x){
    rearIndex = (rearIndex + 1) % 1000; // Loop mechanism
    queue[rearIndex] = x;
    sizequeue++;
}

void dequeue(){
    frontIndex = (frontIndex + 1) % 1000; // Loop mechanism
    sizequeue--;
}

int front(){
    return queue[frontIndex];
}

bool isEmpty(){
    return sizequeue == 0;
}

bool isFull(){
    return sizequeue == 1000;
}

