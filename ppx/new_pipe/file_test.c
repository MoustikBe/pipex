#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "bns_ppx.h"

int main(int argc, char **argv)
{
    pid_t pid1, pid2;
    int fd1[2], fd2[2];

    pipe(fd1);
    pipe(fd2);

    pid1 = fork();
    if (pid1 == 0)
    {
        // Premier processus enfant
        close(fd1[0]); // Ferme la lecture de la première extrémité du premier pipe
        dup2(fd1[1], STDOUT_FILENO); // Redirige la sortie standard vers l'écriture de la première extrémité du premier pipe
        close(fd1[1]); // Ferme l'écriture de la première extrémité du premier pipe

        execlp("cat", "cat", "test.txt", NULL); // Exécute la commande 'cat'
        perror("exec cat"); // En cas d'erreur
        exit(EXIT_FAILURE);
    }
    else if (pid1 > 0)
    {
        // Processus parent
        pid2 = fork();
        if (pid2 == 0)
        {
            // Deuxième processus enfant
            close(fd1[1]); // Ferme l'écriture de la première extrémité du premier pipe
            dup2(fd1[0], STDIN_FILENO); // Redirige l'entrée standard depuis la lecture de la première extrémité du premier pipe
            close(fd1[0]); // Ferme la lecture de la première extrémité du premier pipe

            close(fd2[0]); // Ferme la lecture de la première extrémité du second pipe
            dup2(fd2[1], STDOUT_FILENO); // Redirige la sortie standard vers l'écriture de la première extrémité du second pipe
            close(fd2[1]); // Ferme l'écriture de la première extrémité du second pipe

            execlp("grep", "grep", "aw", NULL); // Exécute la commande 'grep'
            perror("exec grep"); // En cas d'erreur
            exit(EXIT_FAILURE);
        }
        else if (pid2 > 0)
        {
            // Processus parent
            close(fd1[0]); // Ferme la lecture de la première extrémité du premier pipe
            close(fd1[1]); // Ferme l'écriture de la première extrémité du premier pipe

            close(fd2[1]); // Ferme l'écriture de la première extrémité du second pipe
            dup2(fd2[0], STDIN_FILENO); // Redirige l'entrée standard depuis la lecture de la première extrémité du second pipe
            close(fd2[0]); // Ferme la lecture de la première extrémité du second pipe

            execlp("wc", "wc", "-l", NULL); // Exécute la commande 'wc -l'
            perror("exec wc"); // En cas d'erreur
            exit(EXIT_FAILURE);
        }
        else
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    return 0;
}
