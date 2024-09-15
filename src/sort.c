/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franmart <franmart@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 15:32:20 by franmart          #+#    #+#             */
/*   Updated: 2024/09/15 16:56:52 by franmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	sort_list_inplace(t_list *head)
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
	str_arr = merge_sort(str_arr, lst_size);
	i = -1;
	while (++i < lst_size)
	{
		head->content = str_arr[i];
		head = head->next;
	}
	free(str_arr);
}

char	**merge(char **left, size_t size_l, char **right, size_t size_r)
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

char	**merge_sort(char **str_arr, size_t size)
{
	size_t	mid = size / 2;

	if (size <= 1)
		return (str_arr);
	char **left = merge_sort(str_arr, mid);
	char **right = merge_sort(str_arr + mid, size - mid);
	return merge(left, mid, right, size - mid);
}
