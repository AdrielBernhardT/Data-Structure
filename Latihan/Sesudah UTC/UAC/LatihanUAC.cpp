#include <stdio.h>
#include <stdlib.h>

#define max 100

struct minHeap {
    int size;
    int arr[max];
};

void swap (int*a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int parent(int i){
    return (i - 1) / 2;
}

int leftChild(int i){
    return (2 * i + 1);
}

int rightChild(int i){
    return (2 * i + 2);
}

void insert(minHeap* heap, int value) {
    if(heap->size >= max) { // cek array heap max
        printf("Full\n");
        return;
    }

    int i = heap->size;
    heap->arr[i] = value;
    heap->size++;

    while (i != 0 && heap->arr[parent(i)] > heap->arr[i]) {
        swap(&heap->arr[parent(i)], &heap->arr[i]);
        i = parent(i); // Memperbarui index dari heap current yang di swap biar bisa menentukan apakah perlu di swap lagi ga
    }
}

// downHeap di pakai untuk memperbaiki heap tree setelah ambil paling kecil

void downHeap(minHeap* heap, int urutan) {
    int smallest = urutan;
    int left = leftChild(urutan);
    int right = rightChild(urutan);

    if (left < heap->size && heap->arr[left] < heap->arr[smallest]) {
        smallest = left;
    }

    if (right < heap->size && heap->arr[right] < heap->arr[smallest]) {
        smallest = right;
    }

    if (smallest != urutan) { // kalau smallest berubah
        swap(&heap->arr[urutan], &heap->arr[smallest]); // swap value sekarang dengan smallest
        downHeap(heap,smallest); // lakuin sampe smallest ini bener bener paling kecil antara kanan dan kiri
    }
}

int extract(minHeap *heap) {
    if(heap->size <= 0) {
        printf("Heap Empty\n");
        return -1;
    }

    int root = heap->arr[0]; // root adalah heap ke 0 (awal)
    heap->arr[0] = heap->arr[heap->size - 1]; // ubah value awal dengan value akhir
    heap->size--;

    downHeap(heap, 0); // perbaiki susunan dengan downHeap
    return root;
}

void printHeap(minHeap* heap) {
    for (int i = 0; i < heap->size; i++){
        printf("%d ", heap->arr[i]);
    }
    printf("\n");
}

int main(){
    minHeap curr;
    curr.size = 0;

    insert(&curr, 10);
    insert(&curr, 5);
    insert(&curr, 20);
    insert(&curr, 3);

    printf("Heap after insertions: ");
    printHeap(&curr);

    extract(&curr);
    printf("Heap after extraction: ");
    printHeap(&curr);

    return 0;
}