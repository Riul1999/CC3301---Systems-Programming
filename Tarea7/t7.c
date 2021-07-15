#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <sys/types.h>
#include <sys/wait.h>


#include "viajante.h"


int leer(int fd, void *vbuf, int n) {
  char *buf= vbuf;
  do {
    int rc= read(fd, buf, n);
    if (rc<=0)
      return 1; /* fracaso: error o fin del archivo/pipe/socket */
    n-= rc; /* descontamos los bytes leídos */
    buf+= rc; /* avanzamos el buffer para no reescribir lo leido previamente */
  } while (n>0); /* mientras no leamos todo lo que esperamos */
  return 0; /* exito */
}


double viajante_par(int z[], int n, double **m, int nperm, int p) {
  int pids[p];
  int infds[p];
  int step = nperm/8;
  double answer = 0;

  for (int i=0; i<p; i++){
    int fds[2];
    pipe(fds);
    init_rand_seed(random());

    if ((pids[i] = fork()) == 0) {
      close(fds[0]);

      int z_hijo[n+1];
      double min = viajante(z_hijo, n, m, step);
      write( fds[1], z_hijo, (n+1)*sizeof(int));
      write( fds[1], &min, sizeof(double));
      exit(0);
    } else {
      close(fds[1]);
      infds[i] = fds[0];
    }
  }

  for (int j=0; j<p; j++){
    double aux_min;
    int aux_z[n+1];
    leer( infds[j], aux_z, (n+1)*sizeof(int));
    leer( infds[j], &aux_min, sizeof(double));
    waitpid( pids[j], NULL, 0);
    close( infds[j]);
    if (answer == 0){
      answer = aux_min;
      for (int k=0; k<=n; k++){
        z[k] = aux_z[k];
      }
    }
    else if (aux_min <= answer){
      answer = aux_min;
      for (int k=0; k<=n; k++){
        z[k] = aux_z[k];
      }
    }
  }
  return answer;
}
