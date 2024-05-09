#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

/**
 * Main entry point of the progarm
 */
int main()
{
    int pid, ret_exec, status;

    // Create a child process
    pid = fork();

    switch(pid){
        case -1:
            // Error handling if fork fails
            printf("Error\n");
            exit(1);
            

        case 0:
            // Child process
            // Execute ps -A command
            ret_exec = execl("/bin/ps", "ps", "-A", NULL);
            if (ret_exec == -1) { // Error handling if execl fails
                printf("Error executing exec\n");
                exit(1);
            }

        default:
            // Parent process
            // Wait for the child process to terminate
            pid = wait(&status);

            // Check if child process terminated normally
            if (WIFEXITED(status)) {
                // Print process IDs and termination status
                printf("Parent Process ID: %d\n", getpid());
                printf("Child Process ID: %d\n", pid);
                printf("Child Termination Status: %d\n", WEXITSTATUS(status));
            }
    }

    return 0;
}