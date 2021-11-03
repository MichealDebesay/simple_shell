#include "main.h"

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
