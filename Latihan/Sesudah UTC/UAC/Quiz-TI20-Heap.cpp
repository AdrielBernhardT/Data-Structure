#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max 1000

struct node {
    char name[35];
    int priority;
} curr;

struct Heap {
    int size;
    node arr[max];
};

void swap (node* a, node* b) {
    node temp = *a;
    *a = *b;
    *b = temp;
}

int parentIndex(int index) {
    return (index-1)/2;
}

int leftChild(int index) {
    return index*2 + 1;
}

int rightChild(int index) {
    return index*2 + 2;
}

void Insert(Heap* heap) {
    if (heap->size >= max) {
        printf("Heap is full\n");
        return;
    }

    int i = heap->size;

    // assign curr ke heap terbaru
    heap->arr[i].priority =  curr.priority; 
    strcpy(heap->arr[i].name, curr.name);
    heap->size++;

    while (heap->size >= 0 && heap->arr[i].priority < heap->arr[parentIndex(i)].priority) {
        swap(&heap->arr[i], &heap->arr[parentIndex(i)]);
        i = parentIndex(i);
    }   
}

void downHeap(Heap* heap, int i) {
    int smallest = i;
    int left = leftChild(i);
    int right = rightChild(i);

    if (left < heap->size && heap->arr[left].priority < heap->arr[smallest].priority) {
        smallest = left;
    }


    if (right < heap->size && heap->arr[right].priority < heap->arr[smallest].priority) {
        smallest = right;
    }

    if (smallest != i) {
        swap(&heap->arr[i], &heap->arr[smallest]);
        downHeap(heap, smallest);
    }
}

node extract(Heap *heap) {
    if(heap->size <= 0) {
        printf("Heap Empty\n");
        return;
    }

    node root = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;

    downHeap(heap,0);
    return root;
}

void printHeap(Heap* heap){
    for(int i = 0; i < heap->size; i++){
        printf("%d ", heap->arr[i]);
    }
    printf("\n");
}

int main(){
    int T;
    char prosedur[15];
    
    Heap heap;
    heap.size = 0;

    scanf("%d", &T); getchar();
    for(int i = 0; i < T; i++) {
        scanf("%s", prosedur); getchar();
        if (strcmp(prosedur, "ADD") == 0) {
            scanf("%s %d", curr.name, & curr.priority); getchar();
            Insert(&heap);
        } else {
            extract(&heap);
        }
    }

    printHeap(&heap);
    return 0;
}