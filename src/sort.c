/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 15:32:20 by franmart          #+#    #+#             */
/*   Updated: 2024/09/22 20:23:20 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	sort_paths_alphabetically(t_list *head)
{
	size_t	lst_size = ft_lstsize(head);
	char	**str_arr = ft_calloc(sizeof(t_list *), lst_size);
	t_list	*tmp = head;
	size_t	i = -1;

	while (++i < lst_size)
	{
		str_arr[i] = tmp->content;
		tmp = tmp->next;
	}
	str_arr = msort_str(str_arr, lst_size);
	i = -1;
	while (++i < lst_size)
	{
		head->content = str_arr[i];
		head = head->next;
	}
	free(str_arr);
}

void	sort_paths_by_date(t_list *head)
{
	size_t	lst_size = ft_lstsize(head);
	t_file_info	**info = ft_calloc(sizeof(t_file_info *), lst_size);
	t_list	*tmp = head;
	size_t	i = -1;

	while (++i < lst_size)
	{
		info[i] = tmp->content;
		tmp = tmp->next;
	}
	info = msort_date(info, lst_size);
	i = -1;
	while (++i < lst_size)
	{
		head->content = info[i];
		head = head->next;
	}
	free(info);
}

char	**msort_str_merge(char **left, size_t size_l, char **right, size_t size_r)
{
	size_t	i = 0;
	size_t	j = 0;
	size_t	k = 0;
	char **temp = ft_calloc(sizeof(char *), size_l + size_r);

	while (i < size_l && j < size_r)
	{
		if (ft_strncmpi(left[i], right[j], ft_strlen(left[i])) <= 0)
			temp[k++] = left[i++];
		else
			temp[k++] = right[j++];
	}
	while (i < size_l)
		temp[k++] = left[i++];
	while (j < size_r)
		temp[k++] = right[j++];
	i = -1;
	while (++i < k)
		left[i] = temp[i];
	free(temp);
	return (left);
}

char	**msort_str(char **str_arr, size_t size)
{
	size_t	mid = size / 2;

	if (size <= 1)
		return (str_arr);
	char **left = msort_str(str_arr, mid);
	char **right = msort_str(str_arr + mid, size - mid);
	return msort_str_merge(left, mid, right, size - mid);
}

t_file_info	**msort_date_merge(t_file_info **left, size_t size_l,
							t_file_info **right, size_t size_r)
{
	size_t	i = 0;
	size_t	j = 0;
	size_t	k = 0;
	t_file_info **temp = ft_calloc(sizeof(t_file_info *), size_l + size_r);

	while (i < size_l && j < size_r)
	{
		if (left[i]->stat_info.st_mtime <= right[j]->stat_info.st_mtime)
			temp[k++] = left[i++];
		else
			temp[k++] = right[j++];
	}
	while (i < size_l)
	temp[k++] = left[i++];
	while (j < size_r)
		temp[k++] = right[j++];
	i = -1;
	while (++i < k)
		left[i] = temp[i];
	free(temp);
	return (left);
}

t_file_info	**msort_date(t_file_info **file_arr, size_t size)
{
	size_t	mid = size / 2;

	if (size <= 1)
		return (file_arr);
	t_file_info **left = msort_date(file_arr, mid);
	t_file_info **right = msort_date(file_arr + mid, size - mid);
	return msort_date_merge(left, mid, right, size - mid);
}
