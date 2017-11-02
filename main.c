#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "graphes/all.h"

#define SIZE_BUFFER 1000

int orderG(){
    return 10;}
    
    int sizeG(){
    return 10;}
    
  int are_adjacent(int u, int v){
     if(0<= u && 0<=v && u<10 && v<10){
      return (((10+u-v)%10==1)||((10+v-u)%10==1));
     }	
     else return 0;
    }


int graph[3][3] = {
  // 0  1  2
    {0, 1, 1}, //0
    {1, 0, 1}, //1
    {1, 1, 0}  //2
};

/*int are_adjacent(int u, int v){
      return graph[u][v];
}
*/
//Le sommet ne peut avoir qu'une seule hauteur à la fois.
void clause1(FILE *filedesc, int n, int k){
    for (int i=1; i<=n; i++){
        for (int h_suppose = 0; h_suppose<=k; h_suppose++){
            for (int h_impossible = 0; h_impossible <= k; h_impossible++){
                char buf[SIZE_BUFFER];
                if (h_suppose != h_impossible){
                    //Sommet de référence
                    snprintf(buf, SIZE_BUFFER - 1, "%d", i);
                    fwrite("-",sizeof(char),sizeof(char),filedesc);
                    fprintf(filedesc, "%s", buf);
                    //Hauteur supposée vraie
                    snprintf(buf, SIZE_BUFFER - 1, "%d", h_suppose);
                    fprintf(filedesc, "%s", buf);
                    fwrite(" ",sizeof(char),sizeof(char),filedesc);
                    //Sommet de référence
                    snprintf(buf, SIZE_BUFFER - 1, "%d", i);
                    fwrite("-",sizeof(char),sizeof(char),filedesc);
                    fprintf(filedesc, "%s", buf);
                    //Hauteur impossible pour ce sommet
                    snprintf(buf, SIZE_BUFFER - 1, "%d", h_impossible);
                    fprintf(filedesc, "%s", buf);
                    fwrite(" ",sizeof(char),sizeof(char),filedesc);
                    //Fin de ligne
                    fwrite("0",sizeof(char),sizeof(char),filedesc);
                    fwrite("\n",sizeof(char),sizeof(char),filedesc);
                }
            }
        }

    }
    //Chaque sommet a obligatoirement une hauteur
    for (int i=1; i<=n; i++){
        for (int h = 0; h <= k; h++){
            char buf[SIZE_BUFFER];
            snprintf(buf, SIZE_BUFFER - 1, "%d", i);
            fprintf(filedesc, "%s", buf);
            snprintf(buf, SIZE_BUFFER - 1, "%d", h);
            fprintf(filedesc, "%s", buf);
            fwrite(" ",sizeof(char),sizeof(char),filedesc);
        }
        fwrite("0",sizeof(char),sizeof(char),filedesc);
        fwrite("\n",sizeof(char),sizeof(char),filedesc);
    }
}


/* Un unique sommet de hauteur 0 */
void clause2(FILE *filedesc, int n){
    // Parcours des différents sommets.
    for(int i = 1; i<=n; i++){ 
        for(int j = 1; j<=n; j++){
            char buf[1000];
            //Permet de ne pas comparer un sommet a lui même
            if(i!=j){
                //Sommet de référence
                snprintf(buf, SIZE_BUFFER - 1, "%d", i);
                fwrite("-",sizeof(char),sizeof(char),filedesc);
                fprintf(filedesc, "%s", buf);
                //Hauteur 0
                fwrite("0",sizeof(char),sizeof(char),filedesc);
                fwrite(" ",sizeof(char),sizeof(char),filedesc);
                //Sommet de référence
                fwrite("-",sizeof(char),sizeof(char),filedesc);
                snprintf(buf,SIZE_BUFFER - 1, "%d", j);
                fprintf(filedesc, "%s", buf);
                //Hauteur 0
                fwrite("0",sizeof(char),sizeof(char),filedesc);
                fwrite(" ",sizeof(char),sizeof(char),filedesc);
                //Fin de ligne
                fwrite("0",sizeof(char),sizeof(char),filedesc);
                fwrite("\n",sizeof(char),sizeof(char),filedesc);
            }
        }
    }
    //On s'assure qu'on a au moins un sommet 0;
    for (int i = 1; i <= n; i++){
        char buf[SIZE_BUFFER];
        snprintf(buf, SIZE_BUFFER - 1, "%d", i);
        fprintf(filedesc, "%s", buf);
        fwrite("0",sizeof(char),sizeof(char),filedesc);
        fwrite(" ",sizeof(char),sizeof(char),filedesc);
    }
    fwrite("0",sizeof(char),sizeof(char),filedesc);
    fwrite("\n",sizeof(char),sizeof(char),filedesc);
}

