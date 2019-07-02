#include <stdlib.h>
#include <math.h>
#include "../include/utility.h"


void insertionSort(int *A, int n) {
  int i,j,key;
  for (j=1; j<n; j++){
    key = A[j];
    i = j-1;
    while (i>=0 && A[i]>key){
      A[i+1] = A[i];
      i = i-1;
    }
    A [i+1] = key;
  }
}

void insertionSortbegin(int *A, int begin, int n){
  int i,j,key;
  for (j=begin; j<=begin+n-1; j++){
    key = A[j];
    i = j-1;
    while (i>=begin && A[i]>key){
      A[i+1] = A[i];
      i = i-1;
    }
    A[i+1] = key;
  }
}


int partitionPivot(int *A, int l, int r,int pivot){
  int i,j;
  i = l-1;

  for (j = l; j<= r-1; j++){
    if(A[j] <= pivot) {
      i = i+1;
      swap(&A[i],&A[j]);
    }
  }
    swap(&A[i+1],&A[r]);
    return i+1;
}

void quickSort(int *A, int l, int r, int pivot){
  r = r-1; // to make the call quickSort(A,0,n) insthead of quickSort(A,0,n-1)
  int p;
  while (l<r){
    p = partitionPivot(A,l,r,pivot);
    quickSort(A,l,p-1,pivot);
    l = p+1;
    l++;
  }
}

void countingSort(int *A, int *B, int k, int n)
{
    int C[k];
    for (int i = 0; i <= k; i++)
         C[i] = 0;
    initArray(C,k);
    for (int j = 1; j <= n; j++)
        C[A[j]] = C[A[j]] + 1;
    for (int i = 1; i <= k; i++)
        C[i] = C[i] + C[i-1];
    for (int j = n; j >= 1; j--)
    {
        B[C[A[j]]] = A[j];
        C[A[j]] = C[A[j]] - 1;
    }
}

void radixSort(int *array, int n)
{
    int max = findMaxArray(array, n);
    int auxiliar_array[n];
    initArray(auxiliar_array,n);

    // exp is 10^i where i is current digit number
    for (int exp = 1; max/exp > 0; exp *= 10)
        countingSort(array,auxiliar_array, n, exp);
}

struct Node {
  double value;
  struct Node * next;
};
typedef struct Node Node;

void printBucket(Node* const head){
		if(!head) return;
    Node *aux = head;
    while (aux->next){
        printf("%f ", aux->value);
        aux = aux->next;
    }
		printf("%f\n", aux->value );
 }

 size_t listSize(Node* const head){
 	size_t size = 0;
 	if(!head) return size;
 	Node *aux = head;
 	while (aux->next) {
 		aux=aux->next;
 		size++;
 	}
 	size++;
 	return size;
 }

 void swapNode( Node *a, Node *b){
     double temp = a->value;
     a->value = b->value;
     b->value = temp;
 }

Node* bubbleSort( Node *start){
     int swapped;
     struct Node *ptr1;
     struct Node *lptr = NULL;

     if (start == NULL)
         return start;

     do
     {
         swapped = 0;
         ptr1 = start;

         while (ptr1->next != lptr)
         {
             if (ptr1->value > ptr1->next->value)
             {
                 swapNode(ptr1, ptr1->next);
                 swapped = 1;
             }
             ptr1 = ptr1->next;
         }
         lptr = ptr1;
     }
     while (swapped);
     return start;
 }


Node* append(Node *head, const double value){

  Node *newNode = (Node*) malloc(sizeof(Node));
  newNode->value = value;
  newNode->next = NULL;

  if (head){
    Node *aux = head;
    while (aux->next) aux = aux->next;
    aux->next = newNode;
  }
  else head = newNode;

  return head;
}

double getValueList(Node * head, int j){
  Node *aux = head;
  int idx = 0;
  while (idx++ < j ) aux = aux->next;
  return aux-> value;
}

void bucketSort(double *array, int n)
{
  Node** B = (Node**) malloc(n * sizeof(Node*));
  for (int i = 0; i < n; i++) B[i] = NULL;

  for (int i = 0; i < n; i++) {
    size_t idx = floor(array[i]*n);
    B[idx] = append(B[idx],array[i]);
  }

  for (int i = 0; i < n; i++) B[i] = bubbleSort(B[i]);
  int size;
  int aux_idx=0;
  for (int i = 0; i < n; i++) {
    size = listSize(B[i]);
    for (int j = 0; j < size; j++) {
      array[aux_idx] = getValueList(B[i],j);
      aux_idx++;
    }
  }

  for (int i = 0; i < n; i++) {
    free(B[i]);
  }
  free(B);
}
