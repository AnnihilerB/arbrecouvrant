#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "graphes/all.h"

int orderG(){
return 4;}

int sizeG(){
return 2;
}


int graph[4][4] = {
  // 0  1  2
    {0, 1, 1, 1}, //0
    {1, 0, 1, 0}, //1
    {1, 1, 0, 0},  //2
    {1, 0, 0, 0}
};

int are_adjacent(int u, int v){
      return graph[u][v];
}

//Le sommet ne peut avoir qu'une seule hauteur à la fois.
void clause1(int filedesc, int n, int k){
    for (int i=1; i<=n; i++){
        for (int h_suppose = 0; h_suppose<=k; h_suppose++){
            for (int h_impossible = 0; h_impossible <= k; h_impossible++){
                char buf[2];
                if (h_suppose != h_impossible){
                    //Sommet de référence
                    snprintf(buf, 2, "%d", i);
                    write(filedesc,"-",1);
                    write(filedesc,buf,1);
                    //Hauteur supposée vraie
                    snprintf(buf, 2, "%d", h_suppose);
                    write(filedesc,buf,1);
                    write(filedesc," ",1);
                    //Sommet de référence
                    snprintf(buf, 2, "%d", i);
                    write(filedesc,"-",1);
                    write(filedesc,buf,1);
                    //Hauteur impossible pour ce sommet
                    snprintf(buf, 2, "%d", h_impossible);
                    write(filedesc,buf,1);
                    write(filedesc," ",1);
                    //Fin de ligne
                    write(filedesc,"0",1);
                    write(filedesc,"\n",1);
                }
            }
        }

    }
}


/* Un unique sommet de hauteur 0 */
void clause2(int filedesc, int n){
    // Parcours des différents sommets.
    for(int i = 1; i<=n; i++){ 
        for(int j = 1; j<=n; j++){
            char buf[2];
            //Permet de ne pas comparer un sommet a lui même
            if(i!=j){
                //Sommet de référence
                snprintf(buf, 2, "%d", i);
                write(filedesc,"-",1);
                write(filedesc,buf,1);
                //Hauteur 0
                write(filedesc,"0",1);
                write(filedesc," ",1);
                //Sommet de référence
                write(filedesc,"-",1);
                snprintf(buf,2, "%d", j);
                write(filedesc,buf,1);
                //Hauteur 0
                write(filedesc,"0",1);
                write(filedesc," ",1);
                //Fin de ligne
                write(filedesc,"0",1);
                write(filedesc,"\n",1);

            }
        }
    }
}

/* Si un sommet est de hauteur >0, alors il dispose d'un parent si l'arrête existe dans le graphe. */
void clause4(int filedesc, int n, int k){
  char buf[2];
  //Sommet de référence
  for(int i = 1; i<=n; i++){
      //Itération sur K
      for(int ktmp = 1; ktmp<=k; ktmp++){
        //Sommet de référence
        snprintf(buf, 2, "%d", i);
        write(filedesc,"-",1);
        write(filedesc,buf,1);
        //Hauteur présumé du sommet
        snprintf(buf, 2, "%d", ktmp);
        write(filedesc,buf,1);
        write(filedesc," ",1);
        //Parcours des voisins
        for(int j = 1; j<=n; j++){
        // -1 car on commence la numérotation des sommets à 1, glucose ne gérant pas 0 comme variable.
          if(are_adjacent(i-1,j-1)){
            //Sommet voisin
            snprintf(buf, 2, "%d", j);
            write(filedesc,buf,1);
            //Hauteur - 1 (le sommet est plus haut dans le graphe)
            snprintf(buf, 2, "%d", ktmp-1);
            write(filedesc,buf,1);
            write(filedesc," ",1);
          }
        }
        //Fin de ligne.
        write(filedesc,"0",1);
        write(filedesc,"\n",1);
        }
      }
    }

/* Il exite au moins un sommet de hauteur k */
void clause3(int filedesc, int n, int k){
    char buf[2];
    //Parcours de chaque sommet
	for(int i = 1; i<=n; i++){
        //Sommet de référence
		snprintf(buf, 2, "%d", i);
        write(filedesc,buf,1);
        //Hauteur k
        snprintf(buf, 2, "%d", k);
        write(filedesc,buf,1);
        write(filedesc," ",1);
    }
    //Fin de ligne
	write(filedesc,"0",1);
	write(filedesc,"\n",1);
}


int main(int argc, char *argv[]){
    //////// ARBRE ATTENDU DE TAILLE 3 ////////////
    int filedesc = open("form.cnf", O_WRONLY | O_CREAT | O_TRUNC,0666);

    int nb_sommets = orderG();
    //Hauteur désirée de l'arbre couvrant
    int k = atoi(argv[1]);

    clause1(filedesc, nb_sommets, k);
    clause2(filedesc, nb_sommets);
    clause3(filedesc, nb_sommets, k);
    clause4(filedesc, nb_sommets, k);

    close(filedesc);

    pid_t pid_fils;
    int status;
    pid_fils = fork();

    if (pid_fils != 0){
        //Pere
        wait(&status);
        printf("----- Arbre couvrant -----\n");
        execlp("./arbrecouvrant", "./arbrecouvrant", NULL);
    }
    else{
        //Fils
        execlp("./glucose-syrup-4.1/simp/glucose", "./glucose-syrup-4.1/simp/glucose", "form.cnf", "sol.out", NULL);
        sleep(4);
        printf("FILS FINI\n");

    }

    return 0;


}
