/* Exercice 1

   Il s'agit d'implanter une commande =on= qui exécute une
   seconde commande =cmd= si et seulement si l'exécution
   d'une première commande =pred= se termine sur un succès :

   on pred do cmd
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
  pid_t pid;

  switch(pid=fork()){
    case -1 : exit(EXIT_FAILURE);
    case 0 : {execvp(NULL,NULL);
              return 0;
    }
    default : return 1;
  }
  wait(NULL);
  execvp(NULL,NULL);

    return EXIT_SUCCESS;
}
