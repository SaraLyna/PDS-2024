#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "makeargv.h"


int execute_command(char *command) {
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        char **args;
        int argCount = makeargv(command, " ", &args);

        if (argCount < 0) {
            perror("makeargv");
            exit(EXIT_FAILURE);
        }

        execvp(args[0], args);
        perror("execvp");
        exit(EXIT_FAILURE);
    } else {
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
        return WEXITSTATUS(status);
    }
}

int main(int argc, char *argv[]) {
    int conjunction = 1;
    int shortcut_exit = 0;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (argv[i][1] == 'a') {
                conjunction = 1;
            } else if (argv[i][1] == 'o') {
                conjunction = 0;
            } else if (argv[i][1] == 'c') {
                shortcut_exit = 1;
            }
        }
    }

    int command_start_index = 1;
    if (shortcut_exit) {
        command_start_index++;
    }

    int result = conjunction ? 0 : 1;

    for (int i = command_start_index; i < argc; i++) {
        result = execute_command(argv[i]);
        if (shortcut_exit && ((conjunction && result != 0) || (!conjunction && result == 0))) {
            break;
        }
    }

    return result;
}
