/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 21:24:23 by franmart          #+#    #+#             */
/*   Updated: 2024/09/19 23:02:58 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_list	*get_file_info(t_list *paths, bool long_output, bool sort_by_date)
{
    t_file_info *info;
	t_list		*head = NULL;

	while (paths)
	{
		info = ft_calloc(sizeof(t_file_info), 1);
		info->path = paths->content;
		if (long_output || sort_by_date) {
			if (stat(paths->content, &info->stat_info)) {}
				; // what do i do with this
			if (S_ISLNK(info->stat_info.st_mode))
			{
				ft_bzero(&info->stat_info, sizeof(t_file_info));
				if (lstat(paths->content, &info->stat_info)) {}
					; // what do i do with this
			}
			ft_lstadd_back(&head, ft_lstnew(info));
		}
		paths = paths->next;
	}
	if (sort_by_date)
		sort_date_list_inplace(head);
	return head;
}