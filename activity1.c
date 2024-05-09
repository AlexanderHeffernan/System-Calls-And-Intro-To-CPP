#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>

int main()
{
    int pid, ret_exec, status;
    pid=fork();

    switch(pid){
        case -1:
            printf("Error\n");
            exit(1);

        case 0:
            if (execl("/bin/ps", "ps", "-A", NULL) == -1) {
                perror("Error executing exec");
                exit(1);
            }
        default:
            int status;
            waitpid(pid, &status, 0);

            if (WIFEXITED(status)) {
                printf("Parent Process ID: %d\n", getpid());
                printf("Child Process ID: %d\n", pid);
                printf("Child Termination Status: %d\n", WEXITSTATUS(status));
            }
    }

    return 0;
}