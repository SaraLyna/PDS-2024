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

  pid=fork();

  if(pid== -1){
    exit(EXIT_FAILURE);
  } else if(pid==0){
    char *args[2] = {argv[1]};
    execvp(argv[1],args);

  }
  wait(NULL);
  char *args[2] = {argv[3]};
  execvp(argv[3],args);

    return EXIT_SUCCESS;
}
