/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstreak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/24 16:40:24 by lstreak           #+#    #+#             */
/*   Updated: 2018/08/24 16:40:25 by lstreak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void				print_error(char *str)
{
	fprintf(stderr, "%s\n", str);
	exit(EXIT_FAILURE);
}

void				print_prompt(t_env *e)
{
	ft_putstr("\033[36m");
	ft_putstr(e->nickname);
	ft_putstr(" $> ");
	ft_putstr("\033[0m");
}

void				clean_input(void)
{
	char			tmp[BUF_SIZE];

	memset(tmp, 0, BUF_SIZE);
	memset(tmp, '\b', NICK_SIZE + 4);
	ft_putstr(tmp);
	memset(tmp, 0, BUF_SIZE);
	memset(tmp, ' ', NICK_SIZE + 4);
	ft_putstr(tmp);
	memset(tmp, 0, BUF_SIZE);
	memset(tmp, '\b', NICK_SIZE + 4);
	ft_putstr(tmp);
}
