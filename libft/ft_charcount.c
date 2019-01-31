/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charcount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lstreak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 14:50:57 by lstreak           #+#    #+#             */
/*   Updated: 2017/06/10 09:39:04 by lstreak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_charcount(long n)
{
	size_t i;

	i = 1;
	if (n < 0)
		n = -n;
	while (n >= 10)
	{
		i++;
		n /= 10;
	}
	return (i);
}

int			ft_arrlen(char **array)
{
	int		i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

char	*ft_strndup(const char *src, size_t n)
{
	char	*dst;
	size_t	i;

	i = 0;
	dst = (char*)malloc(sizeof(char) * (*src));
	if (!src || !dst)
		return (NULL);
	while (src[i] && i < n)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
