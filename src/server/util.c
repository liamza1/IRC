/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstreak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 10:46:15 by lstreak           #+#    #+#             */
/*   Updated: 2018/08/24 10:46:17 by lstreak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void				get_time(t_env *e)
{
	time_t			timer;
	struct tm		*tm_info;

	time(&timer);
	tm_info = localtime(&timer);
	strftime(e->strtime, DATE_SIZE, "%Y-%m-%d %H:%M:%S", tm_info);
}

int					duplicate_user(t_env *e, int cs, char *name)
{
	int				i;

	i = 0;
	while (i <= e->max)
	{
		if (!strcmp(e->fds[i].user.nickname, name) && i != cs)
			return (1);
		i++;
	}
	return (0);
}

int					get_fd_from_usr(t_env *e, char *name)
{
	int				i;

	i = 0;
	while (i <= e->max)
	{
		if (!strcmp(e->fds[i].user.nickname, name))
			return (i);
		i++;
	}
	return (-1);
}
