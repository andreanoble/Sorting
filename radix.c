//helloa.c
//Andrea Noble	
//CS288

#include <stdio.h>
#include <stdlib.h>clear


int lst[N];
int buf[N];
int group = 8 //should pass as parameter
int buckets = 1<<group;
int cnt[buckets] = 0;
int map[buckets] = 0;
int mask[buckets] = 0;


for (i = 0; i<N; i++){

	cnt[lst[i] & mask]++;
	//map
	map[0] = 0;
	for(i = 1; i<buckets; i++)
		map[i] = cnt[i-1]+map[i-1]

	//move from lst ot buffer
	for(i = 0; i<N; i++)
		src = lst[i] //source
		dest = map[lst[i] & mask]; //destion index of buffer

		lst[i] = buf[dest++];



}