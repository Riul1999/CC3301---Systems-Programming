#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void reducir(char *s){
    char *ptr=s;
    char *ptr2=ptr;
    int espacio=0;
    while (*ptr) {
        if (espacio) {
            if (*ptr==' '){
                ptr++;
            }else{
                *ptr2=*ptr;
                espacio=0;
                ptr++;
                ptr2++;
            }
        } else{
            if (*ptr==' ') {
                *ptr2=*ptr;
                espacio=1;
                ptr++;
                ptr2++;
            } else {
                *ptr2=*ptr;
                ptr++;
                ptr2++;
            }
        }
    }
    *ptr2=*ptr;
}

char *reduccion(char *s){
    int n=strlen(s);
    int espacio=0;
    for(char *ptr=s ;*ptr ;ptr++) {
        if (*ptr==' ' && espacio) {
            n--;
        } else if (*ptr==' ') {
            espacio=1;
        } else {
            espacio=0;
        }
    }
    n++;
    char*a=malloc(n*sizeof(char));
    char* ptr2=a;
    int space=0;
    char *ptr1=s;
    for(;*ptr1;ptr1++) {
        if (space) {
            if (*ptr1==' ') {
            } else {
                space=0;
                *ptr2=*ptr1;
                ptr2++;
            }
        } else {
            if (*ptr1==' ') {
                space=1;
                *ptr2=*ptr1;
                ptr2++;
            } else {
                *ptr2=*ptr1;
                ptr2++;
            }
        }
    }
    *ptr2=*ptr1;
    return a;
}