/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_who.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstreak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 15:38:36 by lstreak           #+#    #+#             */
/*   Updated: 2018/08/24 15:38:38 by lstreak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void			who_in_chan(t_env *e, int cs, char **input_arr)
{
	int			i;

	i = 0;
	if (ft_arrlen(input_arr) > 1)
	{
		strcpy(e->fds[cs].buf_write, "\033[31m==\033[0m Usage: /who\n");
		return ;
	}
	while (i <= e->max)
	{
		if (e->fds[i].type == FD_CLIENT && \
		!strcmp(e->fds[i].user.channel, e->fds[cs].user.channel))
		{
			strcat(e->fds[cs].buf_write, "\033[31m> \033[0m");
			strcat(e->fds[cs].buf_write, e->fds[i].user.nickname);
			strcat(e->fds[cs].buf_write, "\n");
		}
		i++;
	}
}
