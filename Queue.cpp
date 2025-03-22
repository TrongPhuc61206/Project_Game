#include "Queue.h"
using namespace std;

int frontIndex = 0, rearIndex = -1, sizequeue = 0;
int queue[1000];


void enqueue(int x){
    rearIndex++;
    queue[rearIndex] = x;
    sizequeue++;
}

void dequeue(){
    frontIndex++;
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

