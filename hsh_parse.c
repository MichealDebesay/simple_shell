#include "main.h"

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
