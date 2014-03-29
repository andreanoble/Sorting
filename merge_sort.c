
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <sys/time.h>
#include <stdint.h>

#define OK 1
#define NOK 0
#define NELM 100000	/* default 100 elements */
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
  merge_sort(lst,tmp,n);
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

void merge_sort(int list[], int temp[], int n){
  msort_recursive(list, temp, 0, n-1);
}

//use recursion
void msort_recursive(int list[], int temp[], int left, int right){
  // fill here
  int mid;
  if (right>left){
    mid = (right + left)/2;
    msort_recursive(list, temp, left, mid);
    msort_recursive(list, temp, mid+1, right);
    merge(list, temp, mid+1, right);
  }
}

void merge(int list[], int temp[], int left, int mid, int right){
  int i, left_end, num_elements, tmp_pos;
  left_end =  mid - 1;
  tmp_pos = left;
  num_elements = right - left + 1;

  while((left <= left_end) && (mid <= right)){
    if (list[left] <= list[mid]){
      temp[tmp_pos] = list[left];
      tmp_pos++;
      left_end++;
    }
    else{
      temp[tmp_pos] = list[mid];
      tmp_pos++;
      mid++;
    }
  }

  while (left <= left_end){
    temp[tmp_pos] = list[left];
    left++;
    tmp_pos++;
  }

  while ( mid <= right){
    temp[tmp_pos] = list[mid];
    mid++;
    tmp_pos++;
  }

  for ( i =0; i  <= num_elements; i++){
    list[right] = temp[ right];
    right = right--;
  }
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