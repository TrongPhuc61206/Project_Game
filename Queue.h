#pragma once

extern int MAX_SIZE;
extern int frontIndex, sizequeue, rearIndex;
extern int queue[1000];


void enqueue(int x);
void dequeue();
int front();
bool isEmpty();
bool isFull();



