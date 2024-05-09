#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

/**
 * Prints a specified error message to the console and exits the program.
 *
 * @param message - Message to print to the console.
 */
void error (char[] message)
{
    printf(message);
    exit(1);
}

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
            error("Error\n");

        case 0:
            // Child process
            // Execute ps -A command
            ret_exec = execl("/bin/ps", "ps", "-A", NULL);
            if (ret_exec == -1) // Error handling if execl fails
                error("Error executing exec\n");

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