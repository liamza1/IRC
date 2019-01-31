/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstreak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 15:37:38 by lstreak           #+#    #+#             */
/*   Updated: 2018/08/24 15:37:40 by lstreak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static int		is_valid_chan(char *chan)
{
	int			i;

	i = 0;
	chan++;
	while (chan[i] && chan[i] != '\n')
	{
		if (!ft_isalnum(chan[i]))
			return (0);
		i++;
	}
	return (1);
}

static int		check_error(t_env *e, int cs, char **input_arr)
{
	if (ft_arrlen(input_arr) != 2)
	{
		strcpy(e->fds[cs].buf_write, \
			"\033[31m==\033[0m Usage: /join <#channel>\n");
	}
	else if (strlen(input_arr[1]) - 1 > CHAN_SIZE)
	{
		strcpy(e->fds[cs].buf_write, \
		"\033[31m==\033[0m Channel name too long\n");
	}
	else if (input_arr[1][0] != '#' || !is_valid_chan(input_arr[1]))
	{
		strcpy(e->fds[cs].buf_write, \
			"\033[31m==\033[0m Invalid character(s)\n");
	}
	else if (strlen(input_arr[1]) < 4)
	{
		strcpy(e->fds[cs].buf_write, \
			"\033[31m==\033[0m Channel name too short\n");
	}
	else
		return (1);
	return (-1);
}

void			join_chan(t_env *e, int cs, char **input_arr)
{
	char		concat[CHAN_SIZE + NICK_SIZE + 11];

	if ((check_error(e, cs, input_arr)) < 0)
		return ;
	memset(concat, 0, CHAN_SIZE + NICK_SIZE + 11);
	get_time(e);
	strcpy(concat, e->fds[cs].user.nickname);
	strcat(concat, " left ");
	strcat(concat, e->fds[cs].user.channel);
	strcat(concat, "\n");
	send_to_chan(e, concat, MSG_INFO, cs);
	printf("\033[31m[%s]\033[0m %s leaved %s\n", \
		e->strtime, e->fds[cs].user.nickname, e->fds[cs].user.channel);
	memset(e->fds[cs].user.channel, 0, CHAN_SIZE + 1);
	strncpy(e->fds[cs].user.channel, input_arr[1], strlen(input_arr[1]) - 1);
	memset(concat, 0, CHAN_SIZE + NICK_SIZE + 11);
	strcpy(concat, e->fds[cs].user.nickname);
	strcat(concat, " joined ");
	strcat(concat, e->fds[cs].user.channel);
	strcat(concat, "\n");
	send_to_chan(e, concat, MSG_INFO, cs);
	printf("\033[31m[%s]\033[0m %s joined %s\n", \
		e->strtime, e->fds[cs].user.nickname, e->fds[cs].user.channel);
}
