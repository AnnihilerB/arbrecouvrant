#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

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
                write(filedesc,"\n",1);
            }
        }
    }
}


int main(){
    int filedesc = open("form.cnf", O_WRONLY | O_CREAT,0666);

    int n = 3;
    clause2(filedesc, n);
}