/* Si un sommet est de hauteur >0, alors il dispose d'un parent si l'arrête existe dans le graphe. */
void clause4(FILE *filedesc, int n, int k){
  char buf[SIZE_BUFFER];
  //Sommet de référence
  for(int i = 1; i<=n; i++){
      //Itération sur K
      for(int ktmp = 1; ktmp<=k; ktmp++){
        //Sommet de référence
        snprintf(buf, SIZE_BUFFER - 1, "%d", i);
        fwrite("-",sizeof(char),sizeof(char),filedesc);
        fprintf(filedesc, "%s", buf);
        //Hauteur présumé du sommet
        snprintf(buf, SIZE_BUFFER - 1, "%d", ktmp);
        fprintf(filedesc, "%s", buf);
        fwrite(" ",sizeof(char),sizeof(char),filedesc);
        //Parcours des voisins
        for(int j = 1; j<=n; j++){
        // -1 car on commence la numérotation des sommets à 1, glucose ne gérant pas 0 comme variable.
          if(are_adjacent(i-1,j-1)){
            //Sommet voisin
            snprintf(buf, SIZE_BUFFER - 1, "%d", j);
            fprintf(filedesc, "%s", buf);
            //Hauteur - 1 (le sommet est plus haut dans le graphe)
            snprintf(buf, SIZE_BUFFER - 1, "%d", ktmp-1);
            fprintf(filedesc, "%s", buf);
            fwrite(" ",sizeof(char),sizeof(char),filedesc);
          }
        }
        //Fin de ligne.
        fwrite("0",sizeof(char),sizeof(char),filedesc);
        fwrite("\n",sizeof(char),sizeof(char),filedesc);
        }
      }
    }

/* Il exite au moins un sommet de hauteur k */
void clause3(FILE *filedesc, int n, int k){
    char buf[SIZE_BUFFER];
    //Parcours de chaque sommet
	for(int i = 1; i<=n; i++){
        //Sommet de référence
		snprintf(buf, SIZE_BUFFER - 1, "%d", i);
        fprintf(filedesc, "%s", buf);
        //Hauteur k
        snprintf(buf, SIZE_BUFFER - 1, "%d", k);
        fprintf(filedesc, "%s", buf);
        fwrite(" ",sizeof(char),sizeof(char),filedesc);
    }
    //Fin de ligne
	fwrite("0",sizeof(char),sizeof(char),filedesc);
    fwrite("\n",sizeof(char),sizeof(char),filedesc);
}


int main(int argc, char *argv[]){
    //////// ARBRE ATTENDU DE TAILLE 3 ////////////
    FILE *filedesc = fopen("form.cnf", "wr");

    int nb_sommets = orderG();
    //Hauteur désirée de l'arbre couvrant
    int k = atoi(argv[1]);


    clause1(filedesc, nb_sommets, k);
    clause2(filedesc, nb_sommets);
    clause3(filedesc, nb_sommets, k);
    clause4(filedesc, nb_sommets, k);

    fclose(filedesc);

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
