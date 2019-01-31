/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstreak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 10:45:28 by lstreak           #+#    #+#             */
/*   Updated: 2018/08/24 10:45:29 by lstreak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void				clean_fd(int i, t_env *e)
{
	e->fds[i].type = FD_FREE;
	e->fds[i].fct_read = NULL;
	e->fds[1].fct_write = NULL;
	memset(e->fds[i].buf_write, 0, BUF_SIZE + 1);
	memset(e->fds[i].buf_read, 0, BUF_SIZE + 1);
	memset(e->fds[i].user.channel, 0, CHAN_SIZE + 1);
	memset(e->fds[i].user.nickname, 0, NICK_SIZE + 1);
}

void				check_fd(t_env *e)
{
	int				i;

	i = 0;
	while (i < e->maxfd && e->ret > 0)
	{
		if (FD_ISSET(i, &e->fd_read))
			e->fds[i].fct_read(e, i);
		if (FD_ISSET(i, &e->fd_write))
			e->fds[i].fct_write(e, i);
		if (FD_ISSET(i, &e->fd_read) || FD_ISSET(i, &e->fd_write))
			e->ret--;
		i++;
	}
}

void				init_env(t_env *e)
{
	int				i;
	struct rlimit	rlp;

	if (getrlimit(RLIMIT_NOFILE, &rlp) < 0)
		print_error("getrlimit: failed");
	e->maxfd = rlp.rlim_cur;
	if (!(e->fds = (t_fd*)malloc(sizeof(*e->fds) * e->maxfd)))
		print_error("malloc: failed");
	i = 0;
	while (i <= e->maxfd)
	{
		clean_fd(i, e);
		i++;
	}
}

void				init_fd(t_env *e)
{
	int				i;

	i = 0;
	e->max = 0;
	FD_ZERO(&e->fd_read);
	FD_ZERO(&e->fd_write);
	while (i < e->maxfd)
	{
		if (e->fds[i].type != FD_FREE)
		{
			FD_SET(i, &e->fd_read);
			if (strlen(e->fds[i].buf_write) > 0)
				FD_SET(i, &e->fd_write);
			e->max = MAX(e->max, i);
		}
		i++;
	}
}
