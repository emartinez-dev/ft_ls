#include "ft_ls.h"

void    parse_args(char *arg, t_config *conf)
{
    if (arg[0] != '-')
        return ;
    int i = 0;
    while (arg[++i])
    {
        switch (arg[i])
        {
        case 'l':
            conf->l_long = true;
            break;
        case 'R':
            conf->R_recursive = true;
            break;
        case 'a':
            conf->a_hidden = true;
            break;
        case 'r':
            conf->r_reverse = true;
            break;
        case 't':
            conf->t_date_sort = true;
            break;
        }
    }
}

void    print_config(t_config *conf)
{
    char *str = ft_strdup("------\n");
    if (conf->l_long)
        str[1] = 'l';
    if (conf->R_recursive)
        str[2] = 'R';
    if (conf->a_hidden)
        str[3] = 'a';
    if (conf->r_reverse)
        str[4] = 'r';
    if (conf->t_date_sort)
        str[5] = 't';
    ft_printf(str);
    free(str);
}