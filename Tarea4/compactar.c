#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fflush_all(FILE *stream) {
    fflush(stream);
}


void compactar(FILE *stream) {
    char zeros[21] = "                   \n";
    zeros[20] = '\0';
    int i,j;
    i = 0;
    j = 0;
    char L[21];
    while (1) {
        fseek(stream,i*20,SEEK_SET);
        if ( fread(L,20,1,stream) != 1 ) {
            break;
        }
        L[20] = '\0';
        if ( strcmp(L,zeros) ) {
            fseek(stream,j*20,SEEK_SET);
            fwrite(L,20,1,stream);
            i++;
            j++;
            continue;
        }
        i++;

    }
    while (j < i) {
        fseek(stream,20*j,SEEK_SET);
        fwrite(zeros,20,1,stream);
        j++;
    }        
}

int main(int argc, char *argv[]) {
    
    FILE *in = fopen(argv[1],"r+");
    if (in == NULL) {
        perror(argv[1]);
        exit(1);
    }
    compactar(in);
    fclose(in);
    return 0;
}