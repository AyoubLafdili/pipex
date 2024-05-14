#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main(int ac, char *av[])
{
    int fds[2];
    if (pipe(fds) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid_t child = fork();
    if (child == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (child == 0)
    {
        if (dup2(fds[0], 0) == -1)
        {
            perror("dup");
            exit(EXIT_FAILURE);
        }
        close(fds[0]);
        close(fds[1]);
        if (execve("/bin/cat", av, NULL) == -1)
        {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        close(fds[1]);
        wait(NULL);
        close(fds[0]);
        printf("DONE!\n");
    }

    return 0;
}