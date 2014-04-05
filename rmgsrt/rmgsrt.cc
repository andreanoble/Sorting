//Andrea Noble PA_1_2757:rmgsrt.cc

#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>



using namespace std;

int mergesort(int*, int,int, int size,  int (*compare) (const void * , const void *));
int mrg(int*, int, int, int, int size, int (*compare) (const void * , const void *));


void rmgsrt(void *akeys, int n, int size, int (*compare) (const void * , const void *))
{
    int    *keys;
    keys= (int *) akeys;
    mergesort(keys,0,n, size, compare);
}

int mergesort(int keys[],  int low, int high, int size,  int (*compare) (const void * , const void *))
{
    int pivot;

    if (high>low){
        pivot=(low+high)/2;
        mergesort(keys, low, pivot, size, compare);
        mergesort(keys, (pivot+1), high, size, compare);
        mrg(keys, low,pivot, high, size, compare);
        }
        return 0;
}

int mrg(int keys[],int l,int m,int h, int size,  int (*compare) (const void * , const void *))
{
    int n1,n2,i,j,k;
    n1=m-l+1;
    n2=h-m;

    int    *tmpkeys1;
    tmpkeys1 = (int *) malloc((n1+n2)*sizeof(int));
    int   *tmpkeys2;
    tmpkeys2 = (int *) malloc((n1+n2)*sizeof(int));

    for(i=0; i<n1; i++)
        tmpkeys1[i]=keys[l+i];
    for(j=0; j<n2; j++)
        tmpkeys2[j]=keys[m+j+1];

    tmpkeys1[i]=9999999;
    tmpkeys2[j]=9999999;

    i=0;
    j=0;
    for(k=l; k<=h; k++) {
        if(tmpkeys1[i]<=tmpkeys2[j])
            keys[k]=tmpkeys1[i++];
        else
            keys[k]=tmpkeys2[j++];
        }
        free ((void* )tmpkeys1);
        free((void*) tmpkeys2);
    return 0;
}
