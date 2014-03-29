#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>



using namespace std;

void quick(char*, char* , int size,  int (*compare) (const void * , const void *));

void Qksrt(void *akeys, int n, int size, int (*compare) (const void * , const void *))
{
 	quick((char*)akeys, (char *) akeys+n*size, size, compare);
}

void quick(char *left, char* right, int size, int (*compare) (const void * , const void *))
{
    char *x;
    x  = (char *) malloc(size*sizeof(char));

    if(right>left){
         char* pivot = left;
         char* i = left+size;
         char* j = right;


    while (i < j){
        if (compare(i, pivot)<=0){

        i=i+size;
        }
        else{
            //exchange keys[i] with keys[j]

            j=j-size;
            memcpy(x,i,size);
            memcpy(i,j,size);
            memcpy(j,x,size);
            }
    }
    i = i - size;
    memcpy(x,left,size);
    memcpy(left,i,size);
    memcpy(i,x,size);
    quick(left,i, size, compare);
    quick( j,right, size, compare);
    }
}


