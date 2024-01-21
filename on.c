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
  if (argc != 4) {
        exit(EXIT_FAILURE);
  }

  pid_t pid = fork();

  if(pid== -1){
    perror("fork");
    exit(EXIT_FAILURE);
  } else if(pid==0){
      if (execlp(argv[1], argv[1], NULL) == -1) {
            perror("execlp");
            exit(EXIT_FAILURE);
      }

  } else {
    int status;
    if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
    }
    if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            if (execlp(argv[3], argv[3], NULL) == -1) {
                perror("execlp");
                exit(EXIT_FAILURE);
            }
    }

  }

  return EXIT_SUCCESS;
}
