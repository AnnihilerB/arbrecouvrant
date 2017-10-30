#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "graphes/all.h"

int orderG(){
return 3;}

int sizeG(){
return 2;
}


int graph[3][3] = {
  // 0  1  2  3  4  5  6  7  8  9 10 11
    {0, 1, 1}, //0
    {1, 0, 0}, //1
    {1, 0, 0}
};

int are_adjacent(int u, int v){
      return graph[u][v];
}



void clause2(int filedesc, int n){
    for(int i = 1; i<=n; i++){
        for(int j = 1; j<=n; j++){
            char buf[2];
            if(i!=j){
                snprintf(buf, 2, "%d", i);
                write(filedesc,"-",1);
                write(filedesc,buf,1);
                write(filedesc,"0",1);
                write(filedesc," ",1);
                write(filedesc,"-",1);
                snprintf(buf,2, "%d", j);
                write(filedesc,buf,1);
                write(filedesc,"0",1);
                write(filedesc," ",1);
                write(filedesc,"0",1);
                write(filedesc,"\n",1);

            }
        }
    }
}

void clause4(int filedesc, int n, int k){
  char buf[2];
  for(int i = 1; i<=n; i++){
      for(int ktmp = 1; ktmp<=k; ktmp++){
        snprintf(buf, 2, "%d", i);
        write(filedesc,"-",1);
        write(filedesc,buf,1);
        snprintf(buf, 2, "%d", ktmp);
        write(filedesc,buf,1);
        write(filedesc," ",1);
        for(int j = 1; j<=n; j++){
          if(are_adjacent(i-1,j-1)){
            snprintf(buf, 2, "%d", j);
            write(filedesc,buf,1);
            snprintf(buf, 2, "%d", ktmp-1);
            write(filedesc,buf,1);
            write(filedesc," ",1);
          }
        }
        write(filedesc,"0",1);
        write(filedesc,"\n",1);
        }
      }
    }

void clause3(int filedesc, int n, int k){
	char buf[2];
	for(int i = 1; i<=n; i++){
		snprintf(buf, 2, "%d", i);
        write(filedesc,buf,1);
        snprintf(buf, 2, "%d", k);
        write(filedesc,buf,1);
        write(filedesc," ",1);
	}
	write(filedesc,"0",1);
	write(filedesc,"\n",1);
}


int main(){
    int filedesc = open("form.cnf", O_WRONLY | O_CREAT,0666);

    int n = 3;
    int k = 2;
    clause2(filedesc, n);
    clause3(filedesc, n, k);
    clause4(filedesc, n, k);


}
