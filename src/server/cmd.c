/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstreak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 10:45:56 by lstreak           #+#    #+#             */
/*   Updated: 2018/08/24 10:45:58 by lstreak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static void		print_help(t_env *e, int cs, char **input_arr)
{
	if (ft_arrlen(input_arr) != 1)
	{
		strcpy(e->fds[cs].buf_write, "\033[31m==\033[0m Unknow command\n");
		return ;
	}
	strcpy(e->fds[cs].buf_write,
		"===================== - List of commands - ====================\n");
	strcat(e->fds[cs].buf_write,
		"\033[31m> \033[0m    /nick <nickname>\n");
	strcat(e->fds[cs].buf_write,
		"\033[31m> \033[0m    /join <#channel>, /leave [#channel]\n");
	strcat(e->fds[cs].buf_write,
		"\033[31m> \033[0m    /who\n");
	strcat(e->fds[cs].buf_write,
		"\033[31m> \033[0m    /msg <nick> <message>\n");
	strcat(e->fds[cs].buf_write,
		"\033[31m> \033[0m    /ignore\n");
	strcat(e->fds[cs].buf_write,
		"\033[31m> \033[0m    /ignore <nick>\n");
	strcat(e->fds[cs].buf_write,
		"\033[31m> \033[0m    /unignore <nick>\n");
	strcat(e->fds[cs].buf_write,
		"\033[31m> \033[0m    /connect <machine> [port]\n");
	strcat(e->fds[cs].buf_write,
		"===============================================================\n");
}

void			send_to_chan(t_env *e, char *message, int msg_type, int cs)
{
	int			i;

	i = 0;
	while (i <= e->max)
	{
		if (e->fds[i].type == FD_CLIENT && \
		!strcmp(e->fds[i].user.channel, e->fds[cs].user.channel))
		{
			if (msg_type == MSG_INFO)
			{
				strcpy(e->fds[i].buf_write, "\033[31m==\033[0m ");
				strcat(e->fds[i].buf_write, message);
			}
			else if (i != cs)
			{
				strcpy(e->fds[i].buf_write, "\033[33m<");
				strcat(e->fds[i].buf_write, e->fds[cs].user.nickname);
				strcat(e->fds[i].buf_write, ">\033[0m ");
				strcat(e->fds[i].buf_write, message);
			}
		}
		i++;
	}
}

void			run_cmd(t_env *e, int cs, char *buf)
{
	char		**input_arr;

	input_arr = ft_strsplit(buf, ' ');
	if (!strncmp(input_arr[0], "/nick", 5))
		change_nick(e, cs, input_arr);
	else if (!strncmp(input_arr[0], "/msg", 4))
		send_msg(e, input_arr, cs);
	else if (!strncmp(input_arr[0], "/join", 5))
		join_chan(e, cs, input_arr);
	else if (!strncmp(input_arr[0], "/leave", 6))
		leave_chan(e, cs, input_arr);
	else if (!strncmp(input_arr[0], "/who", 4))
		who_in_chan(e, cs, input_arr);
	else if (!strncmp(input_arr[0], "/help", 5))
		print_help(e, cs, input_arr);
	else if (strncmp(input_arr[0], "/connect", 4))
		strcpy(e->fds[cs].buf_write, "\033[31m==\033[0m Unknow command\n");
	ft_arrdel(input_arr);
	memset(e->fds[cs].buf_read, 0, BUF_SIZE + 1);
}
