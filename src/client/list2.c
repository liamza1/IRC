/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstreak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 16:40:07 by lstreak           #+#    #+#             */
/*   Updated: 2018/08/24 16:40:09 by lstreak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void		free_node(t_node *node)
{
	ft_strdel(&node->nickname);
	free(node);
	node = NULL;
}

void			del_node(t_slist *list, char *data)
{
	t_node		*tmp;

	tmp = list->head;
	if (tmp == NULL)
		return ;
	if (tmp && tmp->next == NULL)
	{
		list->head = NULL;
		free_node(tmp);
	}
	else if (!strcmp(tmp->nickname, data))
	{
		list->head = tmp->next;
		tmp->next = tmp->next->next;
		free_node(tmp);
	}
	else
	{
		while (tmp->next && strcmp(tmp->next->nickname, data))
			tmp = tmp->next;
		free_node(tmp->next);
		tmp->next = tmp->next->next;
	}
}

int				is_ignored(t_slist *list, char *data)
{
	t_node		*tmp;

	tmp = list->head;
	while (tmp)
	{
		if (!strcmp(tmp->nickname, data))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
