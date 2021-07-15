#include "maleta.h"
#include <pthread.h>
#include <stdlib.h>

typedef struct {
    double *w;
    double *v;
    int *z;
    int n;
    double maxW;
    int k;
    double best;
} Args;

void *thread_function( void *params ){
    Args *p = (Args *) params;
    double *w = p->w;
    double *v = p->v;
    int *z = p->z;
    int n = p->n;
    double maxW = p->maxW;
    int k = p->k;
    p->best = llenarMaletaSec( w , v , z , n , maxW , k );
    return NULL;
}

double llenarMaletaPar(double w[], double v[], int z[], int n, double maxW, int k){
    pthread_t t[8];
    Args args[8];
    int k_pt = k/8;
    double best = 0;
    for (int i = 0; i < 8; i++) {
        args[i].w = w;
        args[i].v = v;
        args[i].z = malloc(sizeof(int)*n);
        args[i].n = n;
        args[i].maxW = maxW;
        args[i].k = k_pt;
        args[i].best = 0;
        pthread_create(&t[i],NULL,thread_function,&args[i]);
    }

    for (int k = 0; k < 8; k++){
        pthread_join(t[k],NULL);

        if (best < args[k].best) {
            best = args[k].best;
            for (int j = 0; j < n; j++) {
                z[j] = args[k].z[j];
            }
        }
        free(args[k].z);
    } 
    return best;
    
}