#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(void){

    FILE *fichier = fopen("sol.out", "r");

    int buffer;

    while(fscanf(fichier, "%d", &buffer) == 1){
        if (buffer > 0){
            printf("%d ", buffer);
        }
    }
    printf("\n");
    fclose(fichier);
}