/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:46:30 by chansjeo          #+#    #+#             */
/*   Updated: 2024/06/17 15:07:40 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_putstr_fd(char *str, int fd)
{
	int	len;

	len = ft_strlen(str);
	write(fd, str, len);
	return (-1);
}

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str && *str++)
		len++;
	return (len);
}

int	is_digit(const char *str)
{
	if (*str >= '0' && *str <= '9')
		return (1);
	return (0);
}

const char	*valid_arg(const char *str)
{
	const char	*res;

	while (*str == ' ' || *str == '\t' || *str == '\r' || \
			*str == '\n' || *str == '\v' || *str == '\f')
		++str;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
		{
			ft_putstr_fd("positive_only\n", 2);
			return (0);
		}
		++str;
	}
	res = str;
	while (*str)
	{
		if (!is_digit(str))
			return (0);
		str++;
	}
	if (ft_strlen(res) > 10)
		return (0);
	return (res);
}

long	ft_atol(const char *str)
{
	unsigned long	dec;
	unsigned long	ret;
	char			*s;

	ret = 0;
	s = (char *)valid_arg(str);
	if (s == NULL)
		return (ft_putstr_fd("invalid_arg!\n", 2));
	while (1)
	{
		dec = *(s++) - '0';
		if (dec > 9)
			break ;
		ret = ret * 10 + dec;
		if (ret > INT_MAX)
			return (ft_putstr_fd("out_of_range_int!\n", 2));
	}
	return (ret);
}
