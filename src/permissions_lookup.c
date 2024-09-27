/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permissions_lookup.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 19:43:39 by franmart          #+#    #+#             */
/*   Updated: 2024/09/27 20:08:21 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char    *get_group_name(gid_t group_id, t_config *conf)
{
	t_group_info	*info;
	t_list			*head;
	struct group	*grp;

	head = conf->groups;
	while (head)
	{
		info = head->content;
		if (info->gid == group_id)
			return (info->name);
		head = head->next;
	}
	info = ft_calloc(1, sizeof(t_group_info));
	info->gid = group_id;
	grp = getgrgid(group_id);
	if (grp->gr_name)
		info->name = ft_strdup(grp->gr_name);
	else
		info->name = ft_itoa(group_id);
	ft_lstadd_front(&conf->groups, ft_lstnew(info));
	return (info->name);
}

char    *get_user_name(uid_t user_id, t_config *conf)
{
	t_user_info		*info;
	t_list			*head;
	struct passwd	*pw;

	head = conf->users;
	while (head)
	{
		info = head->content;
		if (info->uid == user_id)
			return (info->name);
		head = head->next;
	}
	info = ft_calloc(1, sizeof(t_user_info));
	info->uid = user_id;
	pw = getpwuid(user_id);
	if (pw->pw_name)
		info->name = ft_strdup(pw->pw_name);
	else
		info->name = ft_itoa(user_id);
	ft_lstadd_front(&conf->users, ft_lstnew(info));
	return (info->name);
}

void	free_user_info(void *content)
{
	t_user_info *info;

	info = content;
	if (info->name)
		free(info->name);
	free(info);
}

void	free_group_info(void *content)
{
	t_group_info *info;

	info = content;
	if (info->name)
		free(info->name);
	free(info);
}