#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char **argv, char **envp) {
    int nb_cmd = argc - 1;
    int i;

    for (i = 1; i <= nb_cmd; i++) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            return 1;
        } else if (pid == 0) { // Processus fils
            // Exécuter la commande
            execve(argv[i], &argv[i], envp);
            // En cas d'échec de execve
            perror("execve");
            return 1;
        } else { // Processus parent
            // Attendre la fin du processus fils
            int status;
            waitpid(pid, &status, 0);
            if (WIFEXITED(status)) {
                printf("Commande %d terminée avec code de sortie %d\n", i, WEXITSTATUS(status));
            } else {
                printf("Commande %d terminée de manière anormale\n", i);
            }
        }
    }

    return 0;
}
