#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>

int main()
{
    int pid, ret_exec, status;
    pid = fork();

    switch(pid){
        case -1:
            printf("Error\n");
            exit(1);

        case 0:
            ret_exec = execl("/bin/ps", "ps", "-A", NULL);
            if (ret_exec == -1) {
                perror("Error executing exec");
                exit(1);
            }
        default:
            pid = wait(&status);

            if (WIFEXITED(status)) {
                printf("Parent Process ID: %d\n", getpid());
                printf("Child Process ID: %d\n", pid);
                printf("Child Termination Status: %d\n", WEXITSTATUS(status));
            }
    }

    return 0;
}