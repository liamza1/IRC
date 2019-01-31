/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstreak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 10:41:32 by lstreak           #+#    #+#             */
/*   Updated: 2018/08/24 10:41:33 by lstreak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include "../libft/libft.h"
# include <stdio.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <dirent.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/select.h>
# include <sys/time.h>
# include <stdbool.h>

# define BUF_SIZE	512
# define NICK_SIZE	9
# define CHAN_SIZE	200
# define CHAN_GEN	"#ft_irc-default"
# define DATE_SIZE	26
# define FD_FREE	0
# define FD_SERV	1
# define FD_CLIENT	2
# define MSG_INFO	0
# define MSG_STD	1
# define MAX(a,b)	((a > b) ? a : b)
# define USAGE		"Usage : ./serveur <port>"

typedef struct sockaddr_in	t_sockaddr_in;

typedef struct		s_user
{
	char			channel[CHAN_SIZE + 1];
	char			nickname[NICK_SIZE + 1];
}					t_user;

typedef struct		s_fd
{
	int				type;
	void			(*fct_read)();
	void			(*fct_write)();
	char			buf_read[BUF_SIZE + 1];
	char			buf_write[BUF_SIZE + 1];
	t_user			user;
}					t_fd;

typedef struct		s_env
{
	t_fd			*fds;
	t_sockaddr_in	csin;
	socklen_t		cslen;
	int				port;
	int				sock;
	int				maxfd;
	int				max;
	int				ret;
	int				ret_recv;
	fd_set			fd_read;
	fd_set			fd_write;
	char			strtime[DATE_SIZE];
}					t_env;

void				init_fd(t_env *e);
void				init_env(t_env *e);
void				check_fd(t_env *e);
void				srv_accept(t_env *e);
void				ring_buffer_read(t_env *e, int cs, char *msg);
void				ring_buffer_write(t_env *e, int cs, char *msg);
void				run_cmd(t_env *e, int cs, char *buf);
void				send_msg(t_env *e, char **input_arr, int cs);
void				join_chan(t_env *e, int cs, char **inp_arr);
void				leave_chan(t_env *e, int cs, char **input_arr);
void				change_nick(t_env *e, int cs, char **input_arr);
void				who_in_chan(t_env *e, int cs, char **input_arr);
int					get_fd_from_usr(t_env *e, char *name);
int					duplicate_user(t_env *e, int cs, char *name);
void				send_to_chan(t_env *e, char *message, int msg_type, int cs);
void				clean_fd(int i, t_env *e);
void				print_error(char *str);
void				get_time(t_env *e);

#endif
