#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

char* hsh_readline();
#define HSH_TOKEN_BUFSIZE 64
#define HSH_TOKEN_DELIM " \t\r\n\a"
char** hsh_parse_arg(char* line);
int hsh_launch( char** arg);
int hsh_execute(char** arg);


/*
  Function Declarations for builtin shell commands:
 */
int hsh_exit();

/*
  List of builtin commands, followed by their corresponding functions.
 */
char *builtin_str[] = {
  "exit"
};

int (*builtin_func[]) (char **) = {
  &hsh_exit
};

int lsh_num_builtins() {
  return sizeof(builtin_str) / sizeof(char *);
}

/*
  Builtin function implementations.
*/
int hsh_exit()
{
  return 0;
}


#endif
