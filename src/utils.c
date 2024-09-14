/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 11:31:30 by franmart          #+#    #+#             */
/*   Updated: 2024/09/14 11:39:24 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

void    print_paths(t_list *paths)
{
	while (paths)
	{
		ft_printf("\t%s\n", paths->content);
		paths = paths->next;
	}
}