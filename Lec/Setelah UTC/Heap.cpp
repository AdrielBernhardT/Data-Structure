#include <stdio.h>
#define max 100

struct MinHeap{
    int size;
    int arr[max];
};

void swap(int* a, int*b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

int parent(int i){
    return(i-1)/2;
}

int leftChild(int i){
    return(i*2+1);
}

int rightChild(int i){
    return(i*2+2);
}

void insert(MinHeap* heap, int value){
    if(heap->size >= max){
        printf("Full");
        return;
    }

    int i = heap->size;
    heap->arr[i] = value;
    heap->size++;

    // upheap
    while(i != 0 && heap->arr[parent(i)] > heap->arr[i]){
        swap(&heap->arr[parent(i)], &heap->arr[i]);
        i = parent(i);
    }
}

void DownHeap(MinHeap* heap, int i){
    int smallest = i;
    int left = leftChild(i);
    int right = rightChild(i);

    if(left < heap->size && heap->arr[left] < heap->arr[smallest]){
        smallest = left;
    }
    if(right < heap->size && heap->arr[right] < heap->arr[smallest]){
        smallest = right;
    }
    if(smallest != i){
        swap(&heap->arr[i], &heap->arr[smallest]);
        DownHeap(heap, smallest);
    }
}

int extract(MinHeap* heap){
    if(heap->size <= 0){
        printf("Empty");
        return -1;
    }

    int root = heap->arr[0];
    heap->arr[0] = heap->arr[heap->size-1];
    heap->size--;

    DownHeap(heap, 0);
    return root;
}

void printHeap(MinHeap* heap){
    for(int i = 0; i < heap->size; i++){
        printf("%d ", heap->arr[i]);
    }
    printf("\n");
}

int main(){
    MinHeap heap;
    heap.size = 0;

    insert(&heap, 10);
    insert(&heap, 5);
    insert(&heap, 20);
    insert(&heap, 3);
    
    printf("Heap after insertions: ");
    printHeap(&heap);
    extract(&heap);
    printf("Heap after extraction: ");
    printHeap(&heap);
}