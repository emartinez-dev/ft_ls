/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 20:40:17 by franmart          #+#    #+#             */
/*   Updated: 2024/09/13 21:07:04 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"

/* I am an outer core student, could I pls just use stdbool? */
typedef enum { false, true } bool;
# define true  1
# define false 0

typedef struct s_args
{
    bool l_long;
    bool R_recursive;
    bool a_hidden;
    bool r_reverse;
    bool t_date_sort;
}   t_config;

/* parser.c */
void    parse_args(char *arg, t_config *conf);
void    print_config(t_config *conf);

#endif