/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstreak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 16:40:00 by lstreak           #+#    #+#             */
/*   Updated: 2018/08/24 16:40:03 by lstreak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

t_slist			*create_list(void)
{
	t_slist		*list;

	if (!(list = (t_slist *)malloc(sizeof(t_slist))))
		return (NULL);
	list->head = NULL;
	return (list);
}

void			clear_list(t_slist *list)
{
	t_node		*tmp;

	tmp = list->head;
	while (tmp)
	{
		tmp = tmp->next;
		ft_strdel(&list->head->nickname);
		free(list->head);
		list->head = tmp;
	}
	if (list)
		free(list);
	list = NULL;
}

void			print_list(t_slist *list)
{
	t_node		*tmp;

	tmp = list->head;
	if (tmp == NULL)
		printf("\033[31mIgnore list is empty.\033[0m\n");
	else
	{
		printf("Ignore list:\n");
		while (tmp)
		{
			printf("- %s\n", tmp->nickname);
			tmp = tmp->next;
		}
	}
}

void			list_push_back(t_slist *list, char *data)
{
	t_node		*node;
	t_node		*tmp;

	if (list)
	{
		if (!(node = (t_node *)malloc(sizeof(t_node))))
			return ;
		node->nickname = strdup(data);
		node->next = NULL;
		if (list->head == NULL)
			list->head = node;
		else
		{
			tmp = list->head;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = node;
		}
	}
}
