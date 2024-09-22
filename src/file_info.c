/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 21:24:23 by franmart          #+#    #+#             */
/*   Updated: 2024/09/22 20:22:37 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_list	*get_file_info(t_list *paths, t_config *conf)
{
    t_file_info *info;
	t_list		*head = NULL;

	if (!conf->t_date_sort)
		sort_paths_alphabetically(paths);
	while (paths)
	{
		info = ft_calloc(sizeof(t_file_info), 1);
		info->path = paths->content;
		if (!lstat(paths->content, &info->stat_info))
			ft_lstadd_front(&head, ft_lstnew(info));
		paths = paths->next;
	}
	if (conf->t_date_sort)
		sort_paths_by_date(head);
	if (!conf->r_reverse)
		head = ft_lstreverse(head);
	return head;
}

char	*get_file_name(char *str)
{
	char	*name;

	name = ft_strrchr(str, '/');
	if (name)
		return (name + 1);
	return (str);
}

char	*join_paths(char *p1, char *p2)
{
	char *tmp = ft_strjoin(p1, "/");
	char *path = ft_strjoin(tmp, p2);
	free(tmp);
	return (path);
}