#include "main.h"

int hsh_launch( char** arg)
{
    pid_t pid, wpid __attribute__((unused));
    int status;
    pid = fork();
    if (pid == 0){
        if(execvp(arg[0], arg) == -1) perror("hsh");
        exit(EXIT_FAILURE);
    }
    else if (pid < 0) perror("hsh");
    else
    {
        do
        {
            wpid = waitpid(pid, &status, WUNTRACED);
	    /* WIFSIGNALED i dont know but check again */
        }while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return 1;
}
