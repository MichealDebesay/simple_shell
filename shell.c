#include "main.h"

char* hsh_readline()
{
    char* line = NULL;
    size_t bufsize = 0;
    if(getline(&line, &bufsize, stdin) == -1)
    {
        if(feof(stdin)) exit(EXIT_SUCCESS);
        else
        {
            perror("readline");
            exit(EXIT_FAILURE);
        }
    }
    return(line);
}
#define HSH_TOKEN_BUFSIZE 64
#define HSH_TOKEN_DELIM " \t\r\n\a"
char** hsh_parse_arg(char* line)
{
    int bufsize = HSH_TOKEN_BUFSIZE, position = 0;
    char** tokens = malloc(bufsize * sizeof(char *));
    char* token;
    if (tokens == NULL)
    {
	    /* fprintt forbiden */
        fprintf(stderr, "hsh: allocation error \n");
        exit(EXIT_FAILURE);
    }
    token = strtok(line, HSH_TOKEN_DELIM);
    while (token != NULL)
    {
        tokens[position] = token;
        position++;
        if (position >= bufsize){
            bufsize += HSH_TOKEN_BUFSIZE;
	    /* realloc forbiden */
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (tokens == NULL)
            {
                fprintf(stderr, "hsh: allocation error \n");
                exit(EXIT_FAILURE);
            }
        }
        token = strtok(NULL, HSH_TOKEN_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}
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
int hsh_execute(char** arg)
{
    int i __attribute__((unused));
    if (arg[0] == NULL) return (1);
    for (i = 0; i < hsh_num_builtins(); i++)
    {
        if(strcmp(arg[0], builtin_str[i]) == 0) return (*builtin_func[i])(arg);
    }
    return hsh_launch(arg);
}
int main( int __attribute__((unused)) ac, char __attribute__((unused)) **av)
{
    char* line;
    char** arg;
    int status;
    do
    {
        printf("($) ");
        line = hsh_readline();
        arg = hsh_parse_arg(line);
        status = hsh_execute(arg);
        free(line);
        free(arg);
    } while (status);
    return EXIT_SUCCESS;
}
