//int_radix_sort
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <sys/time.h>
#include <stdint.h>

#define OK 1
#define NOK 0
#define NELM 10	/* default 100 elements */
//#define N 1048576		/* 2^30 or 1 meg elements  */
//#define N 2097152
//#define N 4194304
//#define N 8388608
//#define N 16777216
#define N 33554432

void selection_sort();
void swap();

void merge_sort();
void msort_recursive();
void merge();


void int_radix_sort();
void float_radix_sort();
void swap();
void self_check();

int rand(void);
void srand();
int rand_r();
void init_lst();
void print_lst();

int n, lst[N],tmp[N];

int main(int argc,char **argv) {

  long int del_sec,del_msec;
  struct timeval tv_s,tv_e;

  if (argc>1) n = atoi(argv[1]);
  else n = NELM;
  printf("n=%d\n",n);
  init_lst(lst,n);
  //  print_lst(lst,n);

  gettimeofday(&tv_s, NULL); 
  //  selection_sort(lst,n);
  //  merge_sort(lst,tmp,n);
    int_radix_sort(lst,tmp,n);
  //  float_radix_sort(lst,tmp,n);
  gettimeofday(&tv_e, NULL); 

  /****
    PRINT elapsed time in sec and milli secs
  ****/
   del_sec = (tv_e.tv_sec -tv_s.tv_sec);
  del_msec = (tv_e.tv_usec -tv_s.tv_usec) / 10000;
  printf("%1li.%06li for %d elements\n", del_sec, del_msec, NELM );

  //  print_lst(lst,n);
  self_check();
  return 0;
}

void int_radix_sort(int lst[], int temp[], int n){
	int group=8;			/* 8 bits per pass (or round) */
 	int bucket = 1 << group;	/* number of buckets = 256 */
  	// fill here
	int cnt[bucket];
	int map[bucket];
	int mask = bucket - 1;
	int *src, *dest;
	int i,j,k ,x;
	

	for(x = 0; x<4; x++){
		//flag
		if((x % 2) == 0){
			src = lst;
			dest = temp;
		}
		else
		{
			src = temp;
			dest = lst;
		}

		//init the count
		for(i = 0; i < bucket; i++)
		{
			cnt[i] = 0;
		}
		//compute count
		for(i = 0; i < n; i++)
		{
			cnt[(src[i] >>(group*x)) & mask]++;
		}


		//map
		for (i = 0; i< n; i++){	
		map[0] = 0;
		}
		for(i = 0; i<bucket; i++){
			map[i] = cnt[i-1] + map[i-1];
		}

		//move from lst ot buffer
		for(i = 0; i< n; i++){
			temp = map[(src[i] >> (group*x)) & mask];
			dest[temp]++ = src[i];
			
		}
	}
}

//fix the bucket size to 256. run 4 passes where each pass processes 8 bits
//use lst and tmp only. do not use any more memory of size n.
void radix_sort(int ii) {
  int group=8;			/* 8 bits per pass (or round) */
  int bucket = 1 << group;	/* number of buckets = 256 */
  // fill here
}

void print_lst(int *l,int n){
  int i;
  for (i=0; i<n; i++) {
    printf("%d ",l[i]);
  }
  printf("\n");
}

void init_lst(int *l,int n){
  int i;
  //  int seed = time(0) % 100;	/* seconds since 1/1/1970 */
  //  printf ("seed=%d\n", seed);
  srand(1234);			/* SEED */
  for (i=0; i<n; i++) {
    l[i] = rand();
  }
}

void self_check(int *list,int n) {
  int i,j,flag=OK,*listp;

  listp = list;
  for (i=0;i<n-1;i++)
     if (listp[i] > listp[i+1]) { flag = NOK; break; }

  if (flag == OK) printf("sorted\n");
  else printf("NOT sorted at %d\n",i);
}