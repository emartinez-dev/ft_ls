/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 11:31:17 by franmart          #+#    #+#             */
/*   Updated: 2024/09/14 14:00:16 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void error_invalid_arg(char arg);

/*	Very basic arg parser. It looks for a given set of flags, and raises an error if any unknown
	flag is introduced. */
t_list    *parse_args(char *arg, t_config *conf)
{
	if (arg[0] != '-')
		return ft_lstnew(arg);
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
		default:
			error_invalid_arg(arg[i]);
			break;
		}
	}
	return NULL;
}

static void error_invalid_arg(char arg)
{
	ft_putstr_fd("ft_ls: invalid option -- '", STDERR_FILENO);
	ft_putchar_fd(arg, STDERR_FILENO);
	ft_putstr_fd("'\n", STDERR_FILENO);
	exit(1);
}