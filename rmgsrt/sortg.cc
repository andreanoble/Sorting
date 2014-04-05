#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <iostream>
#include <fstream>
#define DEBUG 1
#define	FEW	8
using namespace std;

/* Set DEBUG to 1 to print few element before and after the sort */
/* This piece of code is to assist you. Don't expect comments on what it
   does (it's obvious); If you find it useful use it, otherwise discard it.
 */

extern clock_t clock();
void rmgsrt(void *, int , int , int (*compare) (const void * , const void *));

int compare(const void  *x,const void  *y)
{
	return(* ((int*)x)-*((int *)y));
}


int main(int argc,char *argv[])
{
	int i,j,n,runs;
	int *ptr,*bptr;
	clock_t t1,t0;
	size_t n_t;
   	double elapsed;

	n=1000;runs=1;
        if ( 1 == argc ) {
	      cout << "Usage: "  << argv[0] << " size " <<endl;
	      exit(1);
	} else {
	      n = atoi(argv[1]);
	}

	ptr= (int*) malloc(n*sizeof(int));
	bptr= (int*) malloc(n*sizeof(int));

	n_t =  (size_t) n;

	for(i=0;i<n_t;i++)
//          bptr[i]=ptr[i] = (int) (n_t*(rand()/((double) RAND_MAX)));
//          bptr[i]=ptr[i] = RAND_MAX;  //data set 2.4
//          bptr[i]=ptr[i] = 1234;   //data set 2.1
          bptr[i]=ptr[i] = n_t -i;   //data set 2.3
//          bptr[i]=ptr[i] = i+1;         //data set 2.2


/* generic qsort */
        if (DEBUG) {
	  for(i=0;i<FEW;i++)
            cout << ptr[i] << " ";
          cout << "...";
	  for(i=n_t-FEW;i<n_t;i++)
            cout << ptr[i] << " ";
          cout << endl;
        }
	elapsed=0.0;
        for(j=0;j<runs;j++){
	   for(i=0;i<n_t;i++) ptr[i] = bptr[i];
	   t0=clock();
             qsort(ptr,(size_t) n_t,sizeof(int),compare);
           t1=clock();
	   elapsed +=(t1-t0)/((double)CLOCKS_PER_SEC);
	}

        if (DEBUG) {
	  for(i=0;i<FEW;i++)
            cout << ptr[i] << " ";
          cout << "...";
	  for(i=n_t-FEW;i<n_t;i++)
            cout << ptr[i] << " ";
          cout << endl;

        }
        printf("qsort generic:Elapsed time is %10.8f\n",elapsed/runs);
	for(i=0;i<n_t-1;i++)
           if (ptr[i] > ptr[i+1] )  {
                 cout <<"qsort does not sort! \n" <<endl;
                 fflush(stdout);
        }

/* End of qsort */

	for(i=0;i<n_t;i++)
           ptr[i]=bptr[i] ;

/* Insertion sort */
        if (DEBUG) {
	  for(i=0;i<FEW;i++)
            cout << ptr[i] << " ";
          cout << "...";
	  for(i=n_t-FEW;i<n_t;i++)
            cout << ptr[i] << " ";
          cout << endl;
        }
	elapsed=0.0;
        for(j=0;j<runs;j++){
	   for(i=0;i<n_t;i++) ptr[i] = bptr[i];
	   t0=clock();
             rmgsrt(ptr,n_t,sizeof(int),compare);
           t1=clock();
	   elapsed +=(t1-t0)/((double)CLOCKS_PER_SEC);
	}

        if (DEBUG) {
	  for(i=0;i<FEW;i++)
            cout << ptr[i] << " ";
          cout << "...";
	  for(i=n_t-FEW;i<n_t;i++)
            cout << ptr[i] << " ";
          cout << endl;
        }
        printf("MergeSort:Elapsed time is %10.8f\n",elapsed/runs);
	for(i=0;i<n_t-1;i++)
           if (ptr[i] > ptr[i+1] )  {
                 cout <<"Mergesort does not sort! \n" <<endl;
        }

	free((void *) ptr);
	free((void *) bptr);
}



