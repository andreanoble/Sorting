#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void msort(void *b, size_t n, size_t s, int (*compare)(const void *v1, const void *v2) )
{
    if (n <= 1)
        return;     /* Already sorted */

    printf("-->> msort(%zu)\n", n);
   // dump_array(stdout, "Entry to msort()", (int *)b, n);
    void *t = malloc(s*n);

    if (t == NULL)
    {
        fprintf(stderr, "Error: No Memory.\n");
        printf("<<-- msort(%zu)\n", n);
        return;
    }

    size_t n1 = n / 2;
    size_t n2 = n - n1;

    char *b1 = (char *) b;
    char *b2 = (char *) b + (n1 * s);

    msort(b1, n1, s, compare);
    msort(b2, n2, s, compare);

    char *tmp = (char *)t;

    while (n1 > 0 && n2 > 0)
    {
        if ((*compare)(b1, b2) <= 0)
        {
            memcpy(tmp, b1, s);
            tmp += s;
            b1 += s;
            --n1;
        }
        else
        {
            memcpy(tmp, b2, s);
            tmp += s;
            b2 += s;
            --n2;
        }
    }
    if (n1 > 0)
        memcpy(tmp, b1, n1 * s);
    else if (n2 > 0)
        memcpy(tmp, b2, n2 * s);
    memcpy(b, t, n * s);
    free(t);

//    dump_array(stdout, "Exit from msort()", (int *)b, n);
 //   printf("<<-- msort(%zu)\n", n);
}




