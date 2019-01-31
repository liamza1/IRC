/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_leave.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstreak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 15:37:49 by lstreak           #+#    #+#             */
/*   Updated: 2018/08/24 15:37:51 by lstreak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static int		chan_error(t_env *e, int cs, char **input_arr)
{
	char	*trim;

	trim = ft_strtrim(input_arr[1]);
	if (!strcmp(trim, CHAN_GEN))
	{
		strcpy(e->fds[cs].buf_write, "\033[31m==\033[0m You can't leave ");
		strcat(e->fds[cs].buf_write, CHAN_GEN);
		strcat(e->fds[cs].buf_write, "\n");
	}
	else if (strcmp(trim, e->fds[cs].user.channel))
	{
		strcpy(e->fds[cs].buf_write, "\033[31m==\033[0m Your channel is ");
		strcat(e->fds[cs].buf_write, e->fds[cs].user.channel);
		strcat(e->fds[cs].buf_write, "\n");
	}
	else
	{
		ft_strdel(&trim);
		return (1);
	}
	ft_strdel(&trim);
	return (-1);
}

static int		args_error(t_env *e, int cs, char **input_arr)
{
	if (strlen(input_arr[1]) - 1 > CHAN_SIZE)
	{
		strcpy(e->fds[cs].buf_write, \
			"\033[31m==\033[0m Channel name too long\n");
		return (-1);
	}
	else if (input_arr[1][0] != '#')
	{
		strcpy(e->fds[cs].buf_write, \
			"\033[31m==\033[0m Channel name must begin with #\n");
		return (-1);
	}
	else if (strlen(input_arr[1]) < 4)
	{
		strcpy(e->fds[cs].buf_write, \
			"\033[31m==\033[0m Channel name too short\n");
		return (-1);
	}
	else if ((chan_error(e, cs, input_arr)) < 0)
		return (-1);
	return (1);
}

static int		check_error(t_env *e, int cs, char **input_arr)
{
	if (ft_arrlen(input_arr) > 2)
	{
		strcpy(e->fds[cs].buf_write, \
			"\033[31m==\033[0m Usage: /leave [#channel]\n");
		return (-1);
	}
	else if (ft_arrlen(input_arr) == 1 && \
	!strcmp(e->fds[cs].user.channel, CHAN_GEN))
	{
		strcpy(e->fds[cs].buf_write, "\033[31m==\033[0m You can't leave ");
		strcat(e->fds[cs].buf_write, CHAN_GEN);
		strcat(e->fds[cs].buf_write, "\n");
		return (-1);
	}
	else if (ft_arrlen(input_arr) == 2)
	{
		if ((args_error(e, cs, input_arr)) < 0)
			return (-1);
	}
	return (1);
}

void			leave_chan(t_env *e, int cs, char **input_arr)
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
	printf("\033[31m[%s]\033[0m %s left %s\n", \
		e->strtime, e->fds[cs].user.nickname, e->fds[cs].user.channel);
	memset(e->fds[cs].user.channel, 0, CHAN_SIZE + 1);
	strncpy(e->fds[cs].user.channel, CHAN_GEN, strlen(CHAN_GEN));
	memset(concat, 0, CHAN_SIZE + NICK_SIZE + 11);
	strcpy(concat, e->fds[cs].user.nickname);
	strcat(concat, " joined ");
	strcat(concat, CHAN_GEN);
	strcat(concat, "\n");
	send_to_chan(e, concat, MSG_INFO, cs);
	printf("\033[31m[%s]\033[0m %s joined %s\n", \
		e->strtime, e->fds[cs].user.nickname, e->fds[cs].user.channel);
}
