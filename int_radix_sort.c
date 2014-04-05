//int_radix_sort
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <sys/time.h>
#include <stdint.h>

#define OK 1
#define NOK 0
#define NELM 10000000	/* default 100 elements */
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
void dump_array();
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
   // print_lst(lst,n);

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
  printf("%1li.%06li for %d elements\n", del_sec, del_msec, n );
  printf("---------------------------------\n");
  //print_lst(lst,n);
 // printf("----------------------------------\n");
    
  //self_check(lst,n);

  return 0;
}

void int_radix_sort(int lst[], int temp[], int n){
	int group=8;			/* 8 bits per pass (or round) */
  int rounds = 4;
 	int bucket = 1 << group;	/* number of buckets = 256 */
  	// fill here
	int cnt[bucket];
	int map[bucket];
	int mask = bucket - 1;
	int *src, *dest;
	int i,j,k, a,x, idx;
  int flag = 0;
	idx = 32;
  for(a=0; a<n; a++){
    temp[a]=0;
  }

	for(x = 0; x<idx; x = x + group){
    
    //printf("buckets %d\n", bucket);
    //printf("x %d\n", x);
		//flag
		if(( x % 2) == 0){
			src = lst;
			dest = temp;
		}
		/*else{
			src = temp;
			dest = lst;
		}
    */

		 //init the count
		for(i = 0; i < bucket; i++){
			cnt[i] = 0;
		}
		//compute count
		for(j = 0; j < n; j++)
		{
			cnt[src[j]>>x & mask]++;
      k=src[j]>>x & mask;
     // printf("src  %x  k  %x cnt  %x\n",src[j], k, cnt[k]);
     // dump_array("cnt : ", n, cnt);
		}
    
    //dump_array("src : ", n, src);
    //dump_array("cnt : ", n, cnt);

		//init map 
		for (i = 0; i < bucket; i++){	
		  map[i] = 0;
		}

    //map
		for(k = 1; k<=bucket; k++){
			map[k] = (cnt[k-1] + map[k-1]);
		//printf("%x  map %x       %x\n", k, map[k] , cnt[k-1]);
    }
    //dump_array("map : ", n, map);

		//move from lst ot buffer
		for(i = 0; i< n; i++){
     // printf("%d     %d\n", src[i],src[i]>>x & mask);

			dest[map[src[i]>>x & mask]++] = src[i];

      //printf("%x  map %x      dest %x   src  %x\n", i, map[src[i]>>x & mask] , dest[map[src[i]>>x & mask]], src[i]);
      //lst[i] =dest[i];	
		}
   //printf("x %d*****************************\n", x);
   //print_lst(dest,n);
	}
  for (i = 0; i<n;  i++)
    lst[i] = dest[i];
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
    printf("0x%08x \n",l[i]);
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
  for (i=0;i<n-1;i++){
    //printf("self check    %x\n",list[i] );
     if (listp[i] > listp[i+1]) 
      { flag = NOK;}
       // printf("listp[i] = %x listp[i+1] = %x\n", listp[i], listp[i+1]);
  if (flag == OK) printf("sorted\n");
  else printf("NOT sorted at %d\n",i);
  }
}

void dump_array(char * message, int size, int a[])
{
  printf("%s\n", message);

  int i;
  for(i = 0; i < size; i++)
  {
    printf("i: %d cnt: int %d hex: 0x%08x\n", i, a[i], a[i]);
  }
}