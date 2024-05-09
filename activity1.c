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
            /* code for case -1 */

        case 0:
            /* code for case 0 */
        default:
            /* code for case default */
    }
}