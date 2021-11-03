#include "main.h"

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
