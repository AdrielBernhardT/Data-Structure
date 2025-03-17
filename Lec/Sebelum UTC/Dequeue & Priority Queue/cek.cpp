#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

int priorityQueue[MAX_SIZE]; 
int queueSize=0; 

//10 5 4 Prioritas angka terkecil (Front di belakang) 
void enqueue(int value){
	if(queueSize==MAX_SIZE){
		printf("Priority Queue overflow. Cannot enqueue %d.\n"); 
		return; 
	}
	int i=queueSize-1; 
	//Shift elements to make space for the new element in sorted order 
	while(i>=0 && priorityQueue[i]<value){
		priorityQueue[i+1]=priorityQueue[i]; 
		i--; 
	}
	priorityQueue[i+1]=value; 
	queueSize++; 
	printf("%d enqueued into the priority queue.\n", value); 
}

//Function to dequeue the element wuth the highest priority 
int dequeue(){
	if(queueSize==0){
		printf("Priority Queue underflow. Cannot dequeue from an empty priority queue.\n"); 
		return -1; //Signifies an error condition 
	}
	int front=priorityQueue[queueSize-1]; 
	queueSize--; 
	return front;
}