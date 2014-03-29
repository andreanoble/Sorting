//Andrea Noble PA_1_2757:inssrt.cc

#include <stdlib.h>
#include <string.h>
using namespace std;

void inssrt(void *akeys, int n, int size, int (*compare) (const void * , const void *))
{
	register int i,j;
	char	*x;
        char    *keys;

        keys= (char *) akeys;
	x = (char *) malloc(size*sizeof(char));
	for(i=1;i<=n-1;i++) {
		memcpy(x,&keys[i*size],size);
		j=i-1;
		while(j>-1 && (compare(&keys[j*size],x)>0)) {
                memcpy(&keys[(j+1)*size],&keys[j*size],size);
                memcpy(&keys[j*size],x,size);
                j--;
			}
		}
        free((char *)x);
}
